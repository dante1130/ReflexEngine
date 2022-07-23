#include "TerrainManager.hpp"

#include "Controller/LuaManager.hpp"

void TerrainManager::lua_access() {
	auto& lua = LuaManager::get_instance().get_state();

	auto terrain_table = lua.create_named_table("Terrain");

	terrain_table.set_function("load_terrain", &TerrainManager::load_terrain,
	                           this);
}

void TerrainManager::load_terrain(const std::string& terrain_name,
                                  const std::string& heightmap) {
	TexturedTerrain& terrain = terrain_map_[terrain_name];

	terrain.load_heightfield(heightmap.c_str());
	terrain.load_mesh();
}

TexturedTerrain& TerrainManager::get_terrain(const std::string& terrain_name) {
	return terrain_map_.at(terrain_name);
}