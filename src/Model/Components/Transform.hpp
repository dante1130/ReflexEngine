#pragma once

#include <glm/glm.hpp>

namespace component {
/**
 * @struct Transform
 * @brief The transform component is used to store the position, rotation and
 * scale of an entity.
 */
struct Transform {
	/// The position of the entity.
	glm::vec3 position = {0.0f, 0.0f, 0.0f};

	// Could maybe use a glm::quat.
	// glm::quat rotation = {1.0f, 0.0f, 0.0f, 0.0f};
	/// The rotation of the entity.
	glm::vec3 rotation = {0.0f, 0.0f, 0.0f};

	/// The scale of the entity.
	glm::vec3 scale = {1.0f, 1.0f, 1.0f};

	/// The angle of the entity.
	float angle = 0.0f;
};
};  // namespace component