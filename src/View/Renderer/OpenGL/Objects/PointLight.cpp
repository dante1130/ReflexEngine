#include "PointLight.hpp"

PointLight::PointLight(GLuint shadow_width, GLuint shadow_height, GLfloat near,
                       GLfloat far, glm::vec3 color, GLfloat aIntensity,
                       GLfloat dIntensity, glm::vec3 position, GLfloat constant,
                       GLfloat linear, GLfloat quadratic)
    : Light(color, aIntensity, dIntensity),
      far_plane_(far),
      m_position(position),
      m_constant(constant),
      m_linear(linear),
      m_quadratic(quadratic) {
	float aspect =
	    static_cast<float>(shadow_width) / static_cast<float>(shadow_height);

	light_projection_ =
	    glm::perspective(glm::radians(90.0f), aspect, near, far);

	omni_shadow_map_.init(shadow_width, shadow_height);
}

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

std::vector<glm::mat4> PointLight::calculate_light_transforms() const {
	std::vector<glm::mat4> light_matrices;

	// +x, -x
	light_matrices.emplace_back(
	    light_projection_ *
	    glm::lookAt(m_position, m_position + glm::vec3(1.0f, 0.0f, 0.0f),
	                glm::vec3(0.0f, -1.0f, 0.0f)));
	light_matrices.emplace_back(
	    light_projection_ *
	    glm::lookAt(m_position, m_position + glm::vec3(-1.0f, 0.0f, 0.0f),
	                glm::vec3(0.0f, -1.0f, 0.0f)));

	// +y, -y
	light_matrices.emplace_back(
	    light_projection_ *
	    glm::lookAt(m_position, m_position + glm::vec3(0.0f, 1.0f, 0.0f),
	                glm::vec3(0.0f, 0.0f, 1.0f)));
	light_matrices.emplace_back(
	    light_projection_ *
	    glm::lookAt(m_position, m_position + glm::vec3(0.0f, -1.0f, 0.0f),
	                glm::vec3(0.0f, 0.0f, -1.0f)));

	// +z, -z
	light_matrices.emplace_back(
	    light_projection_ *
	    glm::lookAt(m_position, m_position + glm::vec3(0.0f, 0.0f, 1.0f),
	                glm::vec3(0.0f, -1.0f, 0.0f)));
	light_matrices.emplace_back(
	    light_projection_ *
	    glm::lookAt(m_position, m_position + glm::vec3(0.0f, 0.0f, -1.0f),
	                glm::vec3(0.0f, -1.0f, 0.0f)));

	return light_matrices;
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

const glm::vec3& PointLight::get_position() const { return m_position; }

const OmniShadowMap& PointLight::get_shadow_map() const {
	return omni_shadow_map_;
}

GLfloat PointLight::get_far_plane() const { return far_plane_; }
