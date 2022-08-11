#version 410 core

in vec3 vColor;
in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;
in vec4 directional_light_space_pos;

out vec4 color;

const int MAX_POINT_LIGHTS = 16;
const int MAX_SPOT_LIGHTS = 16;

struct Light
{
	vec3 color;
	float ambientIntensity;
	float diffuseIntensity;
};

struct DirectionalLight
{
	Light base;
	vec3 direction;
};

struct PointLight
{
	Light base;
	vec3 position;
	float constant;
	float linear;
	float exponent;
};

struct SpotLight
{
	PointLight base;
	vec3 direction;
	float edge;
};

struct OmniShadowMap
{
	samplerCube shadow_map;
	float far_plane;
};

struct Material
{
	float specularIntensity;
	float shininess;
};

uniform bool isUsingTexture;
uniform bool is_using_detailmap;

uniform int pointLightCount;
uniform int spotLightCount;

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

uniform sampler2D theTexture;
uniform sampler2D directional_shadow_map;
uniform sampler2D detailmap;
uniform OmniShadowMap omni_shadow_maps[MAX_POINT_LIGHTS + MAX_SPOT_LIGHTS];

uniform Material material;

uniform vec3 eyePosition;

vec3 sampleOffsetDirections[20] = vec3[]
(
   vec3(1, 1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1, 1,  1), 
   vec3(1, 1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
   vec3(1, 1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1, 1,  0),
   vec3(1, 0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1, 0, -1),
   vec3(0, 1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0, 1, -1)
);

float calc_directional_shadow_factor(DirectionalLight light) 
{
	vec3 proj_coords = directional_light_space_pos.xyz / directional_light_space_pos.w;
	proj_coords = (proj_coords * 0.5) + 0.5;

	float current = proj_coords.z;

	vec3 normal = normalize(normal);
	vec3 light_dir = normalize(light.direction - fragPos);

	float bias = max(0.05 * (1.0 - dot(normal, light_dir)), 0.005);
	float shadow = 0.0;

	vec2 texel_size = 1.0 / textureSize(directional_shadow_map, 0);

	for (int x = -1; x <= 1; ++x) 
	{
		for (int y = -1; y <= 1; ++y) 
		{
			float pcf_depth = texture(directional_shadow_map, proj_coords.xy + vec2(x, y) * texel_size).r;
			shadow += (current - bias) > pcf_depth ? 1.0 : 0.0;
		}
	}

	// Divide by how many pixels sampled.
	shadow /= 9.0;

	if (proj_coords.z > 1.0) 
	{
		shadow = 0.0;
	}

	return shadow;
}

float calc_omni_shadow_factor(PointLight light, int shadow_index) 
{
	vec3 frag_to_light = fragPos - light.position;
	float current = length(frag_to_light);

	float shadow = 0.0;
	float bias = 0.05;
	int samples = 20;

	float view_distance = length(eyePosition - fragPos);
	float disk_radius = (1.0 * (view_distance / omni_shadow_maps[shadow_index].far_plane)) / 25.0;

	for (int i = 0; i < samples; ++i) {
		float closest = texture(omni_shadow_maps[shadow_index].shadow_map, 
								frag_to_light + sampleOffsetDirections[i] * disk_radius).r;
		closest *= omni_shadow_maps[shadow_index].far_plane;

		if (current - bias > closest) {
			shadow += 1.0;
		}
	}

	shadow /= float(samples);
	return shadow;
}

vec4 CalcLightByDirection(Light light, vec3 direction, float shadow_factor)
{
	// Ambient
	vec4 ambientColor = vec4(light.color * light.ambientIntensity, 1.0f);

	// Diffuse
	float diffuseFactor = max(dot(normalize(normal), normalize(direction)), 0.0f);
	vec4 diffuseColor = vec4(light.color * light.diffuseIntensity * diffuseFactor, 1.0f);

	// Specular
	vec3 fragToEye = normalize(eyePosition - fragPos);
	vec3 reflectedVertex = reflect(normalize(direction), normalize(normal));
	float specularFactor = pow(max(dot(fragToEye, reflectedVertex), 0.0), material.shininess);
	vec4 specularColor = vec4(light.color * material.specularIntensity * specularFactor, 1.0f);

	return ambientColor + ((1.0 - shadow_factor) * (diffuseColor + specularColor));
}

vec4 CalcDirectionalLight()
{
	float shadow_factor = calc_directional_shadow_factor(directionalLight);
	return CalcLightByDirection(directionalLight.base, directionalLight.direction, shadow_factor);
}

vec4 CalcPointLight(PointLight pLight, int shadow_index)
{
	vec3 direction = normalize(fragPos - pLight.position);
	float distance = length(direction);

	float shadow_factor = calc_omni_shadow_factor(pLight, shadow_index);

	vec4 color = CalcLightByDirection(pLight.base, direction, shadow_factor);

	float attenuation = (pLight.exponent * (distance * distance)) +
						(pLight.linear * distance) + 
						(pLight.constant);
						
	return (color / attenuation);
}

vec4 CalcSpotLight(SpotLight sLight, int shadow_index)
{
	vec3 rayDirection = normalize(fragPos - sLight.base.position);

	float slFactor = dot(rayDirection, sLight.direction);

	if (slFactor > sLight.edge)
	{
		vec4 color = CalcPointLight(sLight.base, shadow_index);

		return color * (1.0f - (1.0f - slFactor) * (1.0f / (1.0f - sLight.edge)));
	}
	else
	{
		return vec4(0, 0, 0, 0);
	}
}

vec4 CalcPointLights()
{
	vec4 totalColor = vec4(0, 0, 0, 0);

	for (int i = 0; i < pointLightCount; ++i)
	{
		totalColor += CalcPointLight(pointLights[i], i);
	}

	return totalColor;
}

vec4 CalcSpotLights()
{
	vec4 totalColor = vec4(0, 0, 0, 0);

	for (int i = 0; i < spotLightCount; ++i)
	{
		totalColor += CalcSpotLight(spotLights[i], i + pointLightCount);
	}

	return totalColor;
}

void main()
{
	vec4 finalColor = CalcDirectionalLight();
	finalColor += CalcPointLights();
	finalColor += CalcSpotLights();

	if (isUsingTexture)
	{
		finalColor *= texture(theTexture, texCoord);
	}
	else if (is_using_detailmap)
	{
		finalColor *= mix(texture(detailmap, texCoord * 100), texture(theTexture, texCoord), 0.5f);
	}
	else
	{
		finalColor += vec4(vColor, 1.0f);
	}

	color = finalColor;
}

