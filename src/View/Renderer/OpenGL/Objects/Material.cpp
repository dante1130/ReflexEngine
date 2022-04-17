#include "Material.hpp"

Reflex::Material::Material() : m_specularIntensity(0.0f), m_shininess(0.0f) {}

Reflex::Material::Material(GLfloat shine, GLfloat sIntensity)
    : m_specularIntensity(sIntensity), m_shininess(shine) {}

void Reflex::Material::UseMaterial(GLuint shininessLoc,
                                   GLuint specularIntensityLoc) {
	glUniform1f(specularIntensityLoc, m_specularIntensity);
	glUniform1f(shininessLoc, m_shininess);
}

float Reflex::Material::getSpecIntensity() { return m_specularIntensity; }
float Reflex::Material::getShininess() { return m_shininess; }
