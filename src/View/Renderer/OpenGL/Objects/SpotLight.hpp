#pragma once

#include "PointLight.hpp"

/**
 * @class Spotlight
 * @brief A spotlight that illuminates to a direction like a flashlight.
 */
class SpotLight : public PointLight {
public:
	/**
	 * @brief Construct a new Spot Light object
	 *
	 * @param color
	 * @param aIntensity
	 * @param dIntensity
	 * @param position
	 * @param direction
	 * @param constant
	 * @param linear
	 * @param quadratic
	 * @param edge
	 */
	SpotLight(glm::vec3 color, GLfloat aIntensity, GLfloat dIntensity,
	          glm::vec3 position, glm::vec3 direction, GLfloat constant,
	          GLfloat linear, GLfloat quadratic, GLfloat edge);

	/**
	 * @brief Enables the spotlight by passing uniforms to the shader.
	 *
	 * @param ambientColorLoc
	 * @param ambientIntensityLoc
	 * @param diffuseIntensityLoc
	 * @param positionLoc
	 * @param directionLoc
	 * @param constantLoc
	 * @param linearLoc
	 * @param quadraticLoc
	 * @param edgeLoc
	 */
	void UseLight(GLuint ambientColorLoc, GLuint ambientIntensityLoc,
	              GLuint diffuseIntensityLoc, GLuint positionLoc,
	              GLuint directionLoc, GLuint constantLoc, GLuint linearLoc,
	              GLuint quadraticLoc, GLuint edgeLoc) const;

	/**
	 * @brief Sets the position and the direction of the spotlight.
	 *
	 * @param pos
	 * @param dir
	 */
	void SetFlash(glm::vec3 pos, glm::vec3 dir);

private:
	glm::vec3 m_direction = glm::vec3(0.0f, -1.0f, 0.0f);

	GLfloat m_procEdge = 0.0f;
};
