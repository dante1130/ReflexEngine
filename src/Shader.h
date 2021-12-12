#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include <glad/glad.h>

class Shader
{
public:
	Shader();

	GLuint GetProjectionLocation() const;
	GLuint GetModelLocation() const;
	GLuint GetViewLocation() const;

	void UseShader();

	void CompileCode(const char* vertexCode, const char* fragmentCode);
	void CompileFile(const char* vertexPath, const char* fragmentPath);

	std::string ReadFile(const char* fileLocation);

	void ClearShader();

	~Shader();

private:
	GLuint shaderID, uniformProjection, uniformModel, uniformView;

	void AddShader(GLuint program, const char* shaderCode, GLenum shaderType);
	void CompileShader(const char* vertexCode, const char* fragmentCode);
};