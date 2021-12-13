#version 460 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 norm;

out vec4 vColor;
out vec2 texCoord;
out vec3 normal;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
	gl_Position = projection * view * model * vec4(pos, 1.0f);
	vColor = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);

	texCoord = tex;

	normal = mat3(transpose(inverse(model))) * norm;

	fragPos = (model * vec4(pos, 1.0f)).xyz;
}
