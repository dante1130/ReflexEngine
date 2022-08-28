#pragma once

#include <string>

#include <sol/sol.hpp>

#include "Controller/ECS/ECS.hpp"
#include "Controller/ECS/Entity.hpp"

namespace Component {
/**
 * @author Andrew Ho
 * @struct Script
 * @brief The script component is used to run a lua script.
 */
struct Script {
	/// The Lua script to run.
	std::string lua_script = {"default"};
	/// A pointer to the ECS that the script is attached to.
	ECS* ecs = nullptr;
	/// A pointer to the entity that the script is attached to.
	Reflex::Entity* entity = nullptr;
	/// The variables in the script.
	sol::table lua_variables;

	Script() = default;

	Script(const Script&) = default;

	Script(const std::string& lua_script, ECS& ecs, Reflex::Entity& entity)
	    : lua_script(lua_script), ecs(&ecs), entity(&entity) {}
};
};  // namespace Component