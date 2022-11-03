#pragma once

#include "AStar.h"
#include <vector>
#include <deque>

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
	auto findPath(float xStart, float yStart, float xEnd, float yEnd)
	    -> std::deque<std::pair<float, float>>;

	/**
	 * @brief	Sets the grid to be used
	 * @param	newGrid	- The grid to store information from (0 = free
	 * space, everything else it is not allowed to move into). std::move
	 * used
	 * @return	bool	- If it was successful
	 */
	bool setGrid(std::vector<std::vector<int>> newGrid);

	/**
	 * @brief Resets the grid to the one set using setGrid
	 *
	 */
	auto reset_grid_to_original() -> void;

	/**
	 * @brief Set a point in the grid to a specific value
	 *
	 * @param x_point specified the x coordinate
	 * @param y_point specifies the y coordiante
	 * @param new_value the new value to set in the position (0 is free, else
	 * blocked)
	 * @return true done successfully
	 * @return false problem encountered (out of range)
	 */
	auto set_coordinate_value(float x_point, float y_point, int new_value)
	    -> bool;

	/**
	 * @brief	Sets diagonal movement cost
	 * @param	val		- Sets the cost to move diagonal
	 * @return	bool	- If it was successful
	 */
	bool setDiagonalMovementCost(float val);

	/**
	 * @brief	Sets the non diagonal movement cost
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

	/**
	 * @brief Prints the grid
	 *
	 */
	auto print_grid() -> void;

	/**
	 * @brief	Returns the set grid
	 * @return	std::vector<std::vector<int>> &	- The set grid
	 */
	std::vector<std::vector<int>>& getGrid();

	/**
	 * @brief Set the grid ratio
	 *
	 * @param ratio the new ratio of the grid
	 */
	auto set_grid_ratio(float ratio) -> void;

	/**
	 * @brief Get the grid ratio
	 *
	 * @return float
	 */
	auto get_grid_ratio() -> float;

	/**
	 * @brief Set the grid offset
	 *
	 * @param x_offset the new x offset
	 * @param y_offset the new y offset
	 */
	auto set_grid_offset(float x_offset, float y_offset) -> void;

	/**
	 * @brief Get the grid offset object
	 */
	auto get_grid_offset() -> std::pair<float, float>;

	/**
	 * @brief Returns if the starting position is at the end
	 * @param xStart	- The starting xLocation (side to side)
	 * @param yStart	- The starting yLocation (up and down)
	 * @param xEnd	- The ending xLocation (side to size)
	 * @param yEnd	- The ending yLocation (up and down)
	 *
	 * @return bool
	 */
	auto is_at_destination(float xStart, float yStart, float xEnd, float yEnd)
	    -> bool;

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

	/// A 2D vector which is used to store the grid as 0 - free and 1's - not
	/// free
	std::vector<std::vector<int>> grid;

	/// The default grid when first set (to revert back to)
	std::vector<std::vector<int>> default_grid;

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

	/// The offset for the input start & end values
	/// start_offset_[0] - y offset
	/// start_offset_[1] - x offset
	float start_offset_[2];

	/// The grid scale
	/// 1 is 1 unit in real to 1 in grid (1-1 ratio)
	/// 2 is 1 unit in real is 2 in grid (1-2 ratio)
	float grid_ratio_;
};