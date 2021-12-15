#pragma once

#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include <vector>

#include <glad/glad.h>

#include "Light.hpp"
#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include "CommonValues.hpp"

class Shader
{
public:
	Shader();

	GLuint GetProjectionLocation() const;
	GLuint GetModelLocation() const;
	GLuint GetViewLocation() const;
	GLuint GetEyePositionLocation() const;
	GLuint GetAmbientIntensityLocation() const;
	GLuint GetAmbientIntensityColor() const;
	GLuint GetDiffuseIntensityLocation() const;
	GLuint GetDirectionLocation() const;
	GLuint GetSpecularIntensityLocation() const;
	GLuint GetShininessLocation() const;

	void SetDirectionalLight(DirectionalLight& dLight);
	void SetPointLights(PointLight* pLight, GLuint lightCount);

	void UseShader();

	void CompileCode(const char* vertexCode, const char* fragmentCode);
	void CompileFile(const char* vertexPath, const char* fragmentPath);

	std::string ReadFile(const char* fileLocation);

	void ClearShader();

	~Shader();

private:
	GLuint m_shaderID;
		
	GLuint uniformProjection, uniformModel, uniformView;

	GLuint uniformEyePosition;
		
	GLuint uniformSpecularIntensity, uniformShininess;

	struct
	{
		GLuint uniformColor;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;
		GLuint uniformDirection;
	} uniformDirectionalLight;

	struct UniformPointLight
	{
		GLuint uniformColor;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformPosition;
		GLuint uniformConstant;
		GLuint uniformLinear;
		GLuint uniformExponent;
	} uniformPointLights[MAX_POINT_LIGHTS];

	GLuint uniformPointLightCount;

	int pointLightCount;

	void AddShader(GLuint program, const char* shaderCode, GLenum shaderType);
	void CompileShader(const char* vertexCode, const char* fragmentCode);
};