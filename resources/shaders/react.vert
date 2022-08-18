#version 410 core

layout(location = 0) in vec3 pos;
layout(location = 1) in uint color;

out vec4 frag_color;

uniform mat4 projection;
uniform mat4 view;

void main() {
	gl_Position = projection * view * vec4(pos, 1.0);

	frag_color = vec4(vec3(color) / 255.0f, 1.0f);
}
