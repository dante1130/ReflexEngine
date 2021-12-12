#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"

static std::vector<Mesh> meshVec;
static std::vector<Shader> shaderVec;

// Vertex Shader path
static const char* vShader = "shaders/shader.vert";

// Fragment Shader path
static const char* fShader = "shaders/shader.frag";

void CreateObjects();
void CreateShaders();

int main(int argc, char* argv[])
{
	

	Camera camera(glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.2f);

	Window mainWindow(1920, 1080);

	GLfloat deltaTime = 0.0f;
	GLfloat prevTime = 0.0f;

	mainWindow.Init();

	CreateObjects();
	CreateShaders();

	Texture brickTexture("textures/brick.png");
	brickTexture.LoadTexture();

	Texture dirtTexture("textures/dirt.png");
	dirtTexture.LoadTexture();

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;

	glm::mat4 projection = glm::perspective(45.0f, static_cast<GLfloat>(mainWindow.GetBufferWidth()) / static_cast<GLfloat>(mainWindow.GetBufferHeight()), 0.1f, 100.0f);

	while (!mainWindow.IsShouldClose())
	{
		GLfloat currTime = glfwGetTime();
		deltaTime = currTime - prevTime;
		prevTime = currTime;

		glfwPollEvents();

		camera.KeyControl(mainWindow.GetKeys(), deltaTime);
		camera.MouseControl(mainWindow.GetXOffset(), mainWindow.GetYOffset());

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderVec[0].UseShader();
		uniformModel = shaderVec[0].GetModelLocation();
		uniformProjection = shaderVec[0].GetProjectionLocation();
		uniformView = shaderVec[0].GetViewLocation();

		// Creates projection matrix mode
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		// Create view matrix mode
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));

		// Creates identity matrix for model matrix mode
		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brickTexture.UseTexture();
		meshVec[0].RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dirtTexture.UseTexture();
		meshVec[1].RenderMesh();

		glUseProgram(0);

		mainWindow.SwapBuffers();
	}

	return 0;
}

void CreateObjects()
{
	GLuint indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
	//  x	   y	  z		u	  v
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 1.0f, 0.5f, 0.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.5f, 1.0f
	};

	meshVec.reserve(2);

	Mesh* mesh1 = new Mesh();
	mesh1->CreateMesh(vertices, indices, 20, 12);
	meshVec.push_back(*mesh1);

	Mesh* mesh2 = new Mesh();
	mesh2->CreateMesh(vertices, indices, 20, 12);
	meshVec.push_back(*mesh2);
}

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CompileFile(vShader, fShader);
	shaderVec.push_back(*shader1);
}
