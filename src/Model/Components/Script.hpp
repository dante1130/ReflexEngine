#pragma once

#include <string>

#include <sol/sol.hpp>

#include "Controller/ECS/Entity.hpp"

namespace Component {
/**
 * @struct Script
 * @brief The script component is used to run a lua script.
 */
struct Script {
	/// The Lua script to run.
	std::string lua_script;
	/// The variables in the script.
	sol::table lua_variables;
	/// A pointer to the entity that the script is attached to.
	Reflex::Entity* entity = nullptr;
};
};  // namespace Component