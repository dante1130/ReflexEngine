#include "AStar.h"

#define baseParent -1
#define baseCost 9999999999

//////////////////////////////////
// OPERATION FUNCTIONS/////////////
//////////////////////////////////
std::vector<std::vector<DistanceNode>> aStar::aStarSearch(
    std::vector<std::vector<int>> grid, const float movementCost[3],
    const float heuristicsCostScale, const int gridSize[2], const node start,
    const node goal, const float maxDistance) {
	// Init grid used to store path
	std::vector<std::vector<DistanceNode>> distanceGrid;

	// Init grid default values & starting node
	InitDefaultGrid(distanceGrid, gridSize, start);

	// Make sure nodes are available
	if (IsDestination(start, goal) == true) throw(ALREADY_AT_DESTINATION);

	if (ValidPosition(start, gridSize[1], gridSize[0]) == false)
		throw(START_OUT_OF_BOUNDS);
	if (ValidPosition(goal, gridSize[1], gridSize[0]) == false)
		throw(GOAL_OUT_OF_BOUNDS);

	if (CellNotBlocked(start, grid) == false) throw(START_BLOCKED);
	if (CellNotBlocked(goal, grid) == false) throw(GOAL_BLOCKED);

	// Nodes which need to be checked for a shorter path
	std::vector<DistanceNode> nodesToCheck;

	// The nodes which have been already processed - set them to default false
	std::vector<std::vector<bool>> nodesChecked;
	std::vector<bool> row;
	for (int count = 0; count < gridSize[1]; count++) {
		row.push_back(false);
	}
	for (int count = 0; count < gridSize[0]; count++) {
		nodesChecked.push_back(row);
	}

	// Initialise nodeToCheck with inital node
	DistanceNode tempDistanceNode;
	tempDistanceNode.parentNode.x = start.x;
	tempDistanceNode.parentNode.y = start.y;
	tempDistanceNode.f = 0;

	nodesToCheck.push_back(tempDistanceNode);

	// If destination has been reached
	bool pathFound = false;

	DistanceNode distanceNodeChoosen, toAdd;
	int smallestIndex;
	node pos;
	int i = start.x, j = start.y;
	float gNew, hNew, fNew;

	// std::cout << "Movement Cost: " << movementCost[0] << ' ' <<
	// movementCost[1] << ' ' << movementCost[2] << std::endl;

	while (!nodesToCheck.empty() && pathFound == false) {
		// Finds smallest nodes in nodesToCheck and removes it from list and
		// processes it
		smallestIndex = FindLowestCost(nodesToCheck);
		distanceNodeChoosen = nodesToCheck[smallestIndex];

		if (distanceNodeChoosen.f > maxDistance) {
			throw(MAX_DISTANCE_REACHED);
		}
		// std::cout << "\n==ParentNode " << distanceNodeChoosen.parentNode.y <<
		// " " << distanceNodeChoosen.parentNode.x << std::endl;

		nodesToCheck.erase(nodesToCheck.begin() + smallestIndex);

		nodesChecked[distanceNodeChoosen.parentNode.y]
		            [distanceNodeChoosen.parentNode.x] = true;

		i = distanceNodeChoosen.parentNode.x;
		j = distanceNodeChoosen.parentNode.y;

		// Processes all nodes next to the choosen node which was found above
		for (int y = -1; y < 2; y++) {
			for (int x = -1; x < 2; x++) {
				if (y == 0 && x == 0) {
					continue;
				}

				if (movementCost[2] ==
				    0)  // Do not use diagonal if movementCost[2] == 0
				{
					if (y != 0 && x != 0) {
						continue;
					}
				}

				pos.x = i + x;
				pos.y = j + y;

				if (!ValidPosition(pos, gridSize[1], gridSize[0])) {
					continue;
				}
				// std::cout << "POS" << pos.y << ' ' << pos.x << ' ';

				if (IsDestination(pos, goal)) {
					pathFound = true;
					distanceGrid[pos.y][pos.x].parentNode.x = i;
					distanceGrid[pos.y][pos.x].parentNode.y = j;
					break;
				} else if (nodesChecked[pos.y][pos.x] == false &&
				           CellNotBlocked(pos, grid)) {
					if (y != 0 && x != 0) {
						gNew = distanceGrid[j][i].g + movementCost[1];
					}  // diagonal movement exact
					else {
						gNew = distanceGrid[j][i].g + movementCost[0];
					}  // non-diagonal movement exact

					if (movementCost[2] == 1) {
						hNew = DiagonalHeuristic(movementCost[0],
						                         movementCost[1], pos, goal);
					}  // diagonal movement estimate
					else {
						hNew = ManhattanHeuristic(movementCost[0], pos, goal);
					}  // non-diagonal movement estimate

					fNew = gNew + (heuristicsCostScale * hNew);
					// std::cout << " gNew: " << gNew << " - hNew: " << hNew <<
					// " - fNew: " << fNew << std::endl;

					if (distanceGrid[pos.y][pos.x].f == baseCost ||
					    distanceGrid[pos.y][pos.x].f > fNew) {
						toAdd.parentNode.x = pos.x;
						toAdd.parentNode.y = pos.y;
						toAdd.f = fNew;
						nodesToCheck.push_back(toAdd);

						distanceGrid[pos.y][pos.x].f = fNew;
						distanceGrid[pos.y][pos.x].h = hNew;
						distanceGrid[pos.y][pos.x].g = gNew;
						distanceGrid[pos.y][pos.x].parentNode.x = i;
						distanceGrid[pos.y][pos.x].parentNode.y = j;
					}
				}
			}
			if (pathFound) {
				break;
			}
		}
	}

	if (pathFound == false) throw(NO_PATH_FOUND);

	return distanceGrid;
}

void aStar::InitDefaultGrid(
    std::vector<std::vector<DistanceNode>> &distanceGrid, const int gridSize[2],
    const node start) {
	DistanceNode defaultDistanceNode;
	defaultDistanceNode.parentNode.x = baseParent;
	defaultDistanceNode.parentNode.y = baseParent;
	defaultDistanceNode.f = baseCost;
	defaultDistanceNode.g = baseCost;
	defaultDistanceNode.h = baseCost;

	std::vector<DistanceNode> row;
	for (int count = 0; count < gridSize[1]; count++) {
		row.push_back(defaultDistanceNode);
	}
	for (int count = 0; count < gridSize[0]; count++) {
		distanceGrid.push_back(row);
	}

	distanceGrid[start.y][start.x].parentNode.x = start.x;
	distanceGrid[start.y][start.x].parentNode.y = start.y;
	distanceGrid[start.y][start.x].f = 0;
	distanceGrid[start.y][start.x].g = 0;
	distanceGrid[start.y][start.x].h = 0;

	return;
}

//////////////////////////////////
// HEURISTIC FUNCTIONS/////////////
//////////////////////////////////
float aStar::ManhattanHeuristic(const float movementCost, node pos,
                                const node goal) {
	return movementCost * (abs(pos.x - goal.x) + abs(pos.y - goal.y));
}

float aStar::DiagonalHeuristic(const float movementCostManhattan,
                               const float movementCostDiagonal, node pos,
                               const node goal) {
	float dx = abs(pos.x - goal.x);
	float dy = abs(pos.y - goal.y);

	float min;
	if (dx < dy) {
		min = dx;
	} else {
		min = dy;
	}

	return movementCostManhattan * (dx + dy) +
	       (movementCostDiagonal - 2 * movementCostManhattan) * min;
}

//////////////////////////////////
// UTILITY FUNCTIONS///////////////
//////////////////////////////////
int aStar::FindLowestCost(std::vector<DistanceNode> &nodesToCheck) {
	int size = nodesToCheck.size();
	int smallest = 0;

	for (int count = 1; count < size; count++) {
		if (nodesToCheck[smallest].f > nodesToCheck[count].f) smallest = count;
	}

	return smallest;
}

bool aStar::IsDestination(const node pos, node goal) {
	if (pos.x == goal.x && pos.y == goal.y) {
		return true;
	} else {
		return false;
	}
}

bool aStar::ValidPosition(node pos, int xSize, int ySize) {
	if (pos.x >= xSize || pos.x < 0) return false;
	if (pos.y >= ySize || pos.y < 0) return false;

	return true;
}

bool aStar::CellNotBlocked(node pos,
                           const std::vector<std::vector<int>> &grid) {
	if (grid[pos.y][pos.x] == 0) return true;

	return false;
}