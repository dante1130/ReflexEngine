#pragma once

#include <iostream>

#include <glad/glad.h>

/**
 * @class ShadowMap
 * @brief A shadow map.
 */
class ShadowMap {
public:
	/**
	 * @brief Construct a new Shadow Map object
	 */
	ShadowMap();

	/**
	 * @brief Generates the framebuffer for the shadow map.
	 *
	 * @param width The width of the shadow map.
	 * @param height The height of the shadow map.
	 * @return bool
	 */
	virtual bool Init(GLuint width, GLuint height);

	/**
	 * @brief Binds the FBO of the shadow map.
	 */
	virtual void Write();

	/**
	 * @brief Enable the shadow map given a texture unit.
	 *
	 * @param textureUnit The texture unit to bind the shadow map to.
	 */
	virtual void Read(GLenum textureUnit);

	/**
	 * @brief Get the Shadow Width
	 *
	 * @return GLuint
	 */
	GLuint GetShadowWidth() const;

	/**
	 * @brief Get the Shadow Height
	 *
	 * @return GLuint
	 */
	GLuint GetShadowHeight() const;

	/**
	 * @brief Destroy the Shadow Map object
	 */
	virtual ~ShadowMap();

protected:
	/// The framebuffer object.
	GLuint m_fbo;

	/// The shadow map.
	GLuint m_shadowMap;

	/// Shadow dimensions.
	GLuint m_shadowWidth, m_shadowHeight;
};
