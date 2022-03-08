#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <numbers>

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
#include "Model.hpp"
#include "Skybox.hpp"

static std::vector<Mesh*> meshVec;

static Shader* shader;
static Shader* directionalShadowShader;
static Shader* omniShadowShader;

static Window mainWindow;

static glm::mat4 projection;

static Camera camera;

static DirectionalLight mainLight;

static PointLight pointLights[MAX_POINT_LIGHTS];
static SpotLight spotLights[MAX_SPOT_LIGHTS];

static GLuint pointLightCount = 0u;
static GLuint spotLightCount = 0u;

static Texture brickTexture("textures/brick.png");
static Texture dirtTexture("textures/dirt.png");
static Texture plainTexture("textures/plain.png");

static Material shinyMaterial(256, 4.0f);
static Material dullMaterial(4, 0.3f);

static Skybox skybox;

static Model cat;

static GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;

static GLuint uniformEyePosition = 0;

static GLuint uniformSpecularIntensity = 0, uniformShininess = 0;

static GLuint uniformOmniLightPos = 0, uniformFarPlane = 0;

void Init();
void CalcAverageNormals(GLuint* indices, GLuint indicesCount, 
						GLfloat* vertices, GLuint verticesCount, 
						GLuint vLength, GLuint normalOffset);
void RenderScene();
void RenderPass(glm::mat4 projectionMatrix, glm::mat4 viewMatrix);
void DirectionalShadowMapPass(const DirectionalLight& light);
void OmniShadowMapPass(const PointLight& light);
void CreateObjects();
void CreateShaders();
void DeleteObjects();
void DeleteShaders();

int main(int argc, char* argv[])
{
	Init();

	GLfloat deltaTime = 0.0f;
	GLfloat prevTime = glfwGetTime();

	while (!mainWindow.IsShouldClose())
	{
		GLfloat currTime = glfwGetTime();
		deltaTime = currTime - prevTime;
		prevTime = currTime;

		glfwPollEvents();

		camera.KeyControl(mainWindow.GetKeys(), deltaTime);
		camera.MouseControl(mainWindow.GetXOffset(), mainWindow.GetYOffset());

		DirectionalShadowMapPass(mainLight);

		for (size_t i = 0; i < pointLightCount; ++i)
			OmniShadowMapPass(pointLights[i]);

		for (size_t i = 0; i < spotLightCount; ++i)
			OmniShadowMapPass(spotLights[i]);

		RenderPass(projection, camera.CalculateViewMatrix());
		
		glUseProgram(0);

		mainWindow.SwapBuffers();
	}

	DeleteObjects();
	DeleteShaders();

	return 0;
}

void Init()
{
	mainWindow = Window(1920, 1080);
	mainWindow.Init();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.2f);

	cat.LoadModel("models/12221_Cat_v1_l3.obj");
		
	brickTexture = Texture("textures/brick.png");
	brickTexture.LoadTextureA();

	dirtTexture = Texture("textures/dirt.png");
	dirtTexture.LoadTextureA();

	plainTexture = Texture("textures/plain.png");
	plainTexture.LoadTextureA();

	mainLight = DirectionalLight(2048, 2048, glm::vec3(1.0f, 0.53f, 0.3f), 0.1f, 
								 glm::vec3(-10.0f, -12.0f, 18.5f), 0.9f);

	pointLights[0] = PointLight(1024, 1024, 0.01f, 100.0f, 
								glm::vec3(0.0f, 0.0f, 1.0f), 0.0f, 1.0f,
								glm::vec3(1.0f, 2.0f, 0.0f), 0.3f, 1.0f, 1.0f);

	++pointLightCount;

	pointLights[1] = PointLight(1024, 1024, 0.01f, 100.0f,
								glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 1.0f,
								glm::vec3(-4.0f, 3.0f, 0.0f), 0.3f, 1.0f, 1.0f);

	++pointLightCount;

	spotLights[0] = SpotLight(1024, 1024, 0.01f, 100.0f,
							  glm::vec3(1.0f, 1.0f, 1.0f), 0.0f, 2.0f,
							  glm::vec3(0.0f, 0.0f, 0.0f),
							  glm::vec3(0.0f, -1.0f, 0.0f),
							  1.0f, 0.0f, 0.0f, 20.0f);

	++spotLightCount;

	spotLights[1] = SpotLight(1024, 1024, 0.01f, 100.0f,
							  glm::vec3(1.0f, 1.0f, 1.0f), 0.0f, 1.0f,
							  glm::vec3(0.0f, 0.0f, 0.0f),
							  glm::vec3(-100.0f, -1.0f, 0.0f),
							  1.0f, 0.0f, 0.0f, 20.0f);

	++spotLightCount;

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("textures/skyboxes/cupertin-lake/cupertin-lake_rt.tga");
	skyboxFaces.push_back("textures/skyboxes/cupertin-lake/cupertin-lake_lf.tga");
	skyboxFaces.push_back("textures/skyboxes/cupertin-lake/cupertin-lake_up.tga");
	skyboxFaces.push_back("textures/skyboxes/cupertin-lake/cupertin-lake_dn.tga");
	skyboxFaces.push_back("textures/skyboxes/cupertin-lake/cupertin-lake_bk.tga");
	skyboxFaces.push_back("textures/skyboxes/cupertin-lake/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	projection = glm::perspective(glm::radians(60.0f), static_cast<GLfloat>(mainWindow.GetBufferWidth()) / static_cast<GLfloat>(mainWindow.GetBufferHeight()), 0.1f, 100.0f);
}

void RenderScene()
{
	// Creates identity matrix for model matrix mode
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	brickTexture.UseTexture();
	shinyMaterial.UseMaterial(uniformShininess, uniformSpecularIntensity);
	meshVec[0]->RenderMesh();

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 4.0f, -2.5f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	dirtTexture.UseTexture();
	dullMaterial.UseMaterial(uniformShininess, uniformSpecularIntensity);
	meshVec[1]->RenderMesh();

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	dirtTexture.UseTexture();
	shinyMaterial.UseMaterial(uniformShininess, uniformSpecularIntensity);
	meshVec[2]->RenderMesh();

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -2.0f, 4.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	shinyMaterial.UseMaterial(uniformShininess, uniformSpecularIntensity);
	cat.RenderModel();
}

void RenderPass(glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
{
	glViewport(0, 0, 1920, 1080);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	skybox.DrawSkybox(projectionMatrix, viewMatrix);

	shader->UseShader();

	uniformModel = shader->GetModelLocation();
	uniformProjection = shader->GetProjectionLocation();
	uniformView = shader->GetViewLocation();

	uniformEyePosition = shader->GetEyePositionLocation();

	uniformShininess = shader->GetShininessLocation();
	uniformSpecularIntensity = shader->GetSpecularIntensityLocation();

	// Creates projection matrix mode
	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

	// Create view matrix mode
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));

	glUniform3f(uniformEyePosition, camera.GetCamPosition().x,
		camera.GetCamPosition().y,
		camera.GetCamPosition().z);

	shader->SetDirectionalLight(mainLight);
	shader->SetPointLights(pointLights, pointLightCount, 3, 0);
	shader->SetSpotLights(spotLights, spotLightCount, 3  + pointLightCount, pointLightCount);
	shader->SetDirectionalLightTransform(mainLight.CalculateLightTransform());

	mainLight.GetShadowMap()->Read(GL_TEXTURE2);

	shader->SetTexture(1);
	shader->SetDirectionalShadowMap(2);

	glm::vec3 lowerLight = camera.GetCamPosition();
	lowerLight.y -= 0.3f;
	spotLights[0].SetFlash(lowerLight, camera.GetCamDirection());

	shader->Validate();

	RenderScene();
}

void DirectionalShadowMapPass(const DirectionalLight& light)
{
	directionalShadowShader->UseShader();

	glViewport(0, 0,
		light.GetShadowMap()->GetShadowWidth(),
		light.GetShadowMap()->GetShadowHeight());

	light.GetShadowMap()->Write();
	glClear(GL_DEPTH_BUFFER_BIT);
	
	uniformModel = directionalShadowShader->GetModelLocation();
	directionalShadowShader->SetDirectionalLightTransform(light.CalculateLightTransform());

	directionalShadowShader->Validate();

	RenderScene();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OmniShadowMapPass(const PointLight& light)
{
	omniShadowShader->UseShader();

	glViewport(0, 0, light.GetShadowMap()->GetShadowWidth(),
					 light.GetShadowMap()->GetShadowHeight());

	light.GetShadowMap()->Write();

	glClear(GL_DEPTH_BUFFER_BIT);

	uniformModel = omniShadowShader->GetModelLocation();
	uniformOmniLightPos = omniShadowShader->GetOmniLightPosLocation();
	uniformFarPlane = omniShadowShader->GetFarPlaneLocation();

	glUniform3f(uniformOmniLightPos, light.GetPosition().x,
									 light.GetPosition().y,
									 light.GetPosition().z);
	glUniform1f(uniformFarPlane, light.GetFarPlane());

	omniShadowShader->SetLightMatrices(light.CalculateLightTransform());

	omniShadowShader->Validate();

	RenderScene();
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
		0u, 3u, 1u,
		1u, 3u, 2u,
		2u, 3u, 0u,
		0u, 1u, 2u
	};

	GLfloat vertices[] = {
	//  x	   y	  z		u	  v		nx	  ny	nz
		-1.0f, -1.0f, -0.6f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, -0.6f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f
	};

	GLuint floorIndices[] = {
		0u, 2u, 1u,
		1u, 2u, 3u
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f, 10.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f, 0.0f, 10.0f, 0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f, 10.0f, 10.0f, 0.0f, -1.0f, 0.0f
	};

	CalcAverageNormals(indices, 12u, vertices, 32u, 8u, 5u);

	meshVec.reserve(3);

	Mesh* mesh1 = new Mesh();
	mesh1->CreateMesh(vertices, indices, 32u, 12u);
	meshVec.push_back(mesh1);

	Mesh* mesh2 = new Mesh();
	mesh2->CreateMesh(vertices, indices, 32u, 12u);
	meshVec.push_back(mesh2);

	Mesh* mesh3 = new Mesh();
	mesh3->CreateMesh(floorVertices, floorIndices, 32u, 6u);
	meshVec.push_back(mesh3);
}

void CreateShaders()
{
	shader = new Shader();
	shader->CompileFile("shaders/shader.vert", "shaders/shader.frag");

	directionalShadowShader = new Shader();
	directionalShadowShader->CompileFile("shaders/directional_shadow_map.vert", 
										 "shaders/directional_shadow_map.frag");

	omniShadowShader = new Shader();
	omniShadowShader->CompileFile("shaders/omni_shadow_map.vert",
								  "shaders/omni_shadow_map.geom",
								  "shaders/omni_shadow_map.frag");
}

void DeleteObjects()
{
	for (auto& obj : meshVec)
	{
		if (obj)
		{
			delete obj;
			obj = nullptr;
		}
	}
}

void DeleteShaders()
{
	delete shader;
	delete directionalShadowShader;
	delete omniShadowShader;
}
