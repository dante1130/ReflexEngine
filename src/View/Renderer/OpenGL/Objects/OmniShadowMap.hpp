#pragma once

#include "ShadowMap.hpp"

/**
 * @class OmniShadowMap
 * @brief A shadowmap cast by omnidirectional lights.
 */
class OmniShadowMap : public ShadowMap {
public:
	/**
	 * @brief Construct a new Omni Shadow Map object
	 */
	OmniShadowMap() = default;

	/**
	 * @brief Initializes the shadowmap with a width and height.
	 *
	 * @param width The width of the shadowmap.
	 * @param height The height of the shadowmap.
	 * @return bool
	 */
	bool init(GLuint width, GLuint height) override;

	/**
	 * @brief Binds the framebuffer with the FBO.
	 *
	 */
	void write() const override;

	/**
	 * @brief Enables the texture for the shadow.
	 *
	 * @param textureUnit The texture unit to bind the shadowmap to.
	 */
	void read(GLenum textureUnit) const override;
};
