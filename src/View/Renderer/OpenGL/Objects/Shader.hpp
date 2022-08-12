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
	GLuint get_using_detailmap() const;

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
	GLuint m_shaderID = 0u;

	GLuint uniformProjection = 0u, uniformModel = 0u, uniformView = 0u;

	GLuint uniformEyePosition = 0u;

	GLuint uniformSpecularIntensity = 0u, uniformShininess = 0u;

	GLuint uniformTexture = 0u;

	GLuint uniformDirectionalLightTransform = 0u,
	       uniformDirectionalShadowMap = 0u;

	GLuint uniform_detailmap = 0u;

	GLuint uniformOmniLightPos = 0u, uniformFarPlane = 0u;

	GLuint uniformLightMatrices[6];

	GLuint uniformSpotLightCount = 0u;
	GLuint uniformPointLightCount = 0u;

	GLuint uniformUsingTexture = 0u;
	GLuint uniform_using_detailmap = 0u;

	struct {
		GLuint uniformColor = 0u;
		GLuint uniformAmbientIntensity = 0u;
		GLuint uniformDiffuseIntensity = 0u;
		GLuint uniformDirection = 0u;
	} uniformDirectionalLight;

	struct {
		GLuint uniformColor = 0u;
		GLuint uniformAmbientIntensity = 0u;
		GLuint uniformDiffuseIntensity = 0u;

		GLuint uniformPosition = 0u;
		GLuint uniformConstant = 0u;
		GLuint uniformLinear = 0u;
		GLuint uniformQuadratic = 0u;
	} uniformPointLights[MAX_POINT_LIGHTS];

	struct {
		GLuint uniformColor = 0u;
		GLuint uniformAmbientIntensity = 0u;
		GLuint uniformDiffuseIntensity = 0u;

		GLuint uniformPosition = 0u;
		GLuint uniformConstant = 0u;
		GLuint uniformLinear = 0u;
		GLuint uniformQuadratic = 0u;

		GLuint uniformDirection = 0u;
		GLuint uniformEdge = 0u;
	} uniformSpotLights[MAX_SPOT_LIGHTS];

	struct {
		GLuint shadowMap = 0u;
		GLuint farPlane = 0u;
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
