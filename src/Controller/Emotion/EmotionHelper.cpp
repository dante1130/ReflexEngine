#include "EmotionHelper.hpp"

#include "Model/Components/AffordanceAgent.hpp"

auto Emotion::update_emotion(const Reflex::Entity& entity) -> void {
	auto& affordance_agent = entity.get_component<Component::AffordanceAgent>();

	auto total_arousal_weights = 0.0F;
	auto total_valence_weights = 0.0F;

	for (auto& [key, value] : affordance_agent.utility.context) {
		const auto context_table = value.as<sol::table>();
		total_arousal_weights += context_table["arousal_weight"].get<float>();
		total_valence_weights += context_table["valence_weight"].get<float>();
	}

	for (auto& [key, value] : affordance_agent.utility.context) {
		const auto context_table = value.as<sol::table>();
		const float arousal_weight = context_table["arousal_weight"];
		const float valence_weight = context_table["valence_weight"];

		const float context_value = [&context_table]() {
			float temp_value = context_table["value"];
			return temp_value < 0.0F ? 0.0F : temp_value;
		}();

		if (total_arousal_weights != 0.0F) {
			affordance_agent.mood_state.arousal +=
			    (context_value * arousal_weight) / total_arousal_weights;
		}

		if (total_valence_weights != 0.0F) {
			affordance_agent.mood_state.valence +=
			    (context_value * valence_weight) / total_valence_weights;
		}
	}

	affordance_agent.mood_state.arousal =
	    std::clamp(affordance_agent.mood_state.arousal, -1.0F, 1.0F);
	affordance_agent.mood_state.valence =
	    std::clamp(affordance_agent.mood_state.valence, -1.0F, 1.0F);
}