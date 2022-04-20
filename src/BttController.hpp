#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
//#include <vector>
#include <GLFW/glfw3.h>

#include "Terrain.hpp"
#include "View/Renderer/OpenGL/Objects/Mesh.hpp"
#include "BTT.hpp"

class BttController : public Terrain {
public:
	void render(std::shared_ptr<Shader> shader) override;

	/**
	 * @brief Reads the heightmap and loads the mesh.
	 *
	 * @return true
	 * @return false
	 */
	bool load_mesh() override;

	BttController();

	~BttController();

	void getCameraPosition(const glm::vec3& pos);

	void AddHeightMap(std::vector<float> hmap);

	void AddHeightMap(GLfloat* hmap);

	void CreateTerrain(int chunkSize, int chunkDetail, int n);

	void TestThings();

	void Update(glm::vec3 player);

	GLuint* getAllIndices(glm::vec3 pos);

	const std::vector<glm::vec2>& getCenters();

	void set_height_map_size(float size);

	/**
	 * @brief Reads the texture image file and loads the texture.
	 *
	 * @param file_name
	 * @return true
	 * @return false
	 */
	bool load_texture(const char* file_name);

	/**
	 * @brief Reads an image file as a detail map.
	 *
	 * @param file_name
	 * @return true
	 * @return false
	 */
	bool load_detailmap(const char* file_name);

private:
	void GenerateVertices(int chunkSize, int chunkDetail);

	const GLuint findLOD(glm::vec3 pos, glm::vec2 center);

	GLuint* convertInt(const std::vector<glm::vec3>& temp);

	GLfloat* convertFloat(const std::vector<glm::vec3>& temp);

	std::vector<std::vector<Btt>> bttMap;  // all binary trees containing
	                                       // indices
	std::vector<glm::vec2> bttCenters;     // all
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
	glm::vec3 cam;

	std::vector<GLfloat> distances;

	std::shared_ptr<Mesh> mesh_ = nullptr;
	bool b = true;

	glm::vec3 prev_pos;
	GLuint current_total_indices;
	GLuint chunk_size;
	GLuint chunk_detail;

	int height_map_size = 0;

	/// The texture.
	std::shared_ptr<Texture> texture_ = nullptr;
	/// The detailmap.
	std::shared_ptr<Texture> detailmap = nullptr;
};
