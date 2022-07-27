#pragma once

#include "View/guiManager.hpp"

#include "Controller/ECS/ECS.hpp"

class ECSGui {
public:
	ECSGui() = default;

	void draw(const ECS& ecs);

private:
};