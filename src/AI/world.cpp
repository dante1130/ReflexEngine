#include "world.hpp"

void world::setWorld(TexturedTerrain* tt) {
	m_tt = tt;

	std::vector<std::vector<int>> grid;
	create_grid(grid);
	m_aStar.setGrid(grid);
	m_aStar.setAllowDiagonalMovement(true);
	m_aStar.setHeuristicsCostScale(3);
	// m_aStar.setMaxDistance(100);
}

void world::setMinMaxHeight(float min, float max) {
	m_min_height = min;
	m_max_height = max;

	if (m_min_height > m_max_height) {
		std::cerr << "world - setMinMaxHeight - min is greater than max - "
		          << m_min_height << " vs " << m_max_height;
	}
}

float world::get_height(float x, float z) { return m_tt->get_height(x, z); }

std::queue<glm::vec2> world::pathFinding(float currX, float currZ,
                                         float targetX, float targetZ) {
	std::queue<glm::vec2> path;
	std::vector<glm::vec2> inversePath;
	std::vector<std::vector<DistanceNode>> rawPath;

	try {
		rawPath = m_aStar.findPath((int)currX, (int)currZ, (int)targetX,
		                           (int)targetZ);
	} catch (AStarExceptions error) {
		m_aStar.printAstarException(error);

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

		inversePath.push_back(glm::vec2(end.x, end.y));

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

	for (int z = 0; z < m_tt->get_length(); z++) {
		gridRow.clear();

		for (int x = 0; x < m_tt->get_width(); x++) {
			gridValue = 0;
			height = GenericFunctions::getHeight(x, z);

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
