#include "Shader.hpp"

Shader::Shader()
	: m_shaderID(0), uniformModel(0), uniformProjection(0), pointLightCount(0), spotLightCount(0)
{}

GLuint Shader::GetProjectionLocation() const
{
	return uniformProjection;
}

GLuint Shader::GetModelLocation() const
{
	return uniformModel;
}

GLuint Shader::GetViewLocation() const
{
	return uniformView;
}

GLuint Shader::GetEyePositionLocation() const
{
	return uniformEyePosition;
}

GLuint Shader::GetAmbientIntensityLocation() const
{
	return uniformDirectionalLight.uniformAmbientIntensity;
}

GLuint Shader::GetAmbientIntensityColor() const
{
	return uniformDirectionalLight.uniformColor;
}

GLuint Shader::GetDiffuseIntensityLocation() const
{
	return uniformDirectionalLight.uniformDiffuseIntensity;
}

GLuint Shader::GetDirectionLocation() const
{
	return uniformDirectionalLight.uniformDirection;
}

GLuint Shader::GetSpecularIntensityLocation() const
{
	return uniformSpecularIntensity;
}

GLuint Shader::GetShininessLocation() const
{
	return uniformShininess;
}

void Shader::SetDirectionalLight(DirectionalLight& dLight)
{
	dLight.UseLight(uniformDirectionalLight.uniformColor,
					uniformDirectionalLight.uniformAmbientIntensity,
					uniformDirectionalLight.uniformDirection,
					uniformDirectionalLight.uniformDiffuseIntensity);
}

void Shader::SetPointLights(PointLight* pLight, GLuint lightCount)
{
	if (lightCount > MAX_POINT_LIGHTS) lightCount = MAX_POINT_LIGHTS;

	glUniform1i(uniformPointLightCount, lightCount);

	for (size_t i = 0; i < lightCount; ++i)
	{
		pLight[i].UseLight(uniformPointLights[i].uniformColor,
							uniformPointLights[i].uniformAmbientIntensity,
							uniformPointLights[i].uniformDiffuseIntensity,
							uniformPointLights[i].uniformPosition,
							uniformPointLights[i].uniformConstant,
							uniformPointLights[i].uniformLinear,
							uniformPointLights[i].uniformExponent);
	}
}

void Shader::SetSpotLights(SpotLight* sLight, GLuint lightCount)
{
	if (lightCount > MAX_SPOT_LIGHTS) lightCount = MAX_SPOT_LIGHTS;

	glUniform1i(uniformSpotLightCount, lightCount);

	for (size_t i = 0; i < lightCount; ++i)
	{
		sLight[i].UseLight(uniformSpotLights[i].uniformColor,
							uniformSpotLights[i].uniformAmbientIntensity,
							uniformSpotLights[i].uniformDiffuseIntensity,
							uniformSpotLights[i].uniformPosition,
							uniformSpotLights[i].uniformDirection,
							uniformSpotLights[i].uniformConstant,
							uniformSpotLights[i].uniformLinear,
							uniformSpotLights[i].uniformExponent,
							uniformSpotLights[i].uniformEdge);
	}
}

void Shader::UseShader()
{
	glUseProgram(m_shaderID);
}

void Shader::CompileCode(const char* vertexCode, const char* fragmentCode)
{
	CompileShader(vertexCode, fragmentCode);
}

void Shader::CompileFile(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode = ReadFile(vertexPath);
	std::string fragmentCode = ReadFile(fragmentPath);

	CompileShader(vertexCode.c_str(), fragmentCode.c_str());
}

std::string Shader::ReadFile(const char* fileLocation)
{
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileStream)
	{
		std::cout << "Failed to read " << fileLocation << std::endl;
		return "";
	}

	std::string line = "";
	while (fileStream)
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	return content;
}

void Shader::CompileShader(const char* vertexCode, const char* fragmentCode)
{
	m_shaderID = glCreateProgram();

	if (!m_shaderID)
	{
		std::cout << "Error creating shader" << std::endl;
		return;
	}

	AddShader(m_shaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(m_shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar errLog[1024] = { 0 };

	glLinkProgram(m_shaderID);
	glGetProgramiv(m_shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(m_shaderID, sizeof(errLog), NULL, errLog);
		std::cout << "Error linking program: " << errLog << std::endl;
		return;
	}

	glValidateProgram(m_shaderID);
	glGetProgramiv(m_shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(m_shaderID, sizeof(errLog), NULL, errLog);
		std::cout << "Error validating program: " << errLog << std::endl;
		return;
	}

	uniformModel = glGetUniformLocation(m_shaderID, "model");
	uniformProjection = glGetUniformLocation(m_shaderID, "projection");
	uniformView = glGetUniformLocation(m_shaderID, "view");

	uniformEyePosition = glGetUniformLocation(m_shaderID, "eyePosition");

	uniformDirectionalLight.uniformColor = glGetUniformLocation(m_shaderID, "directionalLight.base.color");
	uniformDirectionalLight.uniformAmbientIntensity = glGetUniformLocation(m_shaderID, "directionalLight.base.ambientIntensity");

	uniformDirectionalLight.uniformDirection = glGetUniformLocation(m_shaderID, "directionalLight.direction");
	uniformDirectionalLight.uniformDiffuseIntensity = glGetUniformLocation(m_shaderID, "directionalLight.base.diffuseIntensity");

	uniformShininess = glGetUniformLocation(m_shaderID, "material.shininess");
	uniformSpecularIntensity = glGetUniformLocation(m_shaderID, "material.specularIntensity");

	uniformPointLightCount = glGetUniformLocation(m_shaderID, "pointLightCount");

	for (size_t i = 0; i < MAX_POINT_LIGHTS; ++i)
	{
		char locBuff[100] = { '\0' };

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.color", i);
		uniformPointLights[i].uniformColor = glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.ambientIntensity", i);
		uniformPointLights[i].uniformAmbientIntensity = glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.diffuseIntensity", i);
		uniformPointLights[i].uniformDiffuseIntensity = glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].position", i);
		uniformPointLights[i].uniformPosition = glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].constant", i);
		uniformPointLights[i].uniformConstant = glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].linear", i);
		uniformPointLights[i].uniformLinear = glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].exponent", i);
		uniformPointLights[i].uniformExponent = glGetUniformLocation(m_shaderID, locBuff);
	}

	uniformSpotLightCount = glGetUniformLocation(m_shaderID, "spotLightCount");

	for (size_t i = 0; i < MAX_SPOT_LIGHTS; ++i)
	{
		char locBuff[100] = { '\0' };

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.color", i);
		uniformSpotLights[i].uniformColor = glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.ambientIntensity", i);
		uniformSpotLights[i].uniformAmbientIntensity = glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.diffuseIntensity", i);
		uniformSpotLights[i].uniformDiffuseIntensity = glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.position", i);
		uniformSpotLights[i].uniformPosition = glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.constant", i);
		uniformSpotLights[i].uniformConstant = glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.linear", i);
		uniformSpotLights[i].uniformLinear = glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.exponent", i);
		uniformSpotLights[i].uniformExponent = glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].direction", i);
		uniformSpotLights[i].uniformDirection = glGetUniformLocation(m_shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].edge", i);
		uniformSpotLights[i].uniformEdge = glGetUniformLocation(m_shaderID, locBuff);
	}
}

void Shader::AddShader(GLuint program, const char* shaderCode, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	const GLchar* code[1];
	code[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(shader, 1, code, codeLength);

	glCompileShader(shader);

	GLint result = 0;
	GLchar errLog[1024] = { 0 };

	glLinkProgram(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(shader, sizeof(errLog), NULL, errLog);
		std::cout << "Error compiling the " << shaderType << "shader: " << errLog << std::endl;
		return;
	}

	glAttachShader(program, shader);
}

void Shader::ClearShader()
{
	std::cout << "Cleaned shader!" << std::endl;

	if (m_shaderID != 0)
	{
		glDeleteProgram(m_shaderID);
		m_shaderID = 0;
	}

	uniformModel = 0;
	uniformProjection = 0;
}

Shader::~Shader()
{
	ClearShader();
}