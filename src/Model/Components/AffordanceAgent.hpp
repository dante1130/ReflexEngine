#pragma once

#include <string>

#include <sol/sol.hpp>

#include "Controller/Affordance/Affordance.hpp"
#include "Controller/AI/Utility/Reasoner.hpp"

namespace Component {
struct AffordanceAgent {
	using AffordanceReasoner =
	    AI::Utility::Reasoner<std::string, sol::table, sol::function,
	                          Affordance::Properties>;

	Affordance::Properties properties;
	Affordance::PropertiesWeight property_weights;
	AffordanceReasoner reasoner;
};
}  // namespace Component