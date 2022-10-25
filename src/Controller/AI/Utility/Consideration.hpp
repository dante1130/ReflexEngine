#pragma once

namespace AI::Utility {
/**
 * @brief A consideration takes an agent's context as input and uses it to
 * calculate a score out of the appraisal. Depending on the score of the
 * appraisal, the decision to take an action is made.
 *
 * @tparam Appraisal Drives our final decision, returns an arbitrary value.
 * @tparam Decision The decision to take based on the appraisal.
 */
template <typename Appraisal, typename Decision>
struct Consideration {
	/// The appraisal that drives our decision.
	Appraisal appraisal;
	/// The decision to take based on the appraisal.
	Decision decision;
};
}  // namespace AI::Utility