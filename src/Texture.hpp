#pragma once

#include <iostream>

#include <glad/glad.h>

#include "StbImage.hpp"

class Texture
{
public:
	Texture();
	Texture(const char* fileLocation);

	bool LoadTexture();
	bool LoadTextureA();

	void UseTexture();
	void ClearTexture();

	~Texture();

private:
	GLuint m_textureID;
	int m_width, m_height, m_bitDepth;

	const char* m_fileLocation;
};
