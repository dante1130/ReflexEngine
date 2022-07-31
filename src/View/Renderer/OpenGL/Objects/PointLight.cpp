#include "PointLight.hpp"

PointLight::PointLight(glm::vec3 color, GLfloat aIntensity, GLfloat dIntensity,
                       glm::vec3 position, GLfloat constant, GLfloat linear,
                       GLfloat quadratic)
    : Light(color, aIntensity, dIntensity),
      m_position(position),
      m_constant(constant),
      m_linear(linear),
      m_quadratic(quadratic) {}

void PointLight::UseLight(GLuint ambientColorLoc, GLuint ambientIntensityLoc,
                          GLuint diffuseIntensityLoc, GLuint positionLoc,
                          GLuint constantLoc, GLuint linearLoc,
                          GLuint quadraticLoc) const {
	glUniform3f(ambientColorLoc, m_color.x, m_color.y, m_color.z);
	glUniform1f(ambientIntensityLoc, m_ambientIntensity);
	glUniform1f(diffuseIntensityLoc, m_diffuseIntensity);

	glUniform3f(positionLoc, m_position.x, m_position.y, m_position.z);
	glUniform1f(constantLoc, m_constant);
	glUniform1f(linearLoc, m_linear);
	glUniform1f(quadraticLoc, m_quadratic);
}

void PointLight::set_point_light(glm::vec3 color, GLfloat aIntensity,
                                 GLfloat dIntensity, glm::vec3 position,
                                 GLfloat constant, GLfloat linear,
                                 GLfloat quadratic) {
	m_color = color;
	m_ambientIntensity = aIntensity;
	m_diffuseIntensity = dIntensity;
	m_position = position;
	m_constant = constant;
	m_linear = linear;
	m_quadratic = quadratic;
}

glm::vec3 PointLight::GetPosition() const { return m_position; }