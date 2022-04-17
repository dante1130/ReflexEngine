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
	 */
	Texture();

	/**
	 * @brief Construct a new Texture object
	 *
	 * @param fileLocation
	 */
	Texture(const char* fileLocation);

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
	/// The texture ID.
	GLuint m_textureID;

	/// Information regarding the texture image.
	int m_width, m_height, m_bitDepth;

	// The file location of the texture.
	const char* m_fileLocation;
};
