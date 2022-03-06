#include "Light.hpp"

Light::Light()
	: m_color(1.0f), m_ambientIntensity(1.0f), m_diffuseIntensity(0.0f)
{}

Light::Light(GLfloat shadowWidth, GLfloat shadowHeight, 
			 glm::vec3 color, GLfloat aIntensity, GLfloat dIntensity)
	: m_color(color), m_ambientIntensity(aIntensity), m_diffuseIntensity(dIntensity),
	  m_lightProj(glm::mat4(0.0f)), m_shadowMap(new ShadowMap())
{
	m_shadowMap->Init(shadowWidth, shadowHeight);
}

Light::~Light()
{}


ShadowMap* Light::GetShadowMap() const
{
	return m_shadowMap;
}
