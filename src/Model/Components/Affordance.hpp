#pragma once

#include <string>

#include <sol/sol.hpp>

namespace Component {
struct Affordance {
	std::string object_name;
	sol::function action;

	Affordance() = default;

	Affordance(const Affordance&) = default;

	Affordance(const std::string& object_name, const sol::function& action)
	    : object_name(object_name), action(action) {}
};
}  // namespace Component