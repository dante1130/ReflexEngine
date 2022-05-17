#pragma once

#include <queue>
#include <vector>
#include "Controller/Pathfinding/AStarInterface.h"
#include "Controller/Pathfinding/AStar.h"
#include <glm/glm.hpp>
#include "Controller/Terrain/TexturedTerrain.hpp"
#include "Controller/GenericFunctions.h"

class world {
public:
	void setWorld(TexturedTerrain* tt);

	void setMinMaxHeight(float min, float max);

	float get_height(float x, float z);

	std::queue<glm::vec2> pathFinding(float currX, float currZ, float targetX,
	                                  float targetZ);

	~world();

private:
	AStar m_aStar;
	TexturedTerrain* m_tt;

	float m_min_height = 2;
	float m_max_height = 9999;

	void create_grid(std::vector<std::vector<int>>& grid);
};
