#pragma once

#include <glm/glm.hpp>

class vector2D {
public:
	/**
	 * @brief	Default constructor
	 */
	vector2D();

	/**
	 * @brief	Sets the vector
	 * @param	x	- The x coordinate
	 * @param	y	- the y coordinate
	 */
	void set(float x, float y);

	/**
	 * @brief	Sets the x coordinate
	 * @param	x	- The x coordinate
	 */
	void setX(float x);

	/**
	 * @brief	Sets the y coordinate
	 * @param	y	- the y coordinate
	 */
	void setY(float y);

	/**
	 * @brief	Gets the x coordinate
	 * @return	float	- The x coordinate
	 */
	float getX();

	/**
	 * @brief	Gets the y coordinate
	 * @return	float	- The y coordinate
	 */
	float getY();

	/**
	 * @brief	Normalises the vector
	 */
	void normalise();

	/**
	 * @brief	Determines the float of the vector
	 * @return	float	- The length of the vector
	 */
	float length();

private:
	glm::vec2 vec;
};
