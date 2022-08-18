#pragma once

#include <vector>

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
	Shader() = default;

	GLint GetProjectionLocation() const;
	GLint GetModelLocation() const;
	GLint GetViewLocation() const;
	GLint GetEyePositionLocation() const;
	GLint GetAmbientIntensityLocation() const;
	GLint GetAmbientIntensityColor() const;
	GLint GetDiffuseIntensityLocation() const;
	GLint GetDirectionLocation() const;
	GLint GetSpecularIntensityLocation() const;
	GLint GetShininessLocation() const;
	GLint GetOmniLightPosLocation() const;
	GLint GetFarPlaneLocation() const;
	GLint GetUsingTexture() const;
	GLint get_using_detailmap() const;

	void SetDirectionalLight(const DirectionalLight& dLight);
	void SetPointLights(const PointLight* pLight, GLuint lightCount,
	                    GLuint textureUnit, GLuint offset) const;
	void SetSpotLights(const SpotLight* sLight, GLuint lightCount,
	                   GLuint textureUnit, GLuint offset) const;
	void SetTexture(GLuint textureUnit);
	void SetDirectionalShadowMap(GLuint textureUnit);
	void set_detail_map(GLuint textureUnit);
	void SetDirectionalLightTransform(const glm::mat4& lTransform);
	void SetLightMatrices(const std::vector<glm::mat4>& lightmatrices);

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
	void Validate() const;

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
	GLint m_shaderID = 0u;

	GLint uniformProjection = -1, uniformModel = -1, uniformView = -1;

	GLint uniformEyePosition = -1;

	GLint uniformSpecularIntensity = -1, uniformShininess = -1;

	GLint uniformTexture = -1;

	GLint uniformDirectionalLightTransform = -1;
	GLint uniformDirectionalShadowMap = -1;

	GLint uniform_detailmap = -1;

	GLint uniformOmniLightPos = -1, uniformFarPlane = -1;

	GLint uniformLightMatrices[6];

	GLint uniformSpotLightCount = -1;
	GLint uniformPointLightCount = -1;

	GLint uniformUsingTexture = -1;
	GLint uniform_using_detailmap = -1;

	struct {
		GLint uniformColor = -1;
		GLint uniformAmbientIntensity = -1;
		GLint uniformDiffuseIntensity = -1;
		GLint uniformDirection = -1;
	} uniformDirectionalLight;

	struct {
		GLint uniformColor = -1;
		GLint uniformAmbientIntensity = -1;
		GLint uniformDiffuseIntensity = -1;

		GLint uniformPosition = -1;
		GLint uniformConstant = -1;
		GLint uniformLinear = -1;
		GLuint uniformQuadratic = -1;
	} uniformPointLights[MAX_POINT_LIGHTS];

	struct {
		GLint uniformColor = -1;
		GLint uniformAmbientIntensity = -1;
		GLint uniformDiffuseIntensity = -1;

		GLint uniformPosition = -1;
		GLint uniformConstant = -1;
		GLint uniformLinear = -1;
		GLint uniformQuadratic = -1;

		GLint uniformDirection = -1;
		GLint uniformEdge = -1;
	} uniformSpotLights[MAX_SPOT_LIGHTS];

	struct {
		GLint shadowMap = -1;
		GLint farPlane = -1;
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
