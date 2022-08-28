#include "OmniShadowMap.hpp"

bool OmniShadowMap::init(GLuint width, GLuint height) {
	shadow_width_ = width;
	shadow_height_ = height;

	glGenFramebuffers(1, &fbo_);

	glGenTextures(1, &shadow_map_);
	glBindTexture(GL_TEXTURE_CUBE_MAP, shadow_map_);

	for (size_t i = 0; i < 6; ++i) {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT,
		             shadow_width_, shadow_height_, 0, GL_DEPTH_COMPONENT,
		             GL_FLOAT, nullptr);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadow_map_, 0);

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

void OmniShadowMap::write() const {
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo_);
}

void OmniShadowMap::read(GLenum textureUnit) const {
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_CUBE_MAP, shadow_map_);
}
