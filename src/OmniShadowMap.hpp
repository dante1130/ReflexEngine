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
	 *
	 */
	OmniShadowMap();

	/**
	 * @brief Initializes the shadowmap with a width and height.
	 *
	 * @param width
	 * @param height
	 * @return true
	 * @return false
	 */
	bool Init(GLuint width, GLuint height) override;

	/**
	 * @brief Binds the framebuffer with the FBO.
	 *
	 */
	void Write() override;

	/**
	 * @brief Enables the texture for the shadow.
	 *
	 * @param textureUnit
	 */
	void Read(GLenum textureUnit) override;
};
