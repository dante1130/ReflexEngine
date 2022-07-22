#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "StbImage.hpp"

Texture::Texture(const char* fileLocation) : m_fileLocation(fileLocation) {}

GLuint Texture::get_texture_id() const { return m_textureID; }

int Texture::get_width() const { return m_width; }

int Texture::get_height() const { return m_height; }

void Texture::set_texture_unit(GLuint texture_unit) {
	texture_unit_ = texture_unit;
}

bool Texture::LoadTexture() {
	unsigned char* texData =
	    stbi_load(m_fileLocation, &m_width, &m_height, &m_bitDepth, 0);

	if (!texData) {
		std::cout << "Failed to load image " << m_fileLocation << std::endl;
		return false;
	}

	auto channel = m_bitDepth == 3 ? GL_RGB : GL_RGBA;

	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
	                GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, channel, m_width, m_height, 0, channel,
	             GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(texData);

	return true;
}

bool Texture::LoadTextureA() {
	unsigned char* texData =
	    stbi_load(m_fileLocation, &m_width, &m_height, &m_bitDepth, 0);

	if (!texData) {
		std::cout << "Failed to load image " << m_fileLocation << std::endl;
		return false;
	}

	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
	                GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA,
	             GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(texData);

	return true;
}

void Texture::UseTexture() const {
	glActiveTexture(texture_unit_);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::set_texture_id(GLuint id) { m_textureID = id; }

void Texture::ClearTexture() {
	glDeleteTextures(1, &m_textureID);

	m_textureID = 0;
	m_width = 0;
	m_height = 0;
	m_bitDepth = 0;
	m_fileLocation = "";
}

Texture::~Texture() { ClearTexture(); }
