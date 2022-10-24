#include "AffordanceHelper.hpp"

auto Affordance::find_affordance(AffordancePtr affordances,
                                 const Properties& properties,
                                 const PropertiesWeight& properties_weight)
    -> AffordancePtr {
	auto best_affordance = affordances;

	while (best_affordance->is_composite()) {
		auto affordance_composite =
		    std::dynamic_pointer_cast<AffordanceComposite>(best_affordance);
		auto best_affordance_score = 0.0F;

		auto child_affordances = affordance_composite->get_affordances();
		if (child_affordances.empty()) {
			break;
		}

		for (const auto& child : child_affordances) {
			auto score = 0.0F;

			// Calculate the score of the child.
			for (const auto& child_property : child->get_properties()) {
				if (properties.find(child_property) != properties.end()) {
					// Use the weight of the property if it exists, otherwise 1.
					if (properties_weight.find(child_property) !=
					    properties_weight.end()) {
						score += properties_weight.at(child_property);
					} else {
						score += 1.0F;
					}
				}
			}

			// If the score is better than the current best, set the best.
			if (score > best_affordance_score) {
				best_affordance = child;
				best_affordance_score = score;
			}
		}
	}

	return best_affordance;
}
