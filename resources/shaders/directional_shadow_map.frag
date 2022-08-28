#version 410 core

in vec2 v_tex;

out vec4 color;

uniform sampler2D theTexture;

void main() {
	float alpha = texture(theTexture, v_tex).a;

	if (alpha < 0.5) {
		discard;
	}

	color = vec4(1.0);
}
