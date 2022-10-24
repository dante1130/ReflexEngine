#pragma once

#include "Controller/Affordance/Affordance.hpp"

namespace Component {
struct AffordanceAgent {
	Affordance::Properties properties;
	std::unordered_map<std::string, float> property_weights;
};
}  // namespace Component