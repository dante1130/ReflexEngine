#include "Shader.hpp"

#include <glad/glad.h>

Shader::Shader() {}

GLuint Shader::GetProjectionLocation() const { return uniformProjection; }

GLuint Shader::GetModelLocation() const { return uniformModel; }

GLuint Shader::GetViewLocation() const { return uniformView; }

GLuint Shader::GetEyePositionLocation() const { return uniformEyePosition; }

GLuint Shader::GetAmbientIntensityLocation() const {
	return uniformDirectionalLight.uniformAmbientIntensity;
}

GLuint Shader::GetAmbientIntensityColor() const {
	return uniformDirectionalLight.uniformColor;
}

GLuint Shader::GetDiffuseIntensityLocation() const {
	return uniformDirectionalLight.uniformDiffuseIntensity;
}

GLuint Shader::GetDirectionLocation() const {
	return uniformDirectionalLight.uniformDirection;
}

GLuint Shader::GetSpecularIntensityLocation() const {
	return uniformSpecularIntensity;
}

GLuint Shader::GetShininessLocation() const { return uniformShininess; }

GLuint Shader::GetOmniLightPosLocation() const { return uniformOmniLightPos; }

GLuint Shader::GetFarPlaneLocation() const { return uniformFarPlane; }

GLuint Shader::GetUsingTexture() const { return uniformUsingTexture; }

GLuint Shader::get_using_detailmap() const { return uniform_using_detailmap; }

void Shader::SetDirectionalLight(const DirectionalLight& dLight) {
	dLight.UseLight(uniformDirectionalLight.uniformColor,
	                uniformDirectionalLight.uniformAmbientIntensity,
	                uniformDirectionalLight.uniformDirection,
	                uniformDirectionalLight.uniformDiffuseIntensity);
}

void Shader::SetPointLights(const PointLight* pLight, GLuint lightCount,
                            GLuint textureUnit, GLuint offset) const {
	if (lightCount > MAX_POINT_LIGHTS) lightCount = MAX_POINT_LIGHTS;

	glUniform1i(uniformPointLightCount, lightCount);

	for (size_t i = 0; i < lightCount; ++i) {
		pLight[i].UseLight(uniformPointLights[i].uniformColor,
		                   uniformPointLights[i].uniformAmbientIntensity,
		                   uniformPointLights[i].uniformDiffuseIntensity,
		                   uniformPointLights[i].uniformPosition,
		                   uniformPointLights[i].uniformConstant,
		                   uniformPointLights[i].uniformLinear,
		                   uniformPointLights[i].uniformQuadratic);

		// pLight[i].GetShadowMap()->Read(GL_TEXTURE0 + textureUnit + i);

		// glUniform1i(uniformOmniShadowMap[i + offset].shadowMap,
		//             textureUnit + i);
		// glUniform1f(uniformOmniShadowMap[i + offset].farPlane,
		//             pLight[i].GetFarPlane());
	}
}

void Shader::SetSpotLights(const SpotLight* sLight, GLuint lightCount,
                           GLuint textureUnit, GLuint offset) const {
	if (lightCount > MAX_SPOT_LIGHTS) lightCount = MAX_SPOT_LIGHTS;

	glUniform1i(uniformSpotLightCount, lightCount);

	for (size_t i = 0; i < lightCount; ++i) {
		sLight[i].UseLight(uniformSpotLights[i].uniformColor,
		                   uniformSpotLights[i].uniformAmbientIntensity,
		                   uniformSpotLights[i].uniformDiffuseIntensity,
		                   uniformSpotLights[i].uniformPosition,
		                   uniformSpotLights[i].uniformDirection,
		                   uniformSpotLights[i].uniformConstant,
		                   uniformSpotLights[i].uniformLinear,
		                   uniformSpotLights[i].uniformQuadratic,
		                   uniformSpotLights[i].uniformEdge);

		// sLight[i].GetShadowMap()->Read(GL_TEXTURE0 + textureUnit + i);

		// glUniform1i(uniformOmniShadowMap[i + offset].shadowMap,
		//             textureUnit + i);
		// glUniform1f(uniformOmniShadowMap[i + offset].farPlane,
		//             sLight[i].GetFarPlane());
	}
}

void Shader::SetTexture(GLuint textureUnit) {
	glUniform1i(uniformTexture, textureUnit);
}

void Shader::SetDirectionalShadowMap(GLuint textureUnit) {
	glUniform1i(uniformDirectionalShadowMap, textureUnit);
}

void Shader::set_detail_map(GLuint textureUnit) {
	glUniform1i(uniform_detailmap, textureUnit);
}

void Shader::SetDirectionalLightTransform(const glm::mat4& lTransform) {
	glUniformMatrix4fv(uniformDirectionalLightTransform, 1, GL_FALSE,
	                   glm::value_ptr(lTransform));
}

void Shader::SetLightMatrices(std::vector<glm::mat4> lightMatrices) {
	for (size_t i = 0; i < 6; ++i) {
		glUniformMatrix4fv(uniformLightMatrices[i], 1, GL_FALSE,
		                   glm::value_ptr(lightMatrices[i]));
	}
}

void Shader::UseShader() const { glUseProgram(m_shaderID); }

void Shader::CompileCode(const char* vertexCode, const char* fragmentCode) {
	CompileShader(vertexCode, fragmentCode);
}

void Shader::CompileFile(const char* vertexPath, const char* fragmentPath) {
	std::string vertexCode = ReadFile(vertexPath);
	std::string fragmentCode = ReadFile(fragmentPath);

	CompileShader(vertexCode.c_str(), fragmentCode.c_str());
}

void Shader::CompileFile(const char* vertexPath, const char* geometryPath,
                         const char* fragmentPath) {
	std::string vertexCode = ReadFile(vertexPath);
	std::string geometryCode = ReadFile(geometryPath);
	std::string fragmentCode = ReadFile(fragmentPath);

	CompileShader(vertexCode.c_str(), geometryCode.c_str(),
	              fragmentCode.c_str());
}

std::string Shader::ReadFile(const char* fileLocation) {
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileStream) {
		std::cout << "Failed to read " << fileLocation << std::endl;
		return "";
	}

	std::string line;
	while (fileStream) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	return content;
}

void Shader::CompileShader(const char* vertexCode, const char* fragmentCode) {
	m_shaderID = glCreateProgram();

	if (!m_shaderID) {
		std::cout << "Error creating shader" << std::endl;
		return;
	}

	AddShader(m_shaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(m_shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	CompileProgram();
}

void Shader::CompileShader(const char* vertexCode, const char* geometryCode,
                           const char* fragmentCode) {
	m_shaderID = glCreateProgram();

	if (!m_shaderID) {
		std::cout << "Error creating shader" << std::endl;
		return;
	}

	AddShader(m_shaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(m_shaderID, geometryCode, GL_GEOMETRY_SHADER);
	AddShader(m_shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	CompileProgram();
}

void Shader::Validate() {
	GLint result = 0;
	GLchar errLog[1024] = {0};

	glValidateProgram(m_shaderID);
	glGetProgramiv(m_shaderID, GL_VALIDATE_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(m_shaderID, sizeof(errLog), nullptr, errLog);
		std::cout << "Error validating program: " << errLog << std::endl;
		return;
	}
}

void Shader::CompileProgram() {
	GLint result = 0;
	GLchar errLog[1024] = {0};

	glLinkProgram(m_shaderID);
	glGetProgramiv(m_shaderID, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(m_shaderID, sizeof(errLog), nullptr, errLog);
		std::cout << "Error linking program: " << errLog << std::endl;
		return;
	}

	uniformModel = glGetUniformLocation(m_shaderID, "model");
	uniformProjection = glGetUniformLocation(m_shaderID, "projection");
	uniformView = glGetUniformLocation(m_shaderID, "view");

	uniformEyePosition = glGetUniformLocation(m_shaderID, "eyePosition");

	uniformUsingTexture = glGetUniformLocation(m_shaderID, "isUsingTexture");
	uniform_using_detailmap =
	    glGetUniformLocation(m_shaderID, "is_using_detailmap");

	uniformDirectionalLight.uniformColor =
	    glGetUniformLocation(m_shaderID, "directionalLight.base.color");
	uniformDirectionalLight.uniformAmbientIntensity = glGetUniformLocation(
	    m_shaderID, "directionalLight.base.ambientIntensity");
	uniformDirectionalLight.uniformDiffuseIntensity = glGetUniformLocation(
	    m_shaderID, "directionalLight.base.diffuseIntensity");
	uniformDirectionalLight.uniformDirection =
	    glGetUniformLocation(m_shaderID, "directionalLight.direction");

	uniformShininess = glGetUniformLocation(m_shaderID, "material.shininess");
	uniformSpecularIntensity =
	    glGetUniformLocation(m_shaderID, "material.specularIntensity");

	uniformPointLightCount =
	    glGetUniformLocation(m_shaderID, "pointLightCount");

	for (size_t i = 0; i < MAX_POINT_LIGHTS; ++i) {
		char locBuff[256] = {'\0'};

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.color", i);
		uniformPointLights[i].uniformColor =
		    glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff),
		         "pointLights[%d].base.ambientIntensity", i);
		uniformPointLights[i].uniformAmbientIntensity =
		    glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff),
		         "pointLights[%d].base.diffuseIntensity", i);
		uniformPointLights[i].uniformDiffuseIntensity =
		    glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].position", i);
		uniformPointLights[i].uniformPosition =
		    glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].constant", i);
		uniformPointLights[i].uniformConstant =
		    glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].linear", i);
		uniformPointLights[i].uniformLinear =
		    glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].exponent", i);
		uniformPointLights[i].uniformQuadratic =
		    glGetUniformLocation(m_shaderID, locBuff);
	}

	uniformSpotLightCount = glGetUniformLocation(m_shaderID, "spotLightCount");

	for (size_t i = 0; i < MAX_SPOT_LIGHTS; ++i) {
		char locBuff[256] = {'\0'};

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.color", i);
		uniformSpotLights[i].uniformColor =
		    glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff),
		         "spotLights[%d].base.base.ambientIntensity", i);
		uniformSpotLights[i].uniformAmbientIntensity =
		    glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff),
		         "spotLights[%d].base.base.diffuseIntensity", i);
		uniformSpotLights[i].uniformDiffuseIntensity =
		    glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.position", i);
		uniformSpotLights[i].uniformPosition =
		    glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.constant", i);
		uniformSpotLights[i].uniformConstant =
		    glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.linear", i);
		uniformSpotLights[i].uniformLinear =
		    glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.exponent", i);
		uniformSpotLights[i].uniformQuadratic =
		    glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].direction", i);
		uniformSpotLights[i].uniformDirection =
		    glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].edge", i);
		uniformSpotLights[i].uniformEdge =
		    glGetUniformLocation(m_shaderID, locBuff);
	}

	uniformTexture = glGetUniformLocation(m_shaderID, "theTexture");
	uniformDirectionalLightTransform =
	    glGetUniformLocation(m_shaderID, "directionalLightTransform");
	uniformDirectionalShadowMap =
	    glGetUniformLocation(m_shaderID, "directionalShadowMap");

	uniform_detailmap = glGetUniformLocation(m_shaderID, "detailmap");

	uniformOmniLightPos = glGetUniformLocation(m_shaderID, "lightPos");
	uniformFarPlane = glGetUniformLocation(m_shaderID, "farPlane");

	for (size_t i = 0; i < 6; ++i) {
		char locBuff[100] = {'\0'};

		snprintf(locBuff, sizeof(locBuff), "lightMatrices[%d]", i);
		uniformLightMatrices[i] = glGetUniformLocation(m_shaderID, locBuff);
	}

	for (size_t i = 0; i < MAX_POINT_LIGHTS + MAX_SPOT_LIGHTS; ++i) {
		char locBuff[100] = {'\0'};

		snprintf(locBuff, sizeof(locBuff), "omniShadowMaps[%d].shadowMap", i);
		uniformOmniShadowMap[i].shadowMap =
		    glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "omniShadowMaps[%d].farPlane", i);
		uniformOmniShadowMap[i].farPlane =
		    glGetUniformLocation(m_shaderID, locBuff);
	}
}

void Shader::AddShader(GLuint program, const char* shaderCode,
                       GLenum shaderType) {
	GLuint shader = glCreateShader(shaderType);

	const GLchar* code[1];
	code[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(shader, 1, code, codeLength);

	glCompileShader(shader);

	GLint result = 0;
	GLchar errLog[1024] = {0};

	glLinkProgram(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(shader, sizeof(errLog), nullptr, errLog);
		std::cout << "Error compiling the " << shaderType
		          << "shader: " << errLog << std::endl;
		return;
	}

	glAttachShader(program, shader);
}

void Shader::ClearShader() {
	std::cout << "Cleaned shader!" << std::endl;

	if (m_shaderID != 0) {
		glDeleteProgram(m_shaderID);
		m_shaderID = 0;
	}

	uniformModel = 0;
	uniformProjection = 0;
}

Shader::~Shader() { ClearShader(); }
