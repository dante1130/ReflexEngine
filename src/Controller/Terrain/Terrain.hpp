#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>

#include "View/Renderer/OpenGL/Objects/Mesh.hpp"
#include "View/Renderer/OpenGL/Objects/Texture.hpp"
#include "View/Renderer/OpenGL/Objects/Shader.hpp"

/**
 * @class Base terrain class.
 */
class Terrain {
public:
	/**
	 * @brief Renders the terrain.
	 *
	 * @param shader The shader to use.
	 */
	virtual void render(std::shared_ptr<Shader> shader) = 0;

	/**
	 * @brief Reads the heightmap and loads the mesh.
	 *
	 * @return bool
	 */
	virtual bool load_mesh() = 0;

	/**
	 * @brief Load an image as a heightmap.
	 *
	 * @param file_name The file name of the image.
	 * @return bool
	 */
	bool load_heightfield(const char* file_name);

	/**
	 * @brief Generate terrain by the fault formation method.
	 *
	 * @param iterations The number of iterations.
	 * @param size The size of the terrain.
	 * @param min_height The minimum height of the terrain.
	 * @param max_height The maximum height of the terrain.
	 * @param weight The weight of the fault.
	 * @return bool
	 */
	bool gen_faultformation(int iterations, size_t size, int min_height,
	                        int max_height, float weight);

	/**
	 * @brief Get the offset to origin of the terrain.
	 *
	 * @return glm::vec3
	 */
	glm::vec3 get_origin() const;

	/**
	 * @brief Get the scale of the terrain.
	 *
	 * @return glm::vec3
	 */
	glm::vec3 get_scale() const;

	/**
	 * @brief Get the height in terrain space given the x and z coordinates.
	 *
	 * @param x The x coordinate.
	 * @param z The z coordinate.
	 * @return float
	 */
	float get_height(int x, int z) const;

	/**
	 * @brief Get the height in worldspace given the x and z coordinates.
	 *
	 * @param x The x coordinate.
	 * @param z The z coordinate.
	 * @return float
	 */
	float get_height_world(float x, float z) const;

	/**
	 * @brief Get the height color.
	 *
	 * @param x The x coordinate.
	 * @param z The z coordinate.
	 * @return uint8_t
	 */
	uint8_t get_height_color(int x, int z) const;

	/**
	 * @brief Get the width.
	 *
	 * @return size_t
	 */
	size_t get_width() const;

	/**
	 * @brief Get the width.
	 *
	 * @return size_t
	 */
	size_t get_length() const;

	/**
	 * @brief Get the height map
	 *
	 * @return uint8_t	- The height map
	 */
	uint8_t* get_height_map();

	/**
	 * @brief Set the height map.
	 *
	 * @param map
	 */
	void set_height_map(uint8_t* map);

	/**
	 * @brief Set the scale.
	 *
	 * @param scale
	 */
	void set_scale(glm::vec3 scale);

	/**
	 * @brief Destroy the Terrain object
	 */
	virtual ~Terrain();

protected:
	/// An unsigned char array containing the heightmap.
	uint8_t* heightmap_ = nullptr;

	/// The scale of the heightmap.
	glm::vec3 scale_ = {1.0f, 1.0f, 1.0f};

	/// Calculates the normals for the terrain given x and z coordinates.
	glm::vec3 calculate_terrain_normal(int x, int z) const;

private:
	/// The width of the heightmap.
	size_t width_ = {0};
	/// The length of the heightmap.
	size_t length_ = {0};
	/// The bit depth of the heightmap.
	int bit_depth_ = {0};

	/**
	 * @brief Check whether the given coordinates are within the heightmap.
	 *
	 * @param x The x coordinate.
	 * @param z The z coordinate.
	 * @return true
	 * @return false
	 */
	bool is_in_bounds(int x, int z) const;

	/**
	 * @brief Applies a FCI filter to the heightmap.
	 *
	 * @param heights The heights to filter.
	 * @param weight The weight of the filter.
	 */
	void add_filter(std::vector<float>& heights, float weight);

	/**
	 * @brief A pass of the FCI filter.
	 *
	 * @param start_point The start point.
	 * @param increment The increment.
	 * @param weight The weight of the filter.
	 */
	void filter_pass(float* start_point, int increment, float weight);

	/**
	 * @brief Normalizes and smoothen the terrain heightmap.
	 *
	 * @param heights The heights to normalize.
	 */
	void normalize_terrain(std::vector<float>& heights);
};
