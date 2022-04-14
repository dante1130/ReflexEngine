#version 410 core

in vec4 fragPos;

uniform vec3 lightPos;
uniform float farPlane;

void main()
{
	float theDistance = length(fragPos.xyz - lightPos);

	theDistance = theDistance / farPlane;

	gl_FragDepth = theDistance;
}
