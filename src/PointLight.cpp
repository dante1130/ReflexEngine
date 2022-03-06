#include "PointLight.hpp"

PointLight::PointLight()
	: Light(), m_position(0.0f), m_constant(1.0f), m_linear(0.0f), m_exponent(0.0f)
{}

PointLight::PointLight(glm::vec3 color, GLfloat aIntensity, GLfloat dIntensity,
	glm::vec3 position, GLfloat constant, GLfloat linear, GLfloat exponent)
	: Light(1024.0f, 1024.0f, color, aIntensity, dIntensity), m_position(position),
	m_constant(constant), m_linear(linear), m_exponent(exponent)
{}

void PointLight::UseLight(GLuint ambientColorLoc, GLuint ambientIntensityLoc,
						  GLuint diffuseIntensityLoc, GLuint positionLoc, 
						  GLuint constantLoc, GLuint linearLoc, GLuint exponentLoc) const
{
	glUniform3f(ambientColorLoc, m_color.x, m_color.y, m_color.z);
	glUniform1f(ambientIntensityLoc, m_ambientIntensity);

	glUniform1f(diffuseIntensityLoc, m_diffuseIntensity);

	glUniform3f(positionLoc, m_position.x, m_position.y, m_position.z);
	glUniform1f(constantLoc, m_constant);
	glUniform1f(linearLoc, m_linear);
	glUniform1f(exponentLoc, m_exponent);
}

PointLight::~PointLight()
{}