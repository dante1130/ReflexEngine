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
	ShadowMap() = default;

	/**
	 * @brief Generates the framebuffer for the shadow map.
	 *
	 * @param width The width of the shadow map.
	 * @param height The height of the shadow map.
	 * @return bool
	 */
	virtual bool init(GLuint width, GLuint height);

	/**
	 * @brief Binds the FBO of the shadow map.
	 */
	virtual void write() const;

	/**
	 * @brief Enable the shadow map given a texture unit.
	 *
	 * @param textureUnit The texture unit to bind the shadow map to.
	 */
	virtual void read(GLenum textureUnit) const;

	/**
	 * @brief Get the Shadow Width
	 *
	 * @return GLuint
	 */
	GLuint get_shadow_width() const;

	/**
	 * @brief Get the Shadow Height
	 *
	 * @return GLuint
	 */
	GLuint get_shadow_height() const;

	/**
	 * @brief Destroy the Shadow Map object
	 */
	virtual ~ShadowMap();

protected:
	/// The framebuffer object.
	GLuint fbo_ = 0U;

	/// The shadow map.
	GLuint shadow_map_ = 0U;

	/// Shadow dimensions.
	GLuint shadow_width_ = 0U, shadow_height_ = 0U;
};
