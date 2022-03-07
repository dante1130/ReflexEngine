#include "OmniShadowMap.hpp"

OmniShadowMap::OmniShadowMap()
{
}

bool OmniShadowMap::Init(GLuint width, GLuint height)
{
	m_shadowWidth = width;
	m_shadowHeight = height;

	glGenFramebuffers(1, &m_fbo);

	glGenTextures(1, &m_shadowMap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_shadowMap);

	for (size_t i = 0; i < 6; ++i) 
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT,
					 m_shadowWidth, m_shadowHeight, 0, GL_DEPTH_COMPONENT,
					 GL_FLOAT, nullptr);
	}
		
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_shadowMap, 0);

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Framebuffer error: " << status << '\n';
		return false;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return true;
}

void OmniShadowMap::Write()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
}

void OmniShadowMap::Read(GLenum textureUnit)
{
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_shadowMap);
}

OmniShadowMap::~OmniShadowMap()
{
}
