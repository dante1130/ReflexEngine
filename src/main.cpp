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

#include "Window.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Texture.hpp"
#include "Light.hpp"

static std::vector<Mesh> meshVec;
static std::vector<Shader> shaderVec;

// Vertex Shader path
static const char* vShader = "shaders/shader.vert";

// Fragment Shader path
static const char* fShader = "shaders/shader.frag";

void CalcAverageNormals(GLuint* indices, GLuint indicesCount, 
						GLfloat* vertices, GLuint verticesCount, 
						GLuint vLength, GLuint normalOffset);
void CreateObjects();
void CreateShaders();

int main(int argc, char* argv[])
{
	Window mainWindow(1920, 1080);

	mainWindow.Init();

	Camera camera(glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.2f);

	Texture brickTexture("textures/brick.png");
	brickTexture.LoadTexture();

	Texture dirtTexture("textures/dirt.png");
	dirtTexture.LoadTexture();

	Light mainLight(glm::vec3(1.0f), 0.2f, glm::vec3(2.0f, -1.0f, -2.0f), 1.0f);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;

	GLuint uniformAmbientIntensity = 0, uniformAmbientColor = 0;

	GLuint uniformDiffuseIntensity = 0, uniformDirection = 0;

	GLfloat deltaTime = 0.0f;
	GLfloat prevTime = 0.0f;

	CreateObjects();
	CreateShaders();

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
		uniformAmbientColor = shaderVec[0].GetAmbientIntensityColor();
		uniformAmbientIntensity = shaderVec[0].GetAmbientIntensityLocation();
		uniformDirection = shaderVec[0].GetDirectionLocation();
		uniformDiffuseIntensity = shaderVec[0].GetDiffuseIntensityLocation();

		mainLight.UseLight(uniformAmbientColor, uniformAmbientIntensity,
						   uniformDirection, uniformDiffuseIntensity);

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

void CalcAverageNormals(GLuint* indices, GLuint indicesCount, GLfloat* vertices, GLuint verticesCount, GLuint vLength, GLuint normalOffset)
{
	for (size_t i = 0; i < indicesCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;

		glm::vec3 v1(vertices[in1] - vertices[in0], 
					 vertices[in1 + 1] - vertices[in0 + 1], 
					 vertices[in1 + 2] - vertices[in0 + 2]);

		glm::vec3 v2(vertices[in2] - vertices[in0], 
					 vertices[in2 + 1] - vertices[in0 + 1], 
					 vertices[in2 + 2] - vertices[in0 + 2]);

		glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;

		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticesCount / vLength; ++i)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
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
	//  x	   y	  z		u	  v		nx	  ny	nz
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f
	};

	CalcAverageNormals(indices, 12, vertices, 32, 8, 5);

	meshVec.reserve(2);

	Mesh* mesh1 = new Mesh();
	mesh1->CreateMesh(vertices, indices, 32, 12);
	meshVec.push_back(*mesh1);

	Mesh* mesh2 = new Mesh();
	mesh2->CreateMesh(vertices, indices, 32, 12);
	meshVec.push_back(*mesh2);
}

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CompileFile(vShader, fShader);
	shaderVec.push_back(*shader1);
}
