#version 410 core

in vec3 vColor;
in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;
in vec4 directional_light_space_pos

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
	samplerCube shadowMap;
	float farPlane;
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
uniform OmniShadowMap omniShadowMaps[MAX_POINT_LIGHTS + MAX_SPOT_LIGHTS];

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

float calc_directional_shadow_factor(DirectionalLight light) {
	vec3 proj_coords = directional_light_space_pos.xyz / directional_light_space_pos.w;
	proj_coords = (proj_coords * 0.5) + 0.5;

	float closest = texture(directional_shadow_map, proj_coords.xy).r;
	float current = proj_coords.z;

	float shadow = current > closest ? 1.0 : 0.0;

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

	return ambientColor + ((1.0 - shadow) * (diffuseColor + specularColor));
}

vec4 CalcDirectionalLight()
{
	float shadow_factor = calc_directional_shadow_factor(directionalLight)
	return CalcLightByDirection(directionalLight.base, directionalLight.direction, shadow_factor);
}

vec4 CalcPointLight(PointLight pLight)
{
	vec3 direction = fragPos - pLight.position;
	float distance = length(direction);

	vec4 color = CalcLightByDirection(pLight.base, direction, 0.0f);

	float attenuation = (pLight.exponent * (distance * distance)) +
						(pLight.linear * distance) + 
						(pLight.constant);
						
	return (color / attenuation);
}

vec4 CalcSpotLight(SpotLight sLight)
{
	vec3 rayDirection = normalize(fragPos - sLight.base.position);

	float slFactor = dot(rayDirection, sLight.direction);

	if (slFactor > sLight.edge)
	{
		vec4 color = CalcPointLight(sLight.base);

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
		totalColor += CalcPointLight(pointLights[i]);
	}

	return totalColor;
}

vec4 CalcSpotLights()
{
	vec4 totalColor = vec4(0, 0, 0, 0);

	for (int i = 0; i < spotLightCount; ++i)
	{
		totalColor += CalcSpotLight(spotLights[i]);
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

