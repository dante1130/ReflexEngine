#pragma once

#include <string>
#include <unordered_map>

#include <sol/sol.hpp>

namespace EmotionSystem {

	using definedEmotions = std::unordered_map<Emotions, EmotionalState>;
	/**
	 * @author Florian Robbins
	 * @class Emotion
	 * @brief An emotion is a class that is used to create an object of emotion.
	 * It is used to represent the emotions an AI agent may be experiencing.
	 */

	enum class Emotions { RAGE, TERROR, ADMIRATION, FEAR };

	struct EmotionalState {
		float joy_sadness;
		float trust_disgust;
		float fear_anger;
		float surprise_anticipation;
	};
	class Emotion {
	public:
		Emotion(float joy_sad, float tru_dis, float fea_ang, float sup_ant);

		auto lua_access() -> void;

		auto get_emotional_state(std::string emotion_state);

		auto alter_emotional_state(std::string emotion_state, float adjust_val);
	};
}  // namespace Emotion