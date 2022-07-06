#pragma once

#include <vector>
#include "Light.hpp"
#include "OmniShadowMap.hpp"

/**
 * @class PointLight
 * @brief A point light that illuminates in a sphere.
 */
class PointLight : public Light {
public:
	PointLight() = default;

	/**
	 * @brief Construct a new Point Light object
	 *
	 * @param color The color of the light
	 * @param aIntensity The ambient intensity of the light
	 * @param dIntensity The diffuse intensity of the light
	 * @param position The position of the light
	 * @param constant The constant attenuation of the light
	 * @param linear The linear attenuation of the light
	 * @param quadratic The quadratic attenuation of the light
	 */
	PointLight(glm::vec3 color, GLfloat aIntensity, GLfloat dIntensity,
	           glm::vec3 position, GLfloat constant, GLfloat linear,
	           GLfloat quadratic);

	/**
	 * @brief Enables the light by passing uniforms to the shader.
	 *
	 * @param ambientColorLoc
	 * @param ambientIntensityLoc
	 * @param diffuseIntensityLoc
	 * @param positionLoc
	 * @param constantLoc
	 * @param linearLoc
	 * @param quadraticLoc
	 */
	void UseLight(GLuint ambientColorLoc, GLuint ambientIntensityLoc,
	              GLuint diffuseIntensityLoc, GLuint positionLoc,
	              GLuint constantLoc, GLuint linearLoc,
	              GLuint quadraticLoc) const;

	/**
	 * @brief Set the point light object
	 *
	 * @param color The color of the light
	 * @param aIntensity The ambient intensity of the light
	 * @param dIntensity The diffuse intensity of the light
	 * @param position The position of the light
	 * @param constant The constant attenuation of the light
	 * @param linear The linear attenuation of the light
	 * @param quadratic The quadratic attenuation of the light
	 */
	void set_point_light(glm::vec3 color, GLfloat aIntensity,
	                     GLfloat dIntensity, glm::vec3 position,
	                     GLfloat constant, GLfloat linear, GLfloat quadratic);

	/**
	 * @brief Get the Position.
	 *
	 * @return glm::vec3
	 */
	glm::vec3 GetPosition() const;

	/**
	 * @brief Destroy the Point Light object
	 */
	~PointLight() = default;

protected:
	/// Position of the light.
	glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f);

	/// Equation of the light.
	GLfloat m_constant = 1.0f;
	GLfloat m_linear = 0.0f;
	GLfloat m_quadratic = 0.0f;
};
