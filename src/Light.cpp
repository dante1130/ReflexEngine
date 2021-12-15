#include "Light.hpp"

Light::Light()
	: m_color(1.0f), m_ambientIntensity(1.0f), m_diffuseIntensity(0.0f)
{}

Light::Light(glm::vec3 color, GLfloat aIntensity, GLfloat dIntensity)
	: m_color(color), m_ambientIntensity(aIntensity), m_diffuseIntensity(dIntensity)
{}

Light::~Light()
{
	
}
