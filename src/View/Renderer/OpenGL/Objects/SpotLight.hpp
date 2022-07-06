#pragma once

#include "PointLight.hpp"

/**
 * @class Spotlight
 * @brief A spotlight that illuminates to a direction like a flashlight.
 */
class SpotLight : public PointLight {
public:
	SpotLight() = default;

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
	 * @brief Set the spotlight object
	 *
	 * @param color  The color of the light.
	 * @param aIntensity  The ambient intensity of the light.
	 * @param dIntensity  The diffuse intensity of the light.
	 * @param position  The position of the light.
	 * @param direction  The direction of the light.
	 * @param constant  The constant of the light.
	 * @param linear  The linear of the light.
	 * @param quadratic  The quadratic of the light.
	 * @param edge  The edge of the light.
	 */
	void set_spot_light(glm::vec3 color, GLfloat aIntensity, GLfloat dIntensity,
	                    glm::vec3 position, glm::vec3 direction,
	                    GLfloat constant, GLfloat linear, GLfloat quadratic,
	                    GLfloat edge);

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

private:
	glm::vec3 m_direction = glm::vec3(0.0f, -1.0f, 0.0f);

	GLfloat m_procEdge = 0.0f;
};
