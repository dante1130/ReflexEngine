#pragma once

#include <glm/glm.hpp>

namespace component {
struct Transform {
	glm::vec3 position = {0.0f, 0.0f, 0.0f};

	// Could maybe use a glm::quat.
	// glm::quat rotation = {1.0f, 0.0f, 0.0f, 0.0f};
	glm::vec3 rotation = {0.0f, 0.0f, 0.0f};

	glm::vec3 scale = {1.0f, 1.0f, 1.0f};
	float angle = 0.0f;
};
};  // namespace component