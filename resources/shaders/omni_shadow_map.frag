#version 410 core

in vec4 fragPos;

uniform vec3 light_pos;
uniform float far_plane;

void main() {
	float light_distance = length(fragPos.xyz - light_pos);
	light_distance /= far_plane;

	gl_FragDepth = light_distance;
}
