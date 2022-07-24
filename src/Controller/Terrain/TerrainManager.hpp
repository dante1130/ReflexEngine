#pragma once

#include "TexturedTerrain.hpp"
#include "Controller/LuaManager.hpp"

class OldTerrainManager {
public:
	/**
	 * @brief	Provides access to terrain data in lua
	 */
	static void lua_access();

	static void setPlayableArea(TexturedTerrain* tt, float scale, int size);

	static float getHeight(float x, float z);

	static TexturedTerrain* getTTerrain();

	//~TerrainManager();

private:
	inline static TexturedTerrain* m_tt;
	inline static int m_playable_floor_size;
	inline static float m_playable_floor_y_scale;
};
