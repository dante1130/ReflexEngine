#pragma once

#include <glad/glad.h>

class Material {
public:
	Material();
	Material(GLfloat shine, GLfloat sIntensity);

	void UseMaterial(GLuint shininessLoc, GLuint specularIntensityLoc);

private:
	GLfloat m_specularIntensity;
	GLfloat m_shininess;
};
