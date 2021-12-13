#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

class Light
{
public:
	Light();
	Light(glm::vec3 color, GLfloat aIntensity, glm::vec3 direction, GLfloat dIntensity);

	void UseLight(GLfloat ambientIntensityLoc, GLfloat ambientColorLoc, GLfloat directionLoc, GLfloat diffuseIntensityLoc);

	~Light();

private:
	// Ambient lighting
	glm::vec3 m_color;
	GLfloat m_ambientIntensity;

	// Diffuse lighting
	glm::vec3 m_direction;
	GLfloat m_diffuseIntensity;
};
