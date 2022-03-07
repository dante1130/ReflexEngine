#pragma once

#include "ShadowMap.hpp"

class OmniShadowMap : public ShadowMap
{
public:
	OmniShadowMap();

	bool Init(GLuint width, GLuint height);

	void Write();

	void Read(GLenum textureUnit);

	~OmniShadowMap();

private:
};