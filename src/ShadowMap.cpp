#include "ShadowMap.hpp"

ShadowMap::ShadowMap() : m_fbo(0u), m_shadowMap(0u) {}

bool ShadowMap::Init(GLuint width, GLuint height) {
	m_shadowWidth = width;
	m_shadowHeight = height;

	glGenFramebuffers(1, &m_fbo);

	glGenTextures(1, &m_shadowMap);
	glBindTexture(GL_TEXTURE_2D, m_shadowMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_shadowWidth,
	             m_shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	float borderColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
	                       m_shadowMap, 0);

	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (status != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "Framebuffer error: " << status << '\n';
		return false;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return true;
}

void ShadowMap::Write() { glBindFramebuffer(GL_FRAMEBUFFER, m_fbo); }

void ShadowMap::Read(GLenum textureUnit) {
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, m_shadowMap);
}

GLuint ShadowMap::GetShadowWidth() const { return m_shadowWidth; }

GLuint ShadowMap::GetShadowHeight() const { return m_shadowHeight; }

ShadowMap::~ShadowMap() {
	if (m_fbo) glDeleteFramebuffers(1, &m_fbo);

	if (m_shadowMap) glDeleteTextures(1, &m_shadowMap);
}
