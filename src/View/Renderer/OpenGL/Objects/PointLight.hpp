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
	/**
	 * @brief Construct a new Point Light object
	 */
	PointLight();

	/**
	 * @brief Construct a new Point Light object
	 *
	 * @param shadowWidth The width of the shadow map
	 * @param shadowHeight The height of the shadow map
	 * @param near The near plane of the shadow map
	 * @param far The far plane of the shadow map
	 * @param color The color of the light
	 * @param aIntensity The ambient intensity of the light
	 * @param dIntensity The diffuse intensity of the light
	 * @param position The position of the light
	 * @param constant The constant attenuation of the light
	 * @param linear The linear attenuation of the light
	 * @param quadratic The quadratic attenuation of the light
	 */
	PointLight(GLuint shadowWidth, GLuint shadowHeight, GLfloat near,
	           GLfloat far, glm::vec3 color, GLfloat aIntensity,
	           GLfloat dIntensity, glm::vec3 position, GLfloat constant,
	           GLfloat linear, GLfloat quadratic);

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
	 * @brief Calculates the light transform matrices.
	 *
	 * @return std::vector<glm::mat4>
	 */
	std::vector<glm::mat4> CalculateLightTransform() const;

	/**
	 * @brief Get the Far Plane.
	 *
	 * @return GLfloat
	 */
	GLfloat GetFarPlane() const;

	/**
	 * @brief Get the Position.
	 *
	 * @return glm::vec3
	 */
	glm::vec3 GetPosition() const;

	/**
	 * @brief Destroy the Point Light object
	 */
	~PointLight();

protected:
	/// Position of the light.
	glm::vec3 m_position;

	/// Equation of the light.
	GLfloat m_constant, m_linear, m_quadratic;

	/// The far plane.
	GLfloat m_farPlane;
};
