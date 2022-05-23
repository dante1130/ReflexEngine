#pragma once

#include "GameObject.hpp"
#include "Controller/Terrain/BttController.hpp"
#include "Controller/multiTextureCreator.hpp"
#include "Controller/ResourceManager/ObjectSaving.hpp"

/**
 * @class TerrainObject
 * @brief A terrain game object.
 */
class TerrainObject : public GameObject {
public:
	/**
	 * @brief Construct a new Terrain Object
	 */
	TerrainObject();

	/**
	 * @brief Initializes the game object.
	 */
	void init() override;

	/**
	 * @brief Updates the game object with fixed delta time.
	 *
	 * @param delta_time The time since the last fixed tick.
	 */
	void fixed_update(double delta_time) override;

	/**
	 * @brief Updates the game object with delta time.
	 *
	 * @param delta_time The time since the last frame.
	 */
	void update(double delta_time) override{};

	/**
	 * @brief Adds the draw call to the renderer.
	 */
	void add_draw_call() override;

	/**
	 * @brief The draw function.
	 *
	 * @param shader The shader to use.
	 */
	void draw(std::shared_ptr<Shader> shader) override;

	/**
	 * @brief Saves the object to a lua file.
	 */
	void save_object() override;

	/**
	 * @brief Adds a new texture to the terrain.
	 *
	 * @param file_name The file name of the texture.
	 */
	void add_texture(const std::string& file_name);

	/**
	 * @brief Adds a new heightmap to the terrain.
	 *
	 * @param heightmap The heightmap data
	 * @param xSize The x size of the heightmap
	 * @param ySize The y size of the heightmap
	 * @param island Whether to create an island
	 */
	void add_height_map(uint8_t* heightmap, int xSize, int ySize, bool island);

	/**
	 * @brief Adds a detail map to the terrain.
	 *
	 * @param file_name
	 */
	void add_detail_map(const std::string& file_name);

	/**
	 * @brief Create the terrain.
	 *
	 * @param chunckSize The chunk size.
	 * @param chunkDetail The chunk detail.
	 * @param n Factor that determining tile detail
	 * @param heightSize The height size.
	 * @param scale The scale.
	 */
	void create_terrain(int chunckSize, int chunkDetail, int n, int heightSize,
	                    glm::vec3 scale);

	/**
	 * @brief Get the height map.
	 *
	 * @return uint8_t*
	 */
	uint8_t* get_height_map();

	/**
	 * @brief Adds a new texture file path to the terrain.
	 *
	 * @param text The texture file path.
	 * @param n The index.
	 */
	void add_storage_text(const std::string& text, int n);

private:
	/// The BTT controller.
	BttController bttControl;
	/// The multi texture creator.
	multiTextureCreator mtc;
	/// The last update.
	float lastUpdate = -1;
	/// The array of textures.
	std::string m_text[6];
};
