#include "world.hpp"

void world::setWorld() {
	std::vector<std::vector<int>> grid;
	create_grid(grid);
	m_aStar.setGrid(grid);
	m_aStar.setAllowDiagonalMovement(true);
	m_aStar.setHeuristicsCostScale(1.5);
	m_aStar.setMaxDistance(100);
}

void world::show_world() {
	std::vector<std::vector<int>> gsa = m_aStar.getGrid();
	for (int count = gsa.size() - 1; count >= 0; count--) {
		for (int x = gsa[count].size() - 1; x >= 0; x--) {
			std::cout << gsa[count][x];
		}
		std::cout << std::endl;
	}
}

void world::setMinMaxHeight(float min, float max) {
	m_min_height = min;
	m_max_height = max;

	if (m_min_height > m_max_height) {
		std::cerr << "world - setMinMaxHeight - min is greater than max - "
		          << m_min_height << " vs " << m_max_height;
	}
}

void world::create_sphere_obstruction(float posX, float posZ, float radius) {
	std::vector<std::vector<int>> grid = m_aStar.getGrid();

	float checkRadius = radius / TerrainManager::getTTerrain()->get_scale().x;
	glm::vec2 pos =
	    glm::vec2(posX / TerrainManager::getTTerrain()->get_scale().x,
	              posZ / TerrainManager::getTTerrain()->get_scale().z);
	float distance = 0;

	checkRadius = std::ceil(checkRadius);

	int startY = pos.y - checkRadius;
	int endY = pos.y + checkRadius;
	if (startY < 0) {
		startY = 0;
	}
	if (endY > TerrainManager::getTTerrain()->get_length() - 1) {
		endY = TerrainManager::getTTerrain()->get_length() - 1;
	}
	int startX = pos.x - checkRadius;
	int endX = pos.x + checkRadius;
	if (startX < 0) {
		startX = 0;
	}
	if (endX > TerrainManager::getTTerrain()->get_width() - 1) {
		startX = TerrainManager::getTTerrain()->get_length() - 1;
	}

	for (int y = startY; y < endY; y++) {
		for (int x = startX; x < endX; x++) {
			distance = glm::length(pos - glm::vec2(x, y));
			if (distance < radius) {
				grid[y][x] = 1;
			}
		}
	}

	m_aStar.setGrid(grid);
}

void world::create_box_obstruction(float posX, float posZ, float xSize,
                                   float zSize) {
	std::vector<std::vector<int>> grid = m_aStar.getGrid();

	glm::vec2 pos =
	    glm::vec2(posX / TerrainManager::getTTerrain()->get_scale().x,
	              posZ / TerrainManager::getTTerrain()->get_scale().z);

	xSize = std::ceil(xSize / TerrainManager::getTTerrain()->get_scale().x);
	zSize = std::ceil(zSize / TerrainManager::getTTerrain()->get_scale().z);

	int startY = pos.y - zSize;
	int endY = pos.y + zSize;
	if (startY < 0) {
		startY = 0;
	}
	if (endY > TerrainManager::getTTerrain()->get_length() - 1) {
		endY = TerrainManager::getTTerrain()->get_length() - 1;
	}
	int startX = pos.x - xSize;
	int endX = pos.x + xSize;
	if (startX < 0) {
		startX = 0;
	}
	if (endX > TerrainManager::getTTerrain()->get_width() - 1) {
		startX = TerrainManager::getTTerrain()->get_length() - 1;
	}

	for (int y = startY; y < endY; y++) {
		for (int x = startX; x < endX; x++) {
			grid[y][x] = 1;
		}
	}

	m_aStar.setGrid(grid);
}

float world::get_height(float x, float z) {
	return TerrainManager::getTTerrain()->get_height(x, z);
}

std::queue<glm::vec2> world::pathFinding(float currX, float currZ,
                                         float targetX, float targetZ) {
	std::queue<glm::vec2> path;
	std::vector<glm::vec2> inversePath;
	std::vector<std::vector<DistanceNode>> rawPath;

	try {
		rawPath = m_aStar.findPath((int)currX, (int)currZ, (int)targetX,
		                           (int)targetZ);
	} catch (AStarExceptions error) {
		// m_aStar.printAstarException(error);

		return path;
	}
	glm::vec2 end = glm::vec2(targetX, targetZ);
	int temp;
	int numberOfIt = 0;

	bool running = true;

	while (running) {
		if ((int)currX == end.x && (int)currZ == end.y) {
			running = false;
		} else if (numberOfIt == 10000) {
			std::cout << "failed a*pathfinding" << std::endl;
			return path;
		}
		// std::cout << "Node: y = " << targetZ << " x = " << targetX
		//           << " cost = " << rawPath[end.y][end.x].f
		//           << " Parent: y: " << rawPath[end.y][end.x].parentNode.y
		//           << " x: " << rawPath[end.y][end.x].parentNode.x <<
		//           std::endl;

		inversePath.push_back(
		    glm::vec2(end.x * TerrainManager::getTTerrain()->get_scale().x,
		              end.y * TerrainManager::getTTerrain()->get_scale().z));

		temp = end.x;
		end.x = rawPath[end.y][end.x].parentNode.x;
		end.y = rawPath[end.y][temp].parentNode.y;
		numberOfIt++;
	}

	for (int count = inversePath.size() - 2; count >= 0; count--) {
		path.push(inversePath[count]);
	}

	return path;
}

world::~world() {  // delete m_tt;
}

void world::create_grid(std::vector<std::vector<int>>& grid) {
	float height = 0;
	int gridValue = 0;
	std::vector<int> gridRow;

	for (int z = 0; z < TerrainManager::getTTerrain()->get_length(); z++) {
		gridRow.clear();

		for (int x = 0; x < TerrainManager::getTTerrain()->get_width(); x++) {
			gridValue = 0;
			height = TerrainManager::getHeight(x, z);

			// Check if within min & max heights
			if (height < m_min_height || height > m_max_height) {
				gridValue = 1;
			} else {
				// Also check for objects
				// gridValue = checkIfNotInObject(x, z);
			}
			// std::cout << gridValue;

			gridRow.push_back(gridValue);
		}

		// std::cout << std::endl;
		grid.push_back(gridRow);
	}
}
