#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Mesh.h"
#include "Shader.h"

Window mainWindow;

std::vector<Mesh> meshVec;
std::vector<Shader> shaderVec;

// Vertex Shader source code
static const char* vShader = "shaders/shader.vert";

//Fragment Shader source code
static const char* fShader = "shaders/shader.frag";

void CreateObjects()
{
	GLuint indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	meshVec.reserve(2);

	Mesh* mesh1 = new Mesh();
	mesh1->CreateMesh(vertices, indices, 12, 12);
	meshVec.push_back(*mesh1);

	Mesh* mesh2 = new Mesh();
	mesh2->CreateMesh(vertices, indices, 12, 12);
	meshVec.push_back(*mesh2);
}

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CompileFile(vShader, fShader);
	shaderVec.push_back(*shader1);
}

int main(int argc, char* argv[])
{
	mainWindow = Window(800, 600);

	mainWindow.Init();

	CreateObjects();
	CreateShaders();

	GLuint uniformProjection = 0, uniformModel = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.GetBufferWidth() / mainWindow.GetBufferHeight(), 0.1f, 100.0f);

	while (!mainWindow.IsShouldClose())
	{
		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderVec[0].UseShader();
		uniformModel = shaderVec[0].GetModelLocation();
		uniformProjection = shaderVec[0].GetProjectionLocation();

		// Creates projection matrix mode
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		// Creates identity matrix for model matrix mode
		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshVec[0].RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshVec[1].RenderMesh();

		glUseProgram(0);

		mainWindow.SwapBuffers();
	}

	return 0;
}
