#pragma once

#include <string>
#include <unordered_map>
#include <sol/sol.hpp>

#include "Controller/Affordance/Affordance.hpp"

namespace Affordance {
/**
 * @author Andrew Ho
 * @struct Consideration
 * @brief A consideration has a function that returns a value between 0 and 1,
 * and the affordance properties that the agent desires to look for.
 */
struct Consideration {
	/// The affordance properties that the agent desires to look for.
	Affordance::Properties properties;
	/// A function that returns a value between 0 and 1 to determine the utility
	/// of the affordance.
	sol::function scorer_func;
	/// The score returned from the scorer function.
	float score = 0.0F;

	Consideration() = default;

	Consideration(const Consideration&) = default;

	Consideration(const Affordance::Properties& properties,
	              const sol::function& scorer_func)
	    : properties(properties), scorer_func(scorer_func) {}
};

using UtilityStates = std::unordered_map<std::string, Consideration>;

/**
 * @author Andrew Ho
 * @struct Utility
 * @brief The affordance utility is a minimal utility AI that uses a map of
 * states and considerations to determine the utility of an affordance, the
 * highest score returned by the considerations is the one that the agent will
 * decide to use.
 */
struct Utility {
	/// The states that the agent will consider.
	UtilityStates states;
	/// The context that the agent will use to evaluate the states.
	sol::table context;
	/// An update function that will be called every frame, used to update any
	/// of the context variables.
	sol::function update_func;
	/// The name of the state that the agent will use.
	std::string decision;
};
}  // namespace Affordance