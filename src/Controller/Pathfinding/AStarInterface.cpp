#include "AStarInterface.h"

#include <iostream>
#include <stack>

AStar::AStar()
    : heuristicsCostScale(1.2F), maxDistance(1000), grid_ratio_(1.0F) {
	movementCosts[0] = 1;
	movementCosts[1] = 1.414;
	movementCosts[2] = 0;

	gridSize[0] = 0;
	gridSize[1] = 0;

	start_offset_[0] = 0;
	start_offset_[1] = 0;
}

auto AStar::findPath(float xStart, float yStart, float xEnd, float yEnd)
    -> std::queue<std::pair<float, float>> {
	if (grid.empty()) {
		throw(GRID_UNINITIALISED);
	}

	node start;
	start.x = static_cast<int>((xStart - start_offset_[1]) * grid_ratio_);
	start.y = static_cast<int>((yStart - start_offset_[0]) * grid_ratio_);
	node end;
	end.x = static_cast<int>((xEnd - start_offset_[1]) * grid_ratio_);
	end.y = static_cast<int>((yEnd - start_offset_[0]) * grid_ratio_);

	std::vector<std::vector<DistanceNode>> path;

	path = aStar::aStarSearch(grid, movementCosts, heuristicsCostScale,
	                          gridSize, start, end, maxDistance);

	std::stack<std::pair<float, float>> reversed_path;

	auto x_pos = end.x;
	auto y_pos = end.y;
	auto found = false;
	auto max_dist = static_cast<int>(maxDistance);
	for (auto count = 0; count < max_dist; ++count) {
		auto pair = std::pair<float, float>(path[y_pos][x_pos].parentNode.x,
		                                    path[y_pos][x_pos].parentNode.y);

		x_pos = static_cast<int>(pair.first);
		y_pos = static_cast<int>(pair.second);

		pair.second = (pair.first + start_offset_[1]) / grid_ratio_;
		pair.second = (pair.second + start_offset_[1]) / grid_ratio_;

		reversed_path.push(pair);

		if (x_pos == end.x && y_pos == end.y) {
			found = true;
			break;
		}
	}

	if (!found) {
		return std::queue<std::pair<float, float>>();
	}

	std::queue<std::pair<float, float>> processed_path;
	auto path_size = reversed_path.size();
	for (auto count = 0; count < path_size; ++count) {
		processed_path.push(reversed_path.top());
		reversed_path.pop();
	}
	return processed_path;
}

void AStar::printAstarException(int val) {
	switch (val) {
		case ALREADY_AT_DESTINATION:
			std::cout << "EXCEPTION: Already at destionation" << std::endl;
			break;

		case START_OUT_OF_BOUNDS:
			std::cout << "EXCEPTION: Start out of bounds" << std::endl;
			break;

		case GOAL_OUT_OF_BOUNDS:
			std::cout << "EXCEPTION: Goal out of bounds" << std::endl;
			break;

		case START_BLOCKED:
			std::cout << "EXCEPTION: Start blocked" << std::endl;
			break;

		case GOAL_BLOCKED:
			std::cout << "EXCEPTION: Goal blocked" << std::endl;
			break;

		case NO_PATH_FOUND:
			std::cout << "EXCEPTION: No path found" << std::endl;
			break;

		case NO_PATH_BELOW_LIMIT:
			std::cout << "EXCEPTION: No path below limit" << std::endl;
			break;
		case MAX_DISTANCE_REACHED:
			std::cout << "EXCEPTION: Max distance reached" << std::endl;
			break;
		case GRID_UNINITIALISED:
			std::cout << "EXCEPTION: Grid is not initialised" << std::endl;
			break;
		default:
			std::cout << "EXCEPTION: Undocumented exception (" << val
			          << "): Check AStar.h for more detail" << std::endl;
	}
}

bool AStar::setGrid(std::vector<std::vector<int>>& newGrid) {
	grid = std::move(newGrid);

	gridSize[0] = grid.size();
	gridSize[1] = grid[0].size();

	return true;
}

bool AStar::setDiagonalMovementCost(float val) {
	if (val < 0) {
		movementCosts[1] = 1.414;
		return false;
	}

	movementCosts[1] = val;

	return true;
}

bool AStar::setNonDiagonalMovementCost(float val) {
	if (val < 0) {
		movementCosts[0] = 1;
		return false;
	}

	movementCosts[0] = val;

	return true;
}

void AStar::setAllowDiagonalMovement(bool allow) {
	if (allow) {
		movementCosts[2] = 1;
	} else {
		movementCosts[2] = 0;
	}
}

bool AStar::setHeuristicsCostScale(float val) {
	if (val < 0) {
		heuristicsCostScale = 1;
		return false;
	}

	heuristicsCostScale = val;

	return true;
}

bool AStar::setGridSizeX(int xSize) {
	if (xSize < 1) {
		gridSize[1] = 1;
		return false;
	}

	gridSize[1] = xSize;

	return true;
}

bool AStar::setGridSizeY(int ySize) {
	if (ySize < 1) {
		gridSize[0] = 1;
		return false;
	}

	gridSize[0] = ySize;

	return true;
}

bool AStar::setMaxDistance(float val) {
	if (val < 1) {
		maxDistance = 1;
		return false;
	}

	maxDistance = val;

	return true;
}

std::vector<std::vector<int>>& AStar::getGrid() { return grid; }

auto AStar::set_grid_ratio(float ratio) -> void {
	if (ratio <= 0) {
		return;
	}
	grid_ratio_ = ratio;
}
auto AStar::get_grid_ratio() -> float { return grid_ratio_; }

auto AStar::set_grid_offset(float x_offset, float y_offset) -> void {
	start_offset_[1] = x_offset;
	start_offset_[0] = y_offset;
}

auto AStar::get_grid_offset() -> std::pair<float, float> {
	return std::pair<float, float>(start_offset_[1], start_offset_[0]);
}

auto AStar::set_coordiante_value(float x_point, float y_point, int new_value)
    -> bool {
	x_point = (x_point - start_offset_[1]) * grid_ratio_;
	y_point = (y_point - start_offset_[0]) * grid_ratio_;

	int x_coord = static_cast<int>(x_point);
	int y_coord = static_cast<int>(y_point);

	if (x_coord >= gridSize[1] || y_coord >= gridSize[0]) {
		return false;
	}
	grid[x_coord][y_coord] = new_value;
	return true;
}

auto AStar::print_grid() -> void {
	for (int count = 0; count < gridSize[0]; count++) {
		for (int countTwo = 0; countTwo < gridSize[1]; countTwo++) {
			std::cout << grid[count][countTwo] << ' ';
		}
		std::cout << std::endl;
	}
}