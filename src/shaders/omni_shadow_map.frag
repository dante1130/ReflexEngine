#version 460 core

in vec4 fragPos;

uniform vec3 lightPos;
uniform float farPlane;

void main()
{
	float distance = length(fragPos.xyz - lightPos);

	distance = distance / farPlane;

	gl_FragDepth = distance;
}
