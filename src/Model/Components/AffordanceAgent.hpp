#pragma once

#include <string>

#include <entt/entt.hpp>
#include <sol/sol.hpp>

#include "Controller/Affordance/Affordance.hpp"
#include "Controller/Affordance/AffordanceUtility.hpp"
#include "Controller/ECS/Entity.hpp"

using Affordance::Properties;
using Affordance::PropertiesWeight;
using Affordance::Utility;

namespace Component {
/**
 * @author Andrew Ho
 * @struct AffordanceAgent
 * @brief The affordance agent component represents an agent that looks for an
 * affordance based on the considerations from its utility system. Each agent
 * has a set of properties, and among those properties they have a weighting
 * towards their importance or preference.
 */
struct AffordanceAgent {
	/// The properties that the agent can perceive.
	Properties properties;
	/// The weight of each property.
	PropertiesWeight property_weights;
	/// The affordance utility system.
	Utility utility;
	/// The affordance entity ID that the agent is currently using.
	entt::entity affordance = {entt::null};

	AffordanceAgent() = default;

	AffordanceAgent(const AffordanceAgent&) = default;

	AffordanceAgent(const Properties& properties,
	                const PropertiesWeight& property_weights)
	    : properties(properties), property_weights(property_weights) {}
};
}  // namespace Component