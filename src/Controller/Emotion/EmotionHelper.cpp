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

	auto total_arousal = 0.0F;
	auto total_valence = 0.0F;

	for (auto& [key, value] : affordance_agent.utility.context) {
		const auto context_table = value.as<sol::table>();
		const float arousal_weight = context_table["arousal_weight"];
		const float valence_weight = context_table["valence_weight"];

		const float context_value =
		    std::clamp(context_table["value"].get<float>(), -1.0F, 1.0F);

		total_arousal += (context_value * arousal_weight);
		total_valence += (context_value * valence_weight);
	}

	if (total_arousal_weights > 0.0F) {
		affordance_agent.mood_state.arousal =
		    std::clamp(total_arousal /= total_arousal_weights, -1.0F, 1.0F);
	}

	if (total_valence_weights > 0.0F) {
		affordance_agent.mood_state.valence =
		    std::clamp(total_valence /= total_valence_weights, -1.0F, 1.0F);
	}
}