#version 410 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 tex;

out vec2 v_tex;

uniform mat4 model;
uniform mat4 directional_light_transform;

void main() {
	gl_Position = directional_light_transform * model * vec4(pos, 1.0);
	v_tex = tex;
}
