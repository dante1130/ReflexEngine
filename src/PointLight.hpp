#pragma once

#include <vector>
#include "Light.hpp"
#include "OmniShadowMap.hpp"

class PointLight : public Light
{
public:
	PointLight();

	PointLight(GLuint shadowWidth, GLuint shadowHeight,
			   GLfloat near, GLfloat far,
			   glm::vec3 color, GLfloat aIntensity, GLfloat dIntensity, 
			   glm::vec3 position, GLfloat constant, GLfloat linear, 
			   GLfloat exponent);

	void UseLight(GLuint ambientColorLoc, GLuint ambientIntensityLoc, 
				  GLuint diffuseIntensityLoc, GLuint positionLoc,
				  GLuint constantLoc, GLuint linearLoc, GLuint exponentLoc) const;

	std::vector<glm::mat4> CalculateLightTransform() const;

	GLfloat GetFarPlane() const;
	glm::vec3 GetPosition() const;

	~PointLight();

protected:
	glm::vec3 m_position;

	GLfloat m_constant, m_linear, m_exponent;

	GLfloat m_farPlane;
};
