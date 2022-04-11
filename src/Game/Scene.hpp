#pragma once

#include <memory>
#include <vector>

#include "GameObject/GameObject.hpp"

class Scene {
public:
	virtual void init() = 0;

	virtual void update(float delta_time) = 0;

	virtual void add_draw_call() = 0;

	virtual ~Scene() = default;

protected:
	std::vector<std::shared_ptr<GameObject>> game_objects_;
};
