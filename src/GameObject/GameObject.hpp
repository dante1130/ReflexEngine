#pragma once

#include <glm/glm.hpp>
#include "Shader.hpp"

class GameObject {
public:
	struct {
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
	};

	virtual void init() = 0;

	virtual void update(float delta_time) = 0;

	virtual void add_draw_call() = 0;

	virtual void draw(std::shared_ptr<Shader> shader) = 0;

	virtual ~GameObject() = default;
};
