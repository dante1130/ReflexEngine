#ifndef ASTARINTERFACE_H
#define ASTARINTERFACE_H

#include "AStar.h"

#include <iostream>

#include <vector>

class AStar {
public:
	/**
	 * @brief	Default constructor
	 */
	AStar();

	/**
	 * @brief	Uses a* to find a path to the destination
	 * @param xStart	- The starting xLocation (side to side)
	 * @param yStart	- The starting yLocation (up and down)
	 * @param xEnd	- The ending xLocation (side to size)
	 * @param yEnd	- The ending yLocation (up and down)
	 *
	 */
	std::vector<std::vector<DistanceNode>> findPath(int xStart, int yStart,
	                                                int xEnd, int yEnd);

	/**
	 * @brief	Sets the grid to be used
	 * @param	newGrid	- The grid to store information from (0 = free space,
	 * everything else it is not allowed to move into)
	 * @return	bool	- If it was successful
	 */
	bool setGrid(std::vector<std::vector<int>> newGrid);

	/**
	 * @brief	Sets the grid to be used
	 * @param	newGrid	- The grid to store information from (0 = free space,
	 * everything else it is not allowed to move into)
	 * @param	xSize	- The size of the grid in the xDirection (left/right)
	 * @param	ySize	- The size of the grid in the yDirection (up/down)
	 * @return	bool	- If it was successful
	 */
	bool setGrid(int **newGrid, int xSize, int ySize);

	/**
	 * @brief	Sets diagonal movement cost
	 * @param	val		- Sets the cost to move diagonal
	 * @return	bool	- If it was successful
	 */
	bool setDiagonalMovementCost(float val);

	/**
	 * @brief
	 * @param	val		- Sets the cost to move non-diagonally
	 * @return	bool	- If it was successful
	 */
	bool setNonDiagonalMovementCost(float val);

	/**
	 * @brief	Sets if you allow diagoanl movement or not
	 * @param	allow	- true: allow diagonal movement, false: don't allow
	 * diagonal movement
	 * @return	bool	- If it was successful
	 */
	void setAllowDiagonalMovement(bool allow);

	/**
	 * @brief	Sets the cost of the estimated distance
	 * @param	val		- The heuristicCostScale (larger values means faster but
	 * less chance to get best path)
	 * @return	bool	- If it was successful
	 */
	bool setHeuristicsCostScale(float val);

	/**
	 * @brief	Sets the max distance allowed before the algorithm will
	 * terminate
	 * @param	val		- The max distance
	 * @return	bool	- If it was successful
	 */
	bool setMaxDistance(float val);

	/**
	 * brief		Prints the possible exceptions
	 * @param	val	- the value of the exception
	 */
	void printAstarException(int val);

private:
	/**
	 * @brief	Sets the size of the grid in the x direction
	 * @param	xSize	- The size of the grid in the x direction
	 * @return	bool	- If it was successful
	 */
	bool setGridSizeX(int xSize);

	/**
	 * @brief	Sets the size of the grid in the y direction
	 * @param	ySize	- The size of the grid in the y direction
	 * @return	bool	- If it was successful
	 */
	bool setGridSizeY(int ySize);

	/// <summary>
	/// A 2D vector which is used to store the grid as 0 - free and 1's - not
	/// free
	/// </summary>
	std::vector<std::vector<int>> grid;

	/// <summary>
	/// [0] - horizontal movement cost
	/// [1] - diagonal movement cost
	/// [3] - 0 if don't use diagonal, 1 if use diagonal
	/// </summary>
	float movementCosts[3];

	/// <summary>
	/// 1 is average
	/// smaller values puts less importance on estimate distance making it more
	/// like Dijkstra's algorithm .e. slower but more accurate larger values
	/// puts more importance on estimate distance making it more greedy i.e.
	/// faster but less accurate
	/// </summary>
	float heuristicsCostScale;

	/// <summary>
	/// gridSize[0] - Y size
	/// gridSize[1] - X size
	/// 		/// </summary>
	int gridSize[2];

	/// <summary>
	/// The max distance allowed till the algorithm exits
	/// </summary>
	float maxDistance;
};

#endif
