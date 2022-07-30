#include "TerrainManager.hpp"

#include "Controller/LuaManager.hpp"

void TerrainManager::lua_access() {
	auto& lua = LuaManager::get_instance().get_state();

	auto terrain_table = lua.create_named_table("Terrain");

	terrain_table.set_function("load_terrain", &TerrainManager::load_terrain,
	                           this);

	terrain_table["get_height"] = [this](const std::string& terrain_name,
	                                     const glm::vec3& position,
	                                     const glm::vec3& scale) {
		auto& terrain = terrain_map_.at(terrain_name);
		terrain.set_scale(scale);
		return terrain.get_height_world(position.x, position.z);
	};

	terrain_table["get_width"] = [this](const std::string& terrain_name) {
		return terrain_map_.at(terrain_name).get_width();
	};

	terrain_table["get_length"] = [this](const std::string& terrain_name) {
		return terrain_map_.at(terrain_name).get_length();
	};

	terrain_table["get_origin"] = [this](const std::string& terrain_name,
	                                     const glm::vec3& scale) {
		auto& terrain = terrain_map_.at(terrain_name);
		terrain.set_scale(scale);
		return terrain.get_origin();
	};
}

void TerrainManager::load_terrain(const std::string& terrain_name,
                                  const std::string& heightmap) {
	TexturedTerrain& terrain = terrain_map_[terrain_name];

	terrain.load_heightfield(heightmap.c_str());
	terrain.load_mesh();
}

TexturedTerrain& TerrainManager::get_terrain(const std::string& terrain_name) {
	return terrain_map_[terrain_name];
}