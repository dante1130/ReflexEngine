#pragma once

#include <string>

#include <sol/sol.hpp>

#include "Controller/ECS/Entity.hpp"

namespace component {
/**
 * @struct Script
 * @brief The script component is used to run a lua script.
 */
struct Script {
	std::string lua_script;
	sol::table lua_variables;
	Entity* entity;
};
};  // namespace component