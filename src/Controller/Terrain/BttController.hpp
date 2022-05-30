#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include "Terrain.hpp"
#include "View/Renderer/OpenGL/Objects/Mesh.hpp"
#include "BTT.hpp"

/**
 * @class Binary Triangle Tree Controller class
 */
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

	/**
	 * @brief Default contructor for BttController.
	 */
	BttController();

	/**
	 * @brief Decontructor for BttController.
	 */
	~BttController();

	/**
	 * @brief	Stores the psoition of the camera within the BttController
	 * for later use
	 *
	 * @param		pos	- The position of the camera
	 */
	void getCameraPosition(const glm::vec3& pos);

	/**
	 * @brief	Initialises the BTT grid by generating vertices, creating BTT
	 * structures defining centers and generating LOD distances
	 *
	 * @param		chunkSize - The length of the grid i.e chunkSize * chunkSize
	 * is equal to number of tiles displayed
	 * @param		chunkDetail - The amount of vertices per row of a tile i.e
	 * chunkDetail * chunkDetail is equal to total number of vertice sper tile
	 * @param		n - Factor that determining tile detail i.e chunkDetail
	 * must be equal to 2^n + 1
	 *
	 * @return void
	 */
	void CreateTerrain(int chunkSize, int chunkDetail, int n);

	/**
	 * @brief	Searches through BTT and determines if a BTT needs to increase
	 * its LOD to remove potential T-Junction (NOT IMPLEMENTED)
	 *
	 * @return void
	 */
	void checkTJunction();

	/**
	 * @brief	Updates the mesh when the player moves position
	 *
	 * @param	player - The players position in world coordinates
	 *
	 * @return void
	 */
	void Update(glm::vec3 player);

	/**
	 * @brief	Calculates the meshes new indices for all BTTs and stores them
	 * for later use
	 *
	 * @param	pos - The players position in world coordinates
	 *
	 * @return void
	 */
	void getAllIndices(glm::vec3 pos);

	/**
	 * @brief	Sets the size of the heightmap
	 *
	 * @param	size - Sets length and width of heightmap
	 *
	 * @return void
	 */
	void set_height_map_size(float size);

	/**
	 * @brief Set the texture id.
	 *
	 * @param id
	 */
	void set_texture_id(GLuint id);

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
	/**
	 * @brief	Gets the array of BTT tile centers
	 *
	 * @return a list of vector2
	 */
	const std::vector<glm::vec2>& getCenters();

	/**
	 * @brief	Generate all vertices for terrain
	 *
	 * @param	chunkSize - Determines the gridsize of BTTs
	 * @param 	chunkDetail - Determines the no of vertices per BTT
	 *
	 * @return void
	 */
	void GenerateVertices(int chunkSize, int chunkDetail);

	/**
	 * @brief	based off player position, determines a BTT's level of detail
	 *
	 * @param	pos - The players position in world coordinates
	 * @param 	center - The center of a tile in world coordinates
	 *
	 * @return the level of detail calculated
	 */
	const GLuint findLOD(glm::vec3 pos, glm::vec2 center);

	std::vector<std::vector<Btt>> bttMap;  /// All binary triangle trees
	std::vector<glm::vec2>
	    bttCenters;  /// All centers for BTT tiles (hypotenuse-adjacent BTTs)
	std::vector<GLfloat> vertices;  /// All the vertices for the terrain
	std::vector<GLuint> indices;  /// All the currently used indices for terrain
	glm::vec3 cam;                /// Stored position for camera

	std::vector<GLfloat>
	    distances;  /// Distances from player for changes in LOD for tile

	std::shared_ptr<Mesh> mesh_ = nullptr;  /// Container for mesh data;
	bool firstRun;  /// Determines if first time of mesh generation

	glm::vec3 prev_pos;  /// Saves the players previous position
	GLuint
	    current_total_indices;  /// Number of current total indices being used
	GLuint chunk_size;          /// The length/width of BTT grid
	GLuint chunk_detail;  /// The length/width of a given tile (vertice number)

	int height_map_size = 0;  /// the length/width of height map

	std::shared_ptr<Texture> texture_ = nullptr;   /// Storage for texture.
	std::shared_ptr<Texture> detailmap = nullptr;  /// Storage for detailmap.
};
