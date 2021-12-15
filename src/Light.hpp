#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

class Light
{
public:
	Light();
	Light(glm::vec3 color, GLfloat aIntensity, GLfloat dIntensity);

	~Light();

protected:
	// Ambient lighting
	glm::vec3 m_color;
	GLfloat m_ambientIntensity;

	// Diffuse lighting
	GLfloat m_diffuseIntensity;
};
