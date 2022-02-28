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

#include "CommonValues.hpp"

#include "Window.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Texture.hpp"
#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include "Material.hpp"
#include "SpotLight.hpp"

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

	Texture plainTexture("textures/plain.png");
	plainTexture.LoadTexture();

	DirectionalLight mainLight(glm::vec3(1.0f), 0.1f, glm::vec3(0.0f, 0.0f, -1.0f), 0.1f);

	PointLight pointLights[MAX_POINT_LIGHTS];
	SpotLight spotLights[MAX_SPOT_LIGHTS];

	GLuint pointLightCount = 0u;
	GLuint spotLightCount = 0u;

	pointLights[0] = PointLight(glm::vec3(0.0f, 0.0f, 1.0f), 0.0f, 0.1f, 
								glm::vec3(0.0f, 0.0f, 0.0f), 0.3f, 0.2f, 0.1f);

	++pointLightCount;

	pointLights[1] = PointLight(glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.1f,
								glm::vec3(-4.0f, 2.0f, 0.0f), 0.3f, 0.1f, 0.1f);

	++pointLightCount;

	spotLights[0] = SpotLight(glm::vec3(1.0f, 1.0f, 1.0f), 0.0f, 2.0f,
							  glm::vec3(0.0f, 0.0f, 0.0f), 
							  glm::vec3(0.0f, -1.0f, 0.0f),
							  1.0f, 0.0f, 0.0f, 20.0f);

	++spotLightCount;

	spotLights[1] = SpotLight(glm::vec3(1.0f, 1.0f, 1.0f), 0.0f, 1.0f,
							  glm::vec3(0.0f, 0.0f, 0.0f),
							  glm::vec3(-100.0f, -1.0f, 0.0f),
							  1.0f, 0.0f, 0.0f, 20.0f);

	++spotLightCount;


	Material shinyMaterial(256, 4.0f);
	Material dullMaterial(4, 0.3f);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;

	GLuint uniformEyePosition = 0;

	GLuint uniformSpecularIntensity = 0, uniformShininess = 0;

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

		uniformEyePosition = shaderVec[0].GetEyePositionLocation();

		uniformShininess = shaderVec[0].GetShininessLocation();
		uniformSpecularIntensity = shaderVec[0].GetSpecularIntensityLocation();

		glm::vec3 lowerLight = camera.GetCamPosition();
		lowerLight.y -= 0.3f;

		spotLights[0].SetFlash(lowerLight, camera.GetCamDirection());

		shaderVec[0].SetDirectionalLight(mainLight);
		shaderVec[0].SetPointLights(pointLights, pointLightCount);
		shaderVec[0].SetSpotLights(spotLights, spotLightCount);

		// Creates projection matrix mode
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		// Create view matrix mode
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));

		glUniform3f(uniformEyePosition, camera.GetCamPosition().x,
										camera.GetCamPosition().y,
										camera.GetCamPosition().z);

		// Creates identity matrix for model matrix mode
		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brickTexture.UseTexture();
		shinyMaterial.UseMaterial(uniformShininess, uniformSpecularIntensity);
		meshVec[0].RenderMesh();
		
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 4.0f, -2.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dirtTexture.UseTexture();
		dullMaterial.UseMaterial(uniformShininess, uniformSpecularIntensity);
		meshVec[1].RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		plainTexture.UseTexture();
		shinyMaterial.UseMaterial(uniformShininess, uniformSpecularIntensity);
		meshVec[2].RenderMesh();

		glUseProgram(0);

		mainWindow.SwapBuffers();
	}

	return 0;
}

void CalcAverageNormals(GLuint* indices, GLuint indicesCount, GLfloat* vertices, GLuint verticesCount, GLuint vLength, GLuint normalOffset)
{
	for (size_t i = 0; i < indicesCount; i += 3)
	{
		GLuint in0 = indices[i] * vLength;
		GLuint in1 = indices[i + 1] * vLength;
		GLuint in2 = indices[i + 2] * vLength;

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
		GLuint nOffset = i * vLength + normalOffset;
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
		-1.0f, -1.0f, -0.6f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, -0.6f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f
	};

	GLuint floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f, 10.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f, 0.0f, 10.0f, 0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f, 10.0f, 10.0f, 0.0f, -1.0f, 0.0f
	};

	CalcAverageNormals(indices, 12, vertices, 32, 8, 5);

	meshVec.reserve(3);

	Mesh* mesh1 = new Mesh();
	mesh1->CreateMesh(vertices, indices, 32, 12);
	meshVec.push_back(*mesh1);

	Mesh* mesh2 = new Mesh();
	mesh2->CreateMesh(vertices, indices, 32, 12);
	meshVec.push_back(*mesh2);

	Mesh* mesh3 = new Mesh();
	mesh3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshVec.push_back(*mesh3);
}

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CompileFile(vShader, fShader);
	shaderVec.push_back(*shader1);
}
