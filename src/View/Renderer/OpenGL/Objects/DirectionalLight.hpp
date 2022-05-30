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
	 * @param shadowWidth The width of the shadow map.
	 * @param shadowHeight The height of the shadow map.
	 * @param color The color of the light.
	 * @param aIntensity The ambient intensity of the light.
	 * @param direction The direction of the light.
	 * @param dIntensity The diffuse intensity of the light.
	 */
	DirectionalLight(GLfloat shadowWidth, GLfloat shadowHeight, glm::vec3 color,
	                 GLfloat aIntensity, glm::vec3 direction,
	                 GLfloat dIntensity);

	/**
	 * @brief Enables the light by passing the uniforms to the shader.
	 *
	 * @param ambientColorLoc The location of the ambient color uniform.
	 * @param ambientIntensityLoc The location of the ambient intensity uniform.
	 * @param directionLoc The location of the direction uniform.
	 * @param diffuseIntensityLoc The location of the diffuse intensity uniform.
	 */
	void UseLight(GLuint ambientColorLoc, GLuint ambientIntensityLoc,
	              GLuint directionLoc, GLuint diffuseIntensityLoc) const;

	/**
	 * @brief Calculate the transformation matrix of the light.
	 *
	 * @return glm::mat4 The transformation matrix of the light.
	 */
	glm::mat4 CalculateLightTransform() const;

	/**
	 * @brief Destructor.
	 */
	~DirectionalLight();

private:
	/// The direction the light is facing.
	glm::vec3 m_direction;
};
