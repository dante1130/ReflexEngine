#include "Material.hpp"

Material::Material()
	: m_specularIntensity(0.0f), m_shininess(0.0f)
{}

Material::Material(GLfloat shine, GLfloat sIntensity)
	: m_specularIntensity(sIntensity), m_shininess(shine)
{}

void Material::UseMaterial(GLuint shininessLoc, GLuint specularIntensityLoc)
{
	glUniform1f(specularIntensityLoc, m_specularIntensity);
	glUniform1f(shininessLoc, m_shininess);
}

Material::~Material()
{

}