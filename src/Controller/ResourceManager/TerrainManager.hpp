#pragma once

#include <string>
#include <unordered_map>

#include "Controller/Terrain/TexturedTerrain.hpp"

/**
 * @class TerrainManager
 * @brief An encapsulated map of terrain.
 */
class TerrainManager {
public:
	TerrainManager() = default;

	/**
	 * @brief Register the terrain manager to Lua.
	 */
	void lua_access();

	/**
	 * @brief Loads a terrain from a heightmap file.
	 *
	 * @param terrain_name The name of the terrain.
	 * @param heightmap The heightmap of the terrain.
	 */
	void load_terrain(const std::string& terrain_name,
	                  const std::string& heightmap);
	/**
	 * @brief Get the terrain with the given name.
	 *
	 * @param terrain_name The name of the terrain.
	 * @return TexturedTerrain&
	 */
	TexturedTerrain& get_terrain(const std::string& terrain_name);

private:
	/// The map of terrains.
	std::unordered_map<std::string, TexturedTerrain> terrain_map_;
};