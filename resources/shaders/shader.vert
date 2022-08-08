#version 410 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 tex;
layout(location = 2) in vec3 norm;
layout(location = 3) in vec3 color;

out vec3 vColor;
out vec2 texCoord;
out vec3 normal;
out vec3 fragPos;
out vec4 directional_light_space_pos;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 directional_light_transform;

void main() {
	vColor = color;

	texCoord = tex;

	normal = mat3(transpose(inverse(model))) * norm;

	fragPos = (model * vec4(pos, 1.0f)).xyz;

	gl_Position = projection * view * vec4(fragPos, 1.0f);

	directional_light_space =
	    directional_light_transform * model * vec4(pos, 1.0f);
}
