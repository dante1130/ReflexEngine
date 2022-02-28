#pragma once

#include "PointLight.hpp"

class SpotLight : public PointLight
{
public:
	SpotLight();
	
	SpotLight(glm::vec3 color, GLfloat aIntensity, GLfloat dIntensity, glm::vec3 position, glm::vec3 direction, GLfloat constant, GLfloat linear, GLfloat exponent, GLfloat edge);

	void UseLight(GLuint ambientColorLoc, GLuint ambientIntensityLoc,
		GLuint diffuseIntensityLoc, GLuint positionLoc, GLuint directionLoc,
		GLuint constantLoc, GLuint linearLoc, GLuint exponentLoc, GLuint edgeLoc);

	void SetFlash(glm::vec3 pos, glm::vec3 dir);

private:
	glm::vec3 m_direction;

	GLfloat m_edge, m_procEdge;
};