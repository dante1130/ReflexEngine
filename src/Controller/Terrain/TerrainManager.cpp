#include "TerrainManager.hpp"

void OldTerrainManager::lua_access() {
	sol::state& lua = LuaManager::get_instance().get_state();

	lua.set_function("get_y_coord_on_floor", &OldTerrainManager::getHeight);
}

void OldTerrainManager::setPlayableArea(TexturedTerrain* tt, float scale,
                                        int size) {
	m_tt = tt;
	m_playable_floor_size = size;
	m_playable_floor_y_scale = scale;
}

float OldTerrainManager::getHeight(float x, float z) {
	return m_tt->get_height_world(x - m_playable_floor_size / 2,
	                              z - m_playable_floor_size / 2) *
	       m_playable_floor_y_scale;
}

TexturedTerrain* OldTerrainManager::getTTerrain() { return m_tt; }
