#include <catch2/catch_test_macros.hpp>

#include <vector>

#include "Controller/Pathfinding/AStarInterface.h"

#include <iostream>

TEST_CASE("A Star Pathfinding", "[AStarTest]") {
	AStar level;

	const auto X_OFFSET = 32.5F;
	const auto Y_OFFSET = 10.25F;
	const auto RATIO = 1.5F;

	level.set_grid_offset(X_OFFSET, Y_OFFSET);
	SECTION("Ability to set the grid offset") {
		REQUIRE(level.get_grid_offset().first == X_OFFSET);
		REQUIRE(level.get_grid_offset().second == Y_OFFSET);
	}

	level.set_grid_ratio(RATIO);
	SECTION("Ability to set the grid ratio") {
		REQUIRE(level.get_grid_ratio() == RATIO);
	}

	std::vector<std::vector<int>> grid;
	const auto Y_SIZE = 7;
	const auto X_SIZE = 5;
	grid.resize(Y_SIZE);
	for (int count = 0; count < Y_SIZE; ++count) {
		grid[count].resize(X_SIZE);
		for (int countTwo = 0; countTwo < X_SIZE; ++countTwo) {
			grid[count][countTwo] = 0;
		}
	}

	// Blocked squares
	grid[0][1] = 1;
	grid[0][3] = 1;
	grid[1][3] = 1;
	grid[2][0] = 1;
	grid[2][3] = 1;
	grid[3][2] = 1;
	grid[3][3] = 1;
	grid[4][1] = 1;
	grid[4][2] = 1;
	grid[5][1] = 1;

	level.setGrid(grid);
	SECTION("Ability to set the grid") {
		auto retrieved_grid = level.getGrid();

		REQUIRE(retrieved_grid.size() == Y_SIZE);
		REQUIRE(retrieved_grid[0].size() == X_SIZE);

		REQUIRE(retrieved_grid[0][0] == 0);
		REQUIRE(retrieved_grid[0][1] == 1);
		REQUIRE(retrieved_grid[0][2] == 0);
		REQUIRE(retrieved_grid[0][3] == 1);
		REQUIRE(retrieved_grid[0][4] == 0);

		REQUIRE(retrieved_grid[1][0] == 0);
		REQUIRE(retrieved_grid[1][1] == 0);
		REQUIRE(retrieved_grid[1][2] == 0);
		REQUIRE(retrieved_grid[1][3] == 1);
		REQUIRE(retrieved_grid[1][4] == 0);

		REQUIRE(retrieved_grid[2][0] == 1);
		REQUIRE(retrieved_grid[2][1] == 0);
		REQUIRE(retrieved_grid[2][2] == 0);
		REQUIRE(retrieved_grid[2][3] == 1);
		REQUIRE(retrieved_grid[2][4] == 0);

		REQUIRE(retrieved_grid[3][0] == 0);
		REQUIRE(retrieved_grid[3][1] == 0);
		REQUIRE(retrieved_grid[3][2] == 1);
		REQUIRE(retrieved_grid[3][3] == 1);
		REQUIRE(retrieved_grid[3][4] == 0);

		REQUIRE(retrieved_grid[4][0] == 0);
		REQUIRE(retrieved_grid[4][1] == 1);
		REQUIRE(retrieved_grid[4][2] == 1);
		REQUIRE(retrieved_grid[4][3] == 0);
		REQUIRE(retrieved_grid[4][4] == 0);

		REQUIRE(retrieved_grid[5][0] == 0);
		REQUIRE(retrieved_grid[5][1] == 1);
		REQUIRE(retrieved_grid[5][2] == 0);
		REQUIRE(retrieved_grid[5][3] == 0);
		REQUIRE(retrieved_grid[5][4] == 0);

		REQUIRE(retrieved_grid[6][0] == 0);
		REQUIRE(retrieved_grid[6][1] == 0);
		REQUIRE(retrieved_grid[6][2] == 0);
		REQUIRE(retrieved_grid[6][3] == 0);
		REQUIRE(retrieved_grid[6][4] == 0);
	}

	level.set_coordinate_value((3 / RATIO + X_OFFSET), (5 / RATIO + Y_OFFSET),
	                           1);
	SECTION("Ability to set singular point on grid") {
		auto retrieved_grid = level.getGrid();
		REQUIRE(retrieved_grid.size() == Y_SIZE);
		REQUIRE(retrieved_grid[0].size() == X_SIZE);

		REQUIRE(retrieved_grid[0][0] == 0);
		REQUIRE(retrieved_grid[0][1] == 1);
		REQUIRE(retrieved_grid[0][2] == 0);
		REQUIRE(retrieved_grid[0][3] == 1);
		REQUIRE(retrieved_grid[0][4] == 0);

		REQUIRE(retrieved_grid[1][0] == 0);
		REQUIRE(retrieved_grid[1][1] == 0);
		REQUIRE(retrieved_grid[1][2] == 0);
		REQUIRE(retrieved_grid[1][3] == 1);
		REQUIRE(retrieved_grid[1][4] == 0);

		REQUIRE(retrieved_grid[2][0] == 1);
		REQUIRE(retrieved_grid[2][1] == 0);
		REQUIRE(retrieved_grid[2][2] == 0);
		REQUIRE(retrieved_grid[2][3] == 1);
		REQUIRE(retrieved_grid[2][4] == 0);

		REQUIRE(retrieved_grid[3][0] == 0);
		REQUIRE(retrieved_grid[3][1] == 0);
		REQUIRE(retrieved_grid[3][2] == 1);
		REQUIRE(retrieved_grid[3][3] == 1);
		REQUIRE(retrieved_grid[3][4] == 0);

		REQUIRE(retrieved_grid[4][0] == 0);
		REQUIRE(retrieved_grid[4][1] == 1);
		REQUIRE(retrieved_grid[4][2] == 1);
		REQUIRE(retrieved_grid[4][3] == 0);
		REQUIRE(retrieved_grid[4][4] == 0);

		REQUIRE(retrieved_grid[5][0] == 0);
		REQUIRE(retrieved_grid[5][1] == 1);
		REQUIRE(retrieved_grid[5][2] == 0);
		REQUIRE(retrieved_grid[5][3] == 1);
		REQUIRE(retrieved_grid[5][4] == 0);

		REQUIRE(retrieved_grid[6][0] == 0);
		REQUIRE(retrieved_grid[6][1] == 0);
		REQUIRE(retrieved_grid[6][2] == 0);
		REQUIRE(retrieved_grid[6][3] == 0);
		REQUIRE(retrieved_grid[6][4] == 0);
	}

	SECTION("Basic pathfinding test") {
		auto path =
		    level.findPath((0 / RATIO + X_OFFSET), (1 / RATIO + Y_OFFSET),
		                   (4 / RATIO + X_OFFSET), (1 / RATIO + Y_OFFSET));

		REQUIRE(path.size() == 16);

		auto pair = path.front();
		path.pop();
		pair.first = (pair.first - X_OFFSET) * RATIO;
		pair.second = (pair.second - Y_OFFSET) * RATIO;
		REQUIRE((static_cast<int>(round(pair.first)) == 1 &&
		         static_cast<int>(round(pair.second)) == 1));

		pair = path.front();
		path.pop();
		pair.first = (pair.first - X_OFFSET) * RATIO;
		pair.second = (pair.second - Y_OFFSET) * RATIO;
		REQUIRE((static_cast<int>(round(pair.first)) == 1 &&
		         static_cast<int>(round(pair.second)) == 2));

		pair = path.front();
		path.pop();
		pair.first = (pair.first - X_OFFSET) * RATIO;
		pair.second = (pair.second - Y_OFFSET) * RATIO;
		REQUIRE((static_cast<int>(round(pair.first)) == 1 &&
		         static_cast<int>(round(pair.second)) == 3));

		pair = path.front();
		path.pop();
		pair.first = (pair.first - X_OFFSET) * RATIO;
		pair.second = (pair.second - Y_OFFSET) * RATIO;
		REQUIRE((static_cast<int>(round(pair.first)) == 0 &&
		         static_cast<int>(round(pair.second)) == 3));

		pair = path.front();
		path.pop();
		pair.first = (pair.first - X_OFFSET) * RATIO;
		pair.second = (pair.second - Y_OFFSET) * RATIO;
		REQUIRE((static_cast<int>(round(pair.first)) == 0 &&
		         static_cast<int>(round(pair.second)) == 4));

		pair = path.front();
		path.pop();
		pair.first = (pair.first - X_OFFSET) * RATIO;
		pair.second = (pair.second - Y_OFFSET) * RATIO;
		REQUIRE((static_cast<int>(round(pair.first)) == 0 &&
		         static_cast<int>(round(pair.second)) == 5));

		pair = path.front();
		path.pop();
		pair.first = (pair.first - X_OFFSET) * RATIO;
		pair.second = (pair.second - Y_OFFSET) * RATIO;
		REQUIRE((static_cast<int>(round(pair.first)) == 0 &&
		         static_cast<int>(round(pair.second)) == 6));

		pair = path.front();
		path.pop();
		pair.first = (pair.first - X_OFFSET) * RATIO;
		pair.second = (pair.second - Y_OFFSET) * RATIO;
		REQUIRE((static_cast<int>(round(pair.first)) == 1 &&
		         static_cast<int>(round(pair.second)) == 6));

		pair = path.front();
		path.pop();
		pair.first = (pair.first - X_OFFSET) * RATIO;
		pair.second = (pair.second - Y_OFFSET) * RATIO;
		REQUIRE((static_cast<int>(round(pair.first)) == 2 &&
		         static_cast<int>(round(pair.second)) == 6));

		pair = path.front();
		path.pop();
		pair.first = (pair.first - X_OFFSET) * RATIO;
		pair.second = (pair.second - Y_OFFSET) * RATIO;
		REQUIRE((static_cast<int>(round(pair.first)) == 3 &&
		         static_cast<int>(round(pair.second)) == 6));

		pair = path.front();
		path.pop();
		pair.first = (pair.first - X_OFFSET) * RATIO;
		pair.second = (pair.second - Y_OFFSET) * RATIO;
		REQUIRE((static_cast<int>(round(pair.first)) == 4 &&
		         static_cast<int>(round(pair.second)) == 6));

		pair = path.front();
		path.pop();
		pair.first = (pair.first - X_OFFSET) * RATIO;
		pair.second = (pair.second - Y_OFFSET) * RATIO;
		REQUIRE((static_cast<int>(round(pair.first)) == 4 &&
		         static_cast<int>(round(pair.second)) == 5));

		pair = path.front();
		path.pop();
		pair.first = (pair.first - X_OFFSET) * RATIO;
		pair.second = (pair.second - Y_OFFSET) * RATIO;
		REQUIRE((static_cast<int>(round(pair.first)) == 4 &&
		         static_cast<int>(round(pair.second)) == 4));

		pair = path.front();
		path.pop();
		pair.first = (pair.first - X_OFFSET) * RATIO;
		pair.second = (pair.second - Y_OFFSET) * RATIO;
		REQUIRE((static_cast<int>(round(pair.first)) == 4 &&
		         static_cast<int>(round(pair.second)) == 3));

		pair = path.front();
		path.pop();
		pair.first = (pair.first - X_OFFSET) * RATIO;
		pair.second = (pair.second - Y_OFFSET) * RATIO;
		REQUIRE((static_cast<int>(round(pair.first)) == 4 &&
		         static_cast<int>(round(pair.second)) == 2));

		pair = path.front();
		path.pop();
		pair.first = (pair.first - X_OFFSET) * RATIO;
		pair.second = (pair.second - Y_OFFSET) * RATIO;
		REQUIRE((static_cast<int>(round(pair.first)) == 4 &&
		         static_cast<int>(round(pair.second)) == 1));
	}

	SECTION("Ability to reset the grid") {
		level.reset_grid_to_original();

		auto retrieved_grid = level.getGrid();

		REQUIRE(retrieved_grid.size() == Y_SIZE);
		REQUIRE(retrieved_grid[0].size() == X_SIZE);

		REQUIRE(retrieved_grid[0][0] == 0);
		REQUIRE(retrieved_grid[0][1] == 1);
		REQUIRE(retrieved_grid[0][2] == 0);
		REQUIRE(retrieved_grid[0][3] == 1);
		REQUIRE(retrieved_grid[0][4] == 0);

		REQUIRE(retrieved_grid[1][0] == 0);
		REQUIRE(retrieved_grid[1][1] == 0);
		REQUIRE(retrieved_grid[1][2] == 0);
		REQUIRE(retrieved_grid[1][3] == 1);
		REQUIRE(retrieved_grid[1][4] == 0);

		REQUIRE(retrieved_grid[2][0] == 1);
		REQUIRE(retrieved_grid[2][1] == 0);
		REQUIRE(retrieved_grid[2][2] == 0);
		REQUIRE(retrieved_grid[2][3] == 1);
		REQUIRE(retrieved_grid[2][4] == 0);

		REQUIRE(retrieved_grid[3][0] == 0);
		REQUIRE(retrieved_grid[3][1] == 0);
		REQUIRE(retrieved_grid[3][2] == 1);
		REQUIRE(retrieved_grid[3][3] == 1);
		REQUIRE(retrieved_grid[3][4] == 0);

		REQUIRE(retrieved_grid[4][0] == 0);
		REQUIRE(retrieved_grid[4][1] == 1);
		REQUIRE(retrieved_grid[4][2] == 1);
		REQUIRE(retrieved_grid[4][3] == 0);
		REQUIRE(retrieved_grid[4][4] == 0);

		REQUIRE(retrieved_grid[5][0] == 0);
		REQUIRE(retrieved_grid[5][1] == 1);
		REQUIRE(retrieved_grid[5][2] == 0);
		REQUIRE(retrieved_grid[5][3] == 0);
		REQUIRE(retrieved_grid[5][4] == 0);

		REQUIRE(retrieved_grid[6][0] == 0);
		REQUIRE(retrieved_grid[6][1] == 0);
		REQUIRE(retrieved_grid[6][2] == 0);
		REQUIRE(retrieved_grid[6][3] == 0);
		REQUIRE(retrieved_grid[6][4] == 0);
	}
}