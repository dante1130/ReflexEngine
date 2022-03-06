#pragma once

#include "Light.hpp"

class PointLight : public Light
{
public:
	PointLight();

	PointLight(glm::vec3 color, GLfloat aIntensity, GLfloat dIntensity, glm::vec3 position, GLfloat constant, GLfloat linear, GLfloat exponent);

	void UseLight(GLuint ambientColorLoc, GLuint ambientIntensityLoc, 
				  GLuint diffuseIntensityLoc, GLuint positionLoc,
				  GLuint constantLoc, GLuint linearLoc, GLuint exponentLoc) const;

	~PointLight();

protected:
	glm::vec3 m_position;

	GLfloat m_constant, m_linear, m_exponent;
};