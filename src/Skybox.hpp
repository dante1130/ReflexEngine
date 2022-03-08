#pragma once

#include <vector>
#include <string>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "StbImage.hpp"

#include "Mesh.hpp"
#include "Shader.hpp"

class Skybox
{
public:
	Skybox();

	Skybox(const std::vector<std::string>& faceLocations);

	void DrawSkybox(glm::mat4 projectionMatrix, glm::mat4 viewMatrix);

	~Skybox();

private:
	Mesh* m_skyMesh;
	Shader* m_skyShader;

	GLuint m_textureID;
	GLuint m_uniformProjection, m_uniformView;
};