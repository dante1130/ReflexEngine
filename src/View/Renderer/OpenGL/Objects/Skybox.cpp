#include "Skybox.hpp"

#include "StbImage.hpp"
#include "Controller/ReflexEngine/PerformanceLogger.hpp"

Skybox::Skybox(const std::vector<std::string>& faceLocations) {
	m_skyShader = std::make_unique<Shader>();
	m_skyShader->CompileFile("shaders/skybox.vert", "shaders/skybox.frag");

	m_uniformProjection = m_skyShader->GetProjectionLocation();
	m_uniformView = m_skyShader->GetViewLocation();

	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);

	int width, height, bitDepth;

	for (size_t i = 0; i < 6; ++i) {
		unsigned char* texData =
		    stbi_load(faceLocations[i].c_str(), &width, &height, &bitDepth, 0);

		if (!texData) {
			std::cout << "Failed to load image " << faceLocations[i]
			          << std::endl;
			return;
		}

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width,
		             height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);

		stbi_image_free(texData);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Mesh Setup
	constexpr uint32_t skyboxIndices[] = {// front
	                                      0, 1, 2, 2, 1, 3,
	                                      // right
	                                      2, 3, 5, 5, 3, 7,
	                                      // back
	                                      5, 7, 4, 4, 7, 6,
	                                      // left
	                                      4, 6, 0, 0, 6, 1,
	                                      // top
	                                      4, 0, 5, 5, 0, 2,
	                                      // bottom
	                                      1, 6, 3, 3, 6, 7};

	constexpr float skyboxVertices[] = {
	    -1.0f, 1.0f,  -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	    1.0f,  1.0f,  -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	    1.0f,  -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

	    -1.0f, 1.0f,  1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	    1.0f,  1.0f,  1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	    -1.0f, -1.0f, 1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	    1.0f,  -1.0f, 1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

	m_skyMesh = std::make_unique<Mesh>();
	m_skyMesh->create_mesh(skyboxVertices, skyboxIndices, 64, 36);
}

void Skybox::DrawSkybox(glm::mat4 projectionMatrix,
                        glm::mat4 viewMatrix) const {
	if (!m_skyMesh) return;

	viewMatrix = glm::mat4(glm::mat3(viewMatrix));

	glDepthMask(GL_FALSE);

	m_skyShader->UseShader();

	glUniformMatrix4fv(m_uniformProjection, 1, GL_FALSE,
	                   glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(m_uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);

	PERFORMANCE_LOGGER_PUSH("Validate skybox shader");
	m_skyShader->Validate();
	PERFORMANCE_LOGGER_POP();

	m_skyMesh->render_mesh();

	glDepthMask(GL_TRUE);
}
