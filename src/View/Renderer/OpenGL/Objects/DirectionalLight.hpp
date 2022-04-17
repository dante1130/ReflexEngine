#pragma once

#include "Light.hpp"

/**
 * @class DirectionalLight
 * @brief A directional light that provides global illumination.
 */
class DirectionalLight : public Light {
public:
	/**
	 * @brief Default constructor.
	 */
	DirectionalLight();

	/**
	 * @brief Parameterized constructor.
	 *
	 * @param shadowWidth
	 * @param shadowHeight
	 * @param color
	 * @param aIntensity
	 * @param direction
	 * @param dIntensity
	 */
	DirectionalLight(GLfloat shadowWidth, GLfloat shadowHeight, glm::vec3 color,
	                 GLfloat aIntensity, glm::vec3 direction,
	                 GLfloat dIntensity);

	/**
	 * @brief Enables the light by passing the uniforms to the shader.
	 *
	 * @param ambientColorLoc
	 * @param ambientIntensityLoc
	 * @param directionLoc
	 * @param diffuseIntensityLoc
	 */
	void UseLight(GLuint ambientColorLoc, GLuint ambientIntensityLoc,
	              GLuint directionLoc, GLuint diffuseIntensityLoc) const;

	/**
	 * @brief Calculate the transformation matrix of the light.
	 *
	 * @return glm::mat4
	 */
	glm::mat4 CalculateLightTransform() const;

	/**
	 * @brief Destructor.
	 *
	 */
	~DirectionalLight();

private:
	/// The direction the light is facing.
	glm::vec3 m_direction;
};
