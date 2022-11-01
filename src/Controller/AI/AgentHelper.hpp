#pragma once

#include <glm/glm.hpp>

namespace AI {
auto lua_access() -> void;

auto move_towards(const glm::vec3& from, const glm::vec3& to, float speed)
    -> glm::vec3;

auto is_in_range(const glm::vec3& from, const glm::vec3& to, float range)
    -> bool;
};  // namespace AI
