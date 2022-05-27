#pragma once

#include <glm/glm.hpp>

class vector2D {
public:
	vector2D();

	void set(float x, float y);
	void setX(float x);
	void setY(float y);

	float getX();
	float getY();

	void normalise();
	float length();

private:
	glm::vec2 vec;
};
