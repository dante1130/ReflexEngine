#pragma once

#include <iostream>

#include <glad/glad.h>

class ShadowMap
{
public:
	ShadowMap();

	virtual bool Init(GLuint width, GLuint height);

	virtual void Write();

	virtual void Read(GLenum textureUnit);

	GLuint GetShadowWidth() const;
	GLuint GetShadowHeight() const;

	virtual ~ShadowMap();

protected:
	GLuint m_fbo, m_shadowMap;
	GLuint m_shadowWidth, m_shadowHeight;
};
