#pragma once

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Component {
/**
 * @struct Transform
 * @brief The transform component is used to store the position, rotation and
 * scale of an entity.
 */
struct Transform {
	/// The position of the entity.
	glm::vec3 position = {0.0f, 0.0f, 0.0f};
	/// The rotation of the entity.
	glm::quat rotation = {1.0f, 0.0f, 0.0f, 0.0f};
	/// The scale of the entity.
	glm::vec3 scale = {1.0f, 1.0f, 1.0f};

	Transform() = default;

	Transform(const Transform&) = default;

	Transform(const glm::vec3& pos, const glm::quat& rot, const glm::vec3& scl)
	    : position(pos), rotation(rot), scale(scl) {}
};
};  // namespace Component