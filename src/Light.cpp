#include "Light.hpp"

Light::Light()
	: m_color(1.0f), m_ambientIntensity(1.0f),
	m_direction(glm::vec3(0.0f, -1.0f, 0.0f)), m_diffuseIntensity(0.0f)
{}

Light::Light(glm::vec3 color, GLfloat aIntensity, glm::vec3 direction, GLfloat dIntensity)
	: m_color(color), m_ambientIntensity(aIntensity), 
	m_direction(direction), m_diffuseIntensity(dIntensity)
{}

void Light::UseLight(GLfloat ambientIntensityLoc, GLfloat ambientColorLoc, GLfloat directionLoc, GLfloat diffuseIntensityLoc)
{
	glUniform3f(ambientColorLoc, m_color.x, m_color.y, m_color.z);
	glUniform1f(ambientIntensityLoc, m_ambientIntensity);

	glUniform3f(directionLoc, m_direction.x, m_direction.y, m_direction.z);
	glUniform1f(diffuseIntensityLoc, m_diffuseIntensity);
}

Light::~Light()
{
	
}
