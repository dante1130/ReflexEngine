#ifndef ASTAR_H
#define ASTAR_H

#include <math.h>
#include <vector>

enum AStarExceptions {
	ALREADY_AT_DESTINATION,
	START_OUT_OF_BOUNDS,
	GOAL_OUT_OF_BOUNDS,
	START_BLOCKED,
	GOAL_BLOCKED,
	NO_PATH_FOUND,
	NO_PATH_BELOW_LIMIT,
	MAX_DISTANCE_REACHED,
	GRID_UNINITIALISED
};

struct node {
	/// <summary>
	/// The x position
	/// </summary>
	int x = 0;

	/// <summary>
	/// The y position
	/// </summary>
	int y = 0;
};

struct DistanceNode {
	/// <summary>
	/// The position of the parentNode. (i.e node used to get to it)
	/// </summary>
	node parentNode = node();

	/// <summary>
	/// Sum of the exact cost and estimated cost
	/// </summary>
	float f = 0.0F;

	/// <summary>
	/// Exact cost from starting ponit to current vertex
	/// </summary>
	float g = 0.0F;

	/// <summary>
	/// Heuristic estimated cost from current vertex to destination
	/// </summary>
	float h = 0.0F;
};

namespace aStar {
/**
 * @brief	The heart of the A star search algorithm
 *
 * @param	grid				- The grid of the area you are trying to move
 * through
 * @param	movementCost		- [0] - horizontal movement cost [1] - diagonal
 * movement cost [2] - allow diagonal movement
 * @param	heuristicsCostScale	- Change importance of speed or accuracy
 * @param	gridSize			- The size of the grid [0] - x size, [1] - y
 * size
 * @param	start				- The starting position
 * @param	goal				- The goal position
 * @param	maxDistance			- The max distance the path can be
 *
 * @throws	AStarException
 *
 * @return	An 2D distance node array to the grid size which has the path.
 */
std::vector<std::vector<DistanceNode>> aStarSearch(
    const std::vector<std::vector<int>> grid, const float movementCost[3],
    const float heuristicsCostScale, const int gridSize[2], const node start,
    const node goal, const float maxDistance);

/**
 * @brief	Sets up the inital grid with default values
 *
 * @param	&grid		- The grid
 * @param	gridSize	- The size of the grid
 * @param	start		- The starting position node
 */
void InitDefaultGrid(std::vector<std::vector<DistanceNode>> &grid,
                     const int gridSize[2], const node start);

/**
 * @brief	Estimates distance between the current position and the goal using
 * manhattan heuristic. I.e. cannot go diagonal
 *
 * @param	movementCost	- The movementCost to move horizontally
 * @param	pos				- The location of the position to start from
 * @param	goal			- The location of the position of the goal
 *
 * @return	The shortest estimated difference from the current position and goal
 */
float ManhattanHeuristic(const float movementCost, node pos, const node goal);

/**
 * @brief	Estimates distance between the current position and the goal using
 * diagonal heuristic. I.e. Can go diagonal
 *
 * @param	movementCostManhattan	- The movementCost to move horizontally
 * @param	movementCostDiagonal	- The movementCost to move diagonally
 * @param	pos						- The location of the position to start from
 * @param	goal					- The location of the position of the goal
 *
 * @return	The shortest estimated difference from the current position and goal
 */
float DiagonalHeuristic(const float movementCostManhattan,
                        const float movementCostDiagonal, node pos,
                        const node goal);

/**
 * @brief	Checks if the position is at the goal
 *
 * @param	pos						- The location of the position to start from
 * @param	goal					- The location of the position of the goal
 *
 * @return	True if position is at the goal else false
 */
bool IsDestination(node pos, const node goal);

/**
 * @brief	Checks that the position is inside the grid
 *
 * @param	pos		- The position of the node you want to check
 * @param	xSize	- The size of the grid in the x direction
 * @param	ySize	- The size of the grid in the y direction
 *
 * @return	true if inside else false
 */
bool ValidPosition(node pos, int xSize, int ySize);

/**
 * @brief	Checks that the cell is not blocked and can be moved into
 *
 * @param	pos		- The position of the node you want to check
 * @param	&grid	- The grid
 *
 * @return	true if not blocked else false
 */
bool CellNotBlocked(node pos, const std::vector<std::vector<int>> &grid);

/**
 * @brief	Finds the nodes with the smallest distance cost and processes it
 *
 * @param	nodesToCheck	- A 2D vector which stores all the nodes that need
 * to be processed
 *
 * @return	int				- A value of the index with the lowest cost
 */
int FindLowestCost(std::vector<DistanceNode> &nodesToCheck);

}  // namespace aStar

#endif
