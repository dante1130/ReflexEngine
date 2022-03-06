#include "DirectionalLight.hpp"

DirectionalLight::DirectionalLight() 
	: Light(), m_direction(glm::vec3(0.0f, -1.0f, 0.0f))
{}

DirectionalLight::DirectionalLight(GLfloat shadowWidth, GLfloat shadowHeight, glm::vec3 color, GLfloat aIntensity, glm::vec3 direction, GLfloat dIntensity)
	: Light(shadowWidth, shadowHeight, color, aIntensity, dIntensity)
{
	m_direction = direction;

	m_lightProj = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 100.0f);
}

void DirectionalLight::UseLight(GLuint ambientColorLoc, GLuint ambientIntensityLoc, GLuint directionLoc, GLuint diffuseIntensityLoc) const
{
	glUniform3f(ambientColorLoc, m_color.x, m_color.y, m_color.z);
	glUniform1f(ambientIntensityLoc, m_ambientIntensity);

	glUniform3f(directionLoc, m_direction.x, m_direction.y, m_direction.z);
	glUniform1f(diffuseIntensityLoc, m_diffuseIntensity);
}

glm::mat4 DirectionalLight::CalculateLightTransform() const
{
	return m_lightProj * glm::lookAt(-m_direction, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

DirectionalLight::~DirectionalLight()
{

}
