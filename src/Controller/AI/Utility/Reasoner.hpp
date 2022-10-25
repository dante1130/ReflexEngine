#pragma once

#include <unordered_map>

#include "Consideration.hpp"

namespace AI::Utility {
/**
 * @brief A reasoner is a collection of choices that can be made by an agent.
 *
 * @tparam State A state of the agent.
 * @tparam Context Contains all the information the AI neds to make a decision.
 * @tparam Appraisal Drives our final decision, returns an arbitrary value.
 * @tparam Decision The decision to take based on the appraisal.
 */
template <typename State, typename Context, typename Appraisal,
          typename Decision>
struct Reasoner {
	using Choice = Consideration<Appraisal, Decision>;
	using States = std::unordered_map<State, Choice>;

	/// The choices that can be made by the agent.
	States choices;
	/// The context or information the AI needs to make a decision.
	Context context;
	/// The current decision of the agent.
	Decision best_decision;
};
}  // namespace AI::Utility