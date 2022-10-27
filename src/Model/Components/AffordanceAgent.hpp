#pragma once

#include <string>

#include <sol/sol.hpp>

#include "Controller/Affordance/Affordance.hpp"
#include "Controller/Affordance/AffordanceUtility.hpp"
#include "Controller/ECS/Entity.hpp"

namespace Component {
struct AffordanceAgent {
	Affordance::Properties properties;
	Affordance::PropertiesWeight property_weights;
	Affordance::AffordanceUtility utility;

	AffordanceAgent() = default;

	AffordanceAgent(const AffordanceAgent&) = default;

	AffordanceAgent(const Affordance::Properties& properties,
	                const Affordance::PropertiesWeight& property_weights)
	    : properties(properties), property_weights(property_weights) {}
};
}  // namespace Component