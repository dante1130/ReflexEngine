#include "PointLight.hpp"

PointLight::PointLight()
    : Light(),
      m_position(0.0f),
      m_constant(1.0f),
      m_linear(0.0f),
      m_exponent(0.0f) {}

PointLight::PointLight(GLuint shadowWidth, GLuint shadowHeight, GLfloat near,
                       GLfloat far, glm::vec3 color, GLfloat aIntensity,
                       GLfloat dIntensity, glm::vec3 position, GLfloat constant,
                       GLfloat linear, GLfloat exponent)
    : Light(shadowWidth, shadowHeight, color, aIntensity, dIntensity),
      m_position(position),
      m_constant(constant),
      m_linear(linear),
      m_exponent(exponent),
      m_farPlane(far) {
	float aspect =
	    static_cast<float>(shadowWidth) / static_cast<float>(shadowHeight);

	m_lightProj = glm::perspective(glm::radians(90.0f), aspect, near, far);

	m_shadowMap = new OmniShadowMap();
	m_shadowMap->Init(shadowWidth, shadowHeight);
}

void PointLight::UseLight(GLuint ambientColorLoc, GLuint ambientIntensityLoc,
                          GLuint diffuseIntensityLoc, GLuint positionLoc,
                          GLuint constantLoc, GLuint linearLoc,
                          GLuint exponentLoc) const {
	glUniform3f(ambientColorLoc, m_color.x, m_color.y, m_color.z);
	glUniform1f(ambientIntensityLoc, m_ambientIntensity);

	glUniform1f(diffuseIntensityLoc, m_diffuseIntensity);

	glUniform3f(positionLoc, m_position.x, m_position.y, m_position.z);
	glUniform1f(constantLoc, m_constant);
	glUniform1f(linearLoc, m_linear);
	glUniform1f(exponentLoc, m_exponent);
}

std::vector<glm::mat4> PointLight::CalculateLightTransform() const {
	std::vector<glm::mat4> lightMatrices;

	lightMatrices.push_back(m_lightProj *
	                        glm::lookAt(m_position,
	                                    m_position + glm::vec3(1.0, 0.0, 0.0),
	                                    glm::vec3(0.0, -1.0, 0.0)));
	lightMatrices.push_back(m_lightProj *
	                        glm::lookAt(m_position,
	                                    m_position + glm::vec3(-1.0, 0.0, 0.0),
	                                    glm::vec3(0.0, -1.0, 0.0)));

	lightMatrices.push_back(m_lightProj *
	                        glm::lookAt(m_position,
	                                    m_position + glm::vec3(0.0, 1.0, 0.0),
	                                    glm::vec3(0.0, 0.0, 1.0)));
	lightMatrices.push_back(m_lightProj *
	                        glm::lookAt(m_position,
	                                    m_position + glm::vec3(0.0, -1.0, 0.0),
	                                    glm::vec3(0.0, 0.0, -1.0)));

	lightMatrices.push_back(m_lightProj *
	                        glm::lookAt(m_position,
	                                    m_position + glm::vec3(0.0, 0.0, 1.0),
	                                    glm::vec3(0.0, -1.0, 0.0)));
	lightMatrices.push_back(m_lightProj *
	                        glm::lookAt(m_position,
	                                    m_position + glm::vec3(0.0, 0.0, -1.0),
	                                    glm::vec3(0.0, -1.0, 0.0)));

	return lightMatrices;
}

GLfloat PointLight::GetFarPlane() const { return m_farPlane; }

glm::vec3 PointLight::GetPosition() const { return m_position; }

PointLight::~PointLight() {}
