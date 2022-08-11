#version 410 core

in vec4 fragPos;

uniform vec3 light_pos;
uniform float far_plane;

void main() 
{
	float theDistance = length(fragPos.xyz - light_pos);
	theDistance /= far_plane;

	gl_FragDepth = theDistance;
}
