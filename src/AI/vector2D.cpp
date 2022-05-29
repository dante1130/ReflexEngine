#include "vector2D.hpp"

vector2D::vector2D() {}

void vector2D::set(float x, float y) { vec = glm::vec2(x, y); }
void vector2D::setX(float x) { vec.x = x; }
void vector2D::setY(float y) { vec.y = y; }

float vector2D::getX() { return vec.x; }
float vector2D::getY() { return vec.y; }

void vector2D::normalise() { vec = glm::normalize(vec); }
float vector2D::length() { return glm::length(vec); }
