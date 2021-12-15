#include "DirectionalLight.hpp"

DirectionalLight::DirectionalLight() 
	: Light(), m_direction(glm::vec3(0.0f, -1.0f, 0.0f))
{}

DirectionalLight::DirectionalLight(glm::vec3 color, GLfloat aIntensity, glm::vec3 direction, GLfloat dIntensity)
	: Light(color, aIntensity, dIntensity), m_direction(direction)
{}

void DirectionalLight::UseLight(GLuint ambientColorLoc, GLuint ambientIntensityLoc, GLuint directionLoc, GLuint diffuseIntensityLoc)
{
	glUniform3f(ambientColorLoc, m_color.x, m_color.y, m_color.z);
	glUniform1f(ambientIntensityLoc, m_ambientIntensity);

	glUniform3f(directionLoc, m_direction.x, m_direction.y, m_direction.z);
	glUniform1f(diffuseIntensityLoc, m_diffuseIntensity);
}

DirectionalLight::~DirectionalLight()
{

}
