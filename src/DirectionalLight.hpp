#pragma once

#include "Light.hpp"

class DirectionalLight : public Light
{
public:
	DirectionalLight();

	DirectionalLight(GLfloat shadowWidth, GLfloat shadowHeight,
					 glm::vec3 color, GLfloat aIntensity, glm::vec3 direction, GLfloat dIntensity);

	void UseLight(GLuint ambientColorLoc, GLuint ambientIntensityLoc, GLuint directionLoc, GLuint diffuseIntensityLoc) const;

	glm::mat4 CalculateLightTransform() const;

	~DirectionalLight();

private:
	glm::vec3 m_direction;

};
