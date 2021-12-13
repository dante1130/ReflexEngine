#include "Shader.hpp"

Shader::Shader()
{
	m_shaderID = 0;
	uniformModel = 0;
	uniformProjection = 0;
}

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
	return uniformAmbientIntensity;
}

GLuint Shader::GetAmbientIntensityColor() const
{
	return uniformAmbientColor;
}

GLuint Shader::GetDiffuseIntensityLocation() const
{
	return uniformDiffuseIntensity;
}

GLuint Shader::GetDirectionLocation() const
{
	return uniformDirection;
}

GLuint Shader::GetSpecularIntensityLocation() const
{
	return uniformSpecularIntensity;
}

GLuint Shader::GetShininessLocation() const
{
	return uniformShininess;
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

	uniformAmbientColor = glGetUniformLocation(m_shaderID, "directionalLight.color");
	uniformAmbientIntensity = glGetUniformLocation(m_shaderID, "directionalLight.ambientIntensity");

	uniformDirection = glGetUniformLocation(m_shaderID, "directionalLight.direction");
	uniformDiffuseIntensity = glGetUniformLocation(m_shaderID, "directionalLight.diffuseIntensity");

	uniformShininess = glGetUniformLocation(m_shaderID, "material.shininess");
	uniformSpecularIntensity = glGetUniformLocation(m_shaderID, "material.specularIntensity");
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