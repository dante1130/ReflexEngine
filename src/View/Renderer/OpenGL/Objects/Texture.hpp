#pragma once

#include <iostream>

#include <glad/glad.h>

#include "StbImage.hpp"

/**
 * @class Texture
 * @brief A texture class.
 */
class Texture {
public:
	/**
	 * @brief Construct a new Texture object
	 *
	 * @param fileLocation
	 */
	Texture(const char* fileLocation);

	/**
	 * @brief Set the texture unit.
	 *
	 * @param texture_unit
	 */
	void set_texture_unit(GLuint texture_unit);

	/**
	 * @brief Loads a texture without alpha.
	 *
	 * @return true
	 * @return false
	 */
	bool LoadTexture();

	/**
	 * @brief Loads a texture with alpha.
	 *
	 * @return true
	 * @return false
	 */
	bool LoadTextureA();

	/**
	 * @brief Enables the texture.
	 */
	void UseTexture() const;

	/**
	 * @brief Clears the texture.
	 */
	void ClearTexture();

	/**
	 * @brief Destroy the Texture object
	 */
	~Texture();

private:
	// The file location of the texture.
	const char* m_fileLocation;

	/// The texture ID.
	GLuint m_textureID = 0u;

	/// The texture unit.
	GLuint texture_unit_ = GL_TEXTURE1;

	/// Information regarding the texture image.
	int m_width = 0, m_height = 0, m_bitDepth = 0;
};
