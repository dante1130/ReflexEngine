#pragma once

#include <string>

#include <entt/entt.hpp>
#include <sol/sol.hpp>

#include "Controller/Affordance/Affordance.hpp"
#include "Controller/Affordance/AffordanceUtility.hpp"
#include "Controller/ECS/Entity.hpp"

using Affordance::AffordanceUtility;
using Affordance::Properties;
using Affordance::PropertiesWeight;

namespace Component {
struct AffordanceAgent {
	Properties properties;
	PropertiesWeight property_weights;
	AffordanceUtility utility;

	entt::entity affordance = {entt::null};

	AffordanceAgent() = default;

	AffordanceAgent(const AffordanceAgent&) = default;

	AffordanceAgent(const Properties& properties,
	                const PropertiesWeight& property_weights)
	    : properties(properties), property_weights(property_weights) {}
};
}  // namespace Component