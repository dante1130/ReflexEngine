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

/**
 * @class Shader
 * @brief A shader program
 * @todo Refactor getters and setters.
 */
class Shader {
public:
	/**
	 * @brief Construct a new Shader object
	 */
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
	GLuint GetOmniLightPosLocation() const;
	GLuint GetFarPlaneLocation() const;
	GLuint GetUsingTexture() const;

	void SetDirectionalLight(const DirectionalLight& dLight);
	void SetPointLights(PointLight* pLight, GLuint lightCount,
	                    GLuint textureUnit, GLuint offset);
	void SetSpotLights(SpotLight* sLight, GLuint lightCount, GLuint textureUnit,
	                   GLuint offset);
	void SetTexture(GLuint textureUnit);
	void SetDirectionalShadowMap(GLuint textureUnit);
	void SetDirectionalLightTransform(const glm::mat4& lTransform);
	void SetLightMatrices(std::vector<glm::mat4> lightmatrices);

	/**
	 * @brief Use the current shader.
	 */
	void UseShader() const;

	/**
	 * @brief Compiles the shader code.
	 *
	 * @param vertexCode
	 * @param fragmentCode
	 */
	void CompileCode(const char* vertexCode, const char* fragmentCode);

	/**
	 * @brief Reads in a shader file and compiles the code.
	 *
	 * @param vertexPath
	 * @param fragmentPath
	 */
	void CompileFile(const char* vertexPath, const char* fragmentPath);

	/**
	 * @brief Reads in a shader file and compiles the code.
	 *
	 * @param vertexPath
	 * @param geometryPath
	 * @param fragmentPath
	 */
	void CompileFile(const char* vertexPath, const char* geometryPath,
	                 const char* fragmentPath);

	/**
	 * @brief Validates the shader.
	 */
	void Validate();

	/**
	 * @brief Read a shader file and return the code.
	 *
	 * @param fileLocation
	 * @return std::string
	 */
	std::string ReadFile(const char* fileLocation);

	/**
	 * @brief Clears the shader.
	 */
	void ClearShader();

	/**
	 * @brief Destroy the Shader object
	 */
	~Shader();

private:
	/// The unique id of the shader.
	GLuint m_shaderID;

	GLuint uniformProjection, uniformModel, uniformView;

	GLuint uniformEyePosition;

	GLuint uniformSpecularIntensity, uniformShininess;

	GLuint uniformTexture;

	GLuint uniformDirectionalLightTransform, uniformDirectionalShadowMap;

	GLuint uniformOmniLightPos, uniformFarPlane;

	GLuint uniformLightMatrices[6];

	GLuint uniformSpotLightCount;
	GLuint uniformPointLightCount;

	GLuint uniformUsingTexture;

	int pointLightCount;
	int spotLightCount;

	struct {
		GLuint uniformColor;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;
		GLuint uniformDirection;
	} uniformDirectionalLight;

	struct {
		GLuint uniformColor;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformPosition;
		GLuint uniformConstant;
		GLuint uniformLinear;
		GLuint uniformExponent;
	} uniformPointLights[MAX_POINT_LIGHTS];

	struct {
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

	struct {
		GLuint shadowMap;
		GLfloat farPlane;
	} uniformOmniShadowMap[MAX_POINT_LIGHTS + MAX_SPOT_LIGHTS];

	/**
	 * @brief Adds a new type of shader to the program.
	 *
	 * @param program
	 * @param shaderCode
	 * @param shaderType
	 */
	void AddShader(GLuint program, const char* shaderCode, GLenum shaderType);

	/**
	 * @brief Compiles a vertex and fragment shader.
	 *
	 * @param vertexCode
	 * @param fragmentCode
	 */
	void CompileShader(const char* vertexCode, const char* fragmentCode);

	/**
	 * @brief Compiles a vertex, geometry and fragment shader.
	 *
	 * @param vertexCode
	 * @param geometryCode
	 * @param fragmentCode
	 */
	void CompileShader(const char* vertexCode, const char* geometryCode,
	                   const char* fragmentCode);

	/**
	 * @brief Compiles the shader program.
	 */
	void CompileProgram();
};
