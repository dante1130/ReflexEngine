#pragma once

#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include <vector>

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

#include "Light.hpp"
#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include "SpotLight.hpp"
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

	void SetDirectionalLight(const DirectionalLight& dLight);
	void SetPointLights(PointLight* pLight, GLuint lightCount);
	void SetSpotLights(SpotLight* sLight, GLuint lightCount);
	void SetTexture(GLuint textureUnit);
	void SetDirectionalShadowMap(GLuint textureUnit);
	void SetDirectionalLightTransform(const glm::mat4& lTransform);

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

	GLuint uniformTexture;

	GLuint uniformDirectionalLightTransform, uniformDirectionalShadowMap;

	GLuint uniformSpotLightCount;
	GLuint uniformPointLightCount;

	int pointLightCount;
	int spotLightCount;

	struct
	{
		GLuint uniformColor;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;
		GLuint uniformDirection;
	} uniformDirectionalLight;

	struct
	{
		GLuint uniformColor;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformPosition;
		GLuint uniformConstant;
		GLuint uniformLinear;
		GLuint uniformExponent;
	} uniformPointLights[MAX_POINT_LIGHTS];

	struct
	{
		GLuint uniformColor;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformPosition;
		GLuint uniformConstant;
		GLuint uniformLinear;
		GLuint uniformExponent;

		GLuint uniformDirection;
		GLuint uniformEdge;
	} uniformSpotLights[MAX_SPOT_LIGHTS];

	void AddShader(GLuint program, const char* shaderCode, GLenum shaderType);
	void CompileShader(const char* vertexCode, const char* fragmentCode);
};
