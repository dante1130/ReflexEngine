#pragma once

#include <string>

#include <entt/entt.hpp>
#include <sol/sol.hpp>

#include "Controller/Affordance/Affordance.hpp"
#include "Controller/Affordance/AffordanceUtility.hpp"
#include "Controller/Emotion/Emotion.hpp"
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
 * towards their importance or preference. The agent also stores the mood of the
 * agent and the current emotion the agent is experiencing.
 */
struct AffordanceAgent {
	/// The properties that the agent can perceive.
	Properties properties;
	/// The weight of each property.
	PropertiesWeight property_weights;
	/// The lua script that the agent will use to evaluate utility.
	std::string lua_script;
	/// The affordance utility system.
	Utility utility;
	/// The affordance entity ID that the agent is currently using.
	entt::entity affordance = {entt::null};
	/// The current mood of the agent.
	Emotion::EmotionState mood_state;
	/// Accumulated duration of state
	double accumulator = 0.0;
	/// Whether the action is currently being performed the first time.
	bool is_first_run = false;

	AffordanceAgent() = default;

	AffordanceAgent(const AffordanceAgent&) = default;

	AffordanceAgent(const Properties& properties,
	                const PropertiesWeight& property_weights,
	                const Emotion::EmotionState& mood_state)
	    : properties(properties),
	      property_weights(property_weights),
	      mood_state(mood_state) {}
};
}  // namespace Component