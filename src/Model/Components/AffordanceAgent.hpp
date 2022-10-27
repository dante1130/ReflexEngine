#pragma once

#include <string>

#include <sol/sol.hpp>

#include "Controller/Affordance/Affordance.hpp"
#include "Controller/Affordance/AffordanceUtility.hpp"
#include "Controller/ECS/Entity.hpp"

using namespace Affordance;

namespace Component {
struct AffordanceAgent {
	Properties properties;
	PropertiesWeight property_weights;
	AffordanceUtility utility;

	AffordanceAgent() = default;

	AffordanceAgent(const AffordanceAgent&) = default;

	AffordanceAgent(const Properties& properties,
	                const PropertiesWeight& property_weights)
	    : properties(properties), property_weights(property_weights) {}
};
}  // namespace Component