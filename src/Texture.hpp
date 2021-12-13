#pragma once

#include <iostream>

#include <glad/glad.h>

#include <stb_image.h>

class Texture
{
public:
	Texture();
	Texture(char* fileLocation);

	void LoadTexture();
	void UseTexture();
	void ClearTexture();

	~Texture();

private:
	GLuint m_textureID;
	int m_width, m_height, m_bitDepth;

	char* m_fileLocation;
};
