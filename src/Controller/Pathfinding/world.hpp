#pragma once

#include <queue>
#include <vector>
#include "Controller/Pathfinding/AStarInterface.h"
#include "Controller/Pathfinding/AStar.h"
#include <glm/glm.hpp>
#include "Controller/Terrain/TexturedTerrain.hpp"
#include "Controller/Terrain/TerrainManager.hpp"

class world {
public:
	/**
	 * @brief	Sets the world
	 */
	void setWorld(std::string name);

	/**
	 * @brief	Prints the current pathfinding grid to the terrminal
	 */
	void show_world();

	/**
	 * @brief	Sets the min & max height for the playable area for the NPC's
	 * @param	min	- The min height allowed e.g., set lower limit above water.
	 * @param	max	- The max height allowed
	 */
	void setMinMaxHeight(float min, float max);

	/**
	 * @brief	Sets the maximum distance the pathfinding can go before giving
	 * up
	 * @param	nax_distance	- The maximum distance allowed to travel
	 */
	void setMaxDistance(int max_distance);

	/**
	 * @brief	Create a sphere obstruction on the pathfinding grid
	 * @param	posX	- The x position of the object
	 * @param	posZ	- The z position of the object
	 * @param	radius	- The radius of the object
	 */
	void create_sphere_obstruction(float posX, float posZ, float radius);

	/**
	 * @brief	Create a box obstruction on the pathfinding grid
	 * @param	posX	- The x position of the object
	 * @param	posZ	- The z position of the object
	 * @param	xSize	- The HALF size of the box in the x direction
	 * @param	zSize	- The HALF size of the box in the z direction
	 */
	void create_box_obstruction(float posX, float posZ, float xSize,
	                            float zSize);

	/**
	 * @brief	Gets the height (y) coordinate based on x & z
	 * @param	x	- The x position
	 * @param	z	- The z position
	 */
	float get_height(float x, float z);

	/**
	 * @brief	Generates a queue of vector 2 using the pathfinding algorithm
	 * between two points
	 * @param	currX	- The current x position
	 * @param	currZ	- The current z position
	 * @param	targetX	- The x target position
	 * @param	targetZ	- The z target position
	 */
	std::queue<glm::vec2> pathFinding(float currX, float currZ, float targetX,
	                                  float targetZ);

	/**
	 * @brief	Destructor
	 */
	~world();

private:
	/// The a* interface whch holds the level's grid
	AStar m_aStar;

	/// The minimum height allowed
	float m_min_height = 10;
	/// The maximum height allowed
	float m_max_height = 9999;

	/// Creates the grid for the pathfinding algorithm
	void create_grid(std::vector<std::vector<int>>& grid, TexturedTerrain& tt);
};
