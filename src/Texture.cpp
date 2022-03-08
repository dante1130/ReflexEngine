#include "Texture.hpp"

Texture::Texture()
	: m_textureID(0), m_width(0), m_height(0), m_bitDepth(0), m_fileLocation("")
{}

Texture::Texture(const char* fileLocation)
	: m_textureID(0), m_width(0), m_height(0), m_bitDepth(0), m_fileLocation(fileLocation)
{}

bool Texture::LoadTexture()
{
	unsigned char* texData = stbi_load(m_fileLocation, &m_width, &m_height, &m_bitDepth, 0);

	if (!texData)
	{
		std::cout << "Failed to load image " << m_fileLocation << std::endl;
		return false;
	}

	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(texData);

	return true;
}

bool Texture::LoadTextureA()
{
	unsigned char* texData = stbi_load(m_fileLocation, &m_width, &m_height, &m_bitDepth, 0);

	if (!texData)
	{
		std::cout << "Failed to load image " << m_fileLocation << std::endl;
		return false;
	}

	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(texData);

	return true;
}

void Texture::UseTexture()
{
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::ClearTexture()
{
	glDeleteTextures(1, &m_textureID);

	m_textureID = 0;
	m_width = 0;
	m_height = 0;
	m_bitDepth = 0;
	m_fileLocation = "";
}

Texture::~Texture()
{
	ClearTexture();
}
