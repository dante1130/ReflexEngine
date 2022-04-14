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
	 * @param shadowWidth
	 * @param shadowHeight
	 * @param near
	 * @param far
	 * @param color
	 * @param aIntensity
	 * @param dIntensity
	 * @param position
	 * @param constant
	 * @param linear
	 * @param exponent
	 */
	PointLight(GLuint shadowWidth, GLuint shadowHeight, GLfloat near,
	           GLfloat far, glm::vec3 color, GLfloat aIntensity,
	           GLfloat dIntensity, glm::vec3 position, GLfloat constant,
	           GLfloat linear, GLfloat exponent);

	/**
	 * @brief Enables the light by passing uniforms to the shader.
	 *
	 * @param ambientColorLoc
	 * @param ambientIntensityLoc
	 * @param diffuseIntensityLoc
	 * @param positionLoc
	 * @param constantLoc
	 * @param linearLoc
	 * @param exponentLoc
	 */
	void UseLight(GLuint ambientColorLoc, GLuint ambientIntensityLoc,
	              GLuint diffuseIntensityLoc, GLuint positionLoc,
	              GLuint constantLoc, GLuint linearLoc,
	              GLuint exponentLoc) const;

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
	GLfloat m_constant, m_linear, m_exponent;

	/// The far plane.
	GLfloat m_farPlane;
};
