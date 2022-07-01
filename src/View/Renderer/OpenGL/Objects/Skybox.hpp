#pragma once

#include <vector>
#include <string>
#include <memory>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "StbImage.hpp"

#include "Mesh.hpp"
#include "Shader.hpp"

/**
 * @class Skybox
 * @brief A skybox.
 */
class Skybox {
public:
	Skybox() = default;

	/**
	 * @brief Construct a new Skybox object
	 *
	 * @param faceLocations The locations of the faces of the skybox.
	 */
	Skybox(const std::vector<std::string>& faceLocations);

	/**
	 * @brief Renders the skybox given a projection and view matrix.
	 *
	 * @param projectionMatrix The projection matrix.
	 * @param viewMatrix The view matrix.
	 */
	void DrawSkybox(glm::mat4 projectionMatrix, glm::mat4 viewMatrix);

private:
	/// The mesh of the skybox.
	std::unique_ptr<Mesh> m_skyMesh;

	/// The shader of the skybox.
	std::unique_ptr<Shader> m_skyShader;

	/// The locations of the faces of the skybox.
	GLuint m_textureID;

	/// The uniform projection and view.
	GLuint m_uniformProjection, m_uniformView;
};
