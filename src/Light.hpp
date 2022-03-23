#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ShadowMap.hpp"

class Light {
public:
	Light();
	Light(GLuint shadowWidth, GLuint shadowHeight, glm::vec3 color,
	      GLfloat aIntensity, GLfloat dIntensity);

	ShadowMap* GetShadowMap() const;

	~Light();

protected:
	// Ambient lighting
	glm::vec3 m_color;
	GLfloat m_ambientIntensity;

	// Diffuse lighting
	GLfloat m_diffuseIntensity;

	glm::mat4 m_lightProj;

	ShadowMap* m_shadowMap;
};
