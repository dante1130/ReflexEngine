#include "EmotionHelper.hpp"

#include "Model/Components/AffordanceAgent.hpp"

auto Emotion::update_emotion(const Reflex::Entity& entity) -> void {
	auto& affordance_agent = entity.get_component<Component::AffordanceAgent>();

	auto total_arousal_weights = 0.0F;
	auto total_valence_weights = 0.0F;

	for (auto& [key, value] : affordance_agent.utility.context) {
		sol::table context_table = value.as<sol::table>();
		total_arousal_weights += context_table["arousal_weight"];
		total_valence_weights += context_table["valence_weight"];
	}

	for (auto& [key, value] : affordance_agent.utility.context) {
		sol::table context_table = value.as<sol::table>();
		float arousal_weight = context_table["arousal_weight"];
		float valence_weight = context_table["valence_weight"];

		float value = context_table["value"];

		if (total_arousal_weights != 0.0F) {
			affordance_agent.mood_state.arousal +=
			    (value * arousal_weight) / total_arousal_weights;
		}

		if (total_valence_weights != 0.0F) {
			affordance_agent.mood_state.valence +=
			    (value * valence_weight) / total_valence_weights;
		}
	}
}