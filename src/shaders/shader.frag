#version 460 core

in vec4 vColor;
in vec2 texCoord;

out vec4 color;

uniform sampler2D theTexture;

void main()
{
	color = texture(theTexture, texCoord);
}
