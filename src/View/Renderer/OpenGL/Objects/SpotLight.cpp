#include "SpotLight.hpp"

SpotLight::SpotLight(GLuint shadow_width, GLuint shadow_height,
                     const glm::mat4& light_projection, GLfloat far_plane,
                     const glm::vec3& color, GLfloat aIntensity,
                     GLfloat dIntensity, const glm::vec3& position,
                     const glm::vec3& direction, GLfloat constant,
                     GLfloat linear, GLfloat quadratic, GLfloat edge)
    : PointLight(shadow_width, shadow_height, light_projection, far_plane,
                 color, aIntensity, dIntensity, position, constant, linear,
                 quadratic),
      m_direction(glm::normalize(direction)),
      m_procEdge(cosf(glm::radians(edge))) {}

void SpotLight::set_spot_light(glm::vec3 color, GLfloat aIntensity,
                               GLfloat dIntensity, glm::vec3 position,
                               glm::vec3 direction, GLfloat constant,
                               GLfloat linear, GLfloat quadratic,
                               GLfloat edge) {
	PointLight::set_point_light(color, aIntensity, dIntensity, position,
	                            constant, linear, quadratic);
	m_direction = glm::normalize(direction);
	m_procEdge = cosf(glm::radians(edge));
}

void SpotLight::UseLight(GLuint ambientColorLoc, GLuint ambientIntensityLoc,
                         GLuint diffuseIntensityLoc, GLuint positionLoc,
                         GLuint directionLoc, GLuint constantLoc,
                         GLuint linearLoc, GLuint quadraticLoc,
                         GLuint edgeLoc) const {
	glUniform3f(ambientColorLoc, m_color.x, m_color.y, m_color.z);
	glUniform1f(ambientIntensityLoc, m_ambientIntensity);

	glUniform1f(diffuseIntensityLoc, m_diffuseIntensity);

	glUniform3f(positionLoc, m_position.x, m_position.y, m_position.z);
	glUniform1f(constantLoc, m_constant);
	glUniform1f(linearLoc, m_linear);
	glUniform1f(quadraticLoc, m_quadratic);

	glUniform3f(directionLoc, m_direction.x, m_direction.y, m_direction.z);
	glUniform1f(edgeLoc, m_procEdge);
}
