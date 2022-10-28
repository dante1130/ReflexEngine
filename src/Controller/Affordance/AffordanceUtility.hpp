#pragma once

#include <string>
#include <unordered_map>
#include <sol/sol.hpp>

#include "Controller/Affordance/Affordance.hpp"

namespace Affordance {
struct Consideration {
	Affordance::Properties properties;
	sol::function scorer_func;
};

using UtilityStates = std::unordered_map<std::string, Consideration>;

struct AffordanceUtility {
	UtilityStates states;
	sol::table context;
	sol::function update_func;
	std::string decision;
};
}  // namespace Affordance