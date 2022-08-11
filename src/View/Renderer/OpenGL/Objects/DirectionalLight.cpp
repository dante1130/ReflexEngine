#include "DirectionalLight.hpp"

#include <glm/gtc/matrix_transform.hpp>

DirectionalLight::DirectionalLight() {
	light_projection_ = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 100.0f);
}

DirectionalLight::DirectionalLight(GLuint shadow_width, GLuint shadow_height,
                                   glm::vec3 color, GLfloat aIntensity,
                                   glm::vec3 direction, GLfloat dIntensity)
    : Light(shadow_width, shadow_height, color, aIntensity, dIntensity),
      m_direction(direction) {
	light_projection_ = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 100.0f);
}

void DirectionalLight::set_directional_light(glm::vec3 color,
                                             GLfloat aIntensity,
                                             glm::vec3 direction,
                                             GLfloat dIntensity) {
	m_color = color;
	m_ambientIntensity = aIntensity;
	m_direction = direction;
	m_diffuseIntensity = dIntensity;
}

glm::mat4 DirectionalLight::calculate_light_transform() const {
	return light_projection_ * glm::lookAt(-m_direction,
	                                       glm::vec3(0.0f, 0.0f, 0.0f),
	                                       glm::vec3(0.0f, 1.0f, 0.0f));
}

void DirectionalLight::UseLight(GLuint ambientColorLoc,
                                GLuint ambientIntensityLoc, GLuint directionLoc,
                                GLuint diffuseIntensityLoc) const {
	glUniform3f(ambientColorLoc, m_color.x, m_color.y, m_color.z);
	glUniform1f(ambientIntensityLoc, m_ambientIntensity);

	glUniform3f(directionLoc, m_direction.x, m_direction.y, m_direction.z);
	glUniform1f(diffuseIntensityLoc, m_diffuseIntensity);
}
