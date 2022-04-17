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

/**
 * @class Skybox
 * @brief A skybox.
 */
class Skybox {
public:
	/**
	 * @brief Construct a new Skybox object
	 */
	Skybox();

	/**
	 * @brief Construct a new Skybox object
	 *
	 * @param faceLocations
	 */
	Skybox(const std::vector<std::string>& faceLocations);

	/**
	 * @brief Renders the skybox given a projection and view matrix.
	 *
	 * @param projectionMatrix
	 * @param viewMatrix
	 */
	void DrawSkybox(glm::mat4 projectionMatrix, glm::mat4 viewMatrix);

private:
	/// The mesh of the skybox.
	Mesh* m_skyMesh;

	/// The shader of the skybox.
	Shader* m_skyShader;

	/// The locations of the faces of the skybox.
	GLuint m_textureID;

	/// The uniform projection and view.
	GLuint m_uniformProjection, m_uniformView;
};
