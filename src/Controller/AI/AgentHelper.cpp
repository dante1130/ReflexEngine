#include "AgentHelper.hpp"

#include <glm/gtc/constants.hpp>

#include "Controller/ReflexEngine/EngineTime.hpp"
#include "Controller/LuaManager.hpp"

auto AI::lua_access() -> void {
	auto& lua = LuaManager::get_instance().get_state();

	auto ai_table = lua.create_named_table("AI");

	ai_table.set_function("move_towards", &AI::move_towards);
}

auto AI::move_towards(const glm::vec3& from, const glm::vec3& to, float speed)
    -> glm::vec3 {
	glm::vec3 direction = glm::normalize(to - from);
	float movement = speed * EngineTime::get_delta_time();

	if (glm::length(to - from) < movement) {
		return to;
	} else {
		return from + direction * movement;
	}
}