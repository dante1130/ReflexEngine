#include "SpotLight.hpp"

SpotLight::SpotLight() 
	: PointLight(), m_direction(glm::vec3(0.0f, -1.0f, 0.0f)), m_procEdge(0.0f)
{}

SpotLight::SpotLight(GLuint shadowWidth, GLuint shadowHeight,
					 GLfloat near, GLfloat far, 
					 glm::vec3 color, GLfloat aIntensity, GLfloat dIntensity, 
					 glm::vec3 position, glm::vec3 direction, GLfloat constant, 
					 GLfloat linear, GLfloat exponent, GLfloat edge)
	: PointLight(shadowWidth, shadowHeight, near, far, color, aIntensity, dIntensity, position, constant, linear, exponent),
		m_direction(glm::normalize(direction)), m_procEdge(cosf(glm::radians(edge)))
{}


void SpotLight::UseLight(GLuint ambientColorLoc, GLuint ambientIntensityLoc,
	GLuint diffuseIntensityLoc, GLuint positionLoc, GLuint directionLoc,
	GLuint constantLoc, GLuint linearLoc, GLuint exponentLoc, GLuint edgeLoc) const
{
	glUniform3f(ambientColorLoc, m_color.x, m_color.y, m_color.z);
	glUniform1f(ambientIntensityLoc, m_ambientIntensity);

	glUniform1f(diffuseIntensityLoc, m_diffuseIntensity);

	glUniform3f(positionLoc, m_position.x, m_position.y, m_position.z);
	glUniform1f(constantLoc, m_constant);
	glUniform1f(linearLoc, m_linear);
	glUniform1f(exponentLoc, m_exponent);

	glUniform3f(directionLoc, m_direction.x, m_direction.y, m_direction.z);
	glUniform1f(edgeLoc, m_procEdge);
}

void SpotLight::SetFlash(glm::vec3 pos, glm::vec3 dir)
{
	m_position = pos;
	m_direction = dir;
}
