#version 460 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 tex;
layout(location = 2) in vec3 norm;
layout(location = 3) in vec3 color;

out vec3 vColor;
out vec2 texCoord;
out vec3 normal;
out vec3 fragPos;
out vec4 directionalLightSpacePos;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 directionalLightTransform;

void main() {
	gl_Position = projection * view * model * vec4(pos, 1.0f);

	directionalLightSpacePos =
	    directionalLightTransform * model * vec4(pos, 1.0f);

	vColor = color;

	texCoord = tex;

	normal = mat3(transpose(inverse(model))) * norm;

	fragPos = (model * vec4(pos, 1.0f)).xyz;
}
