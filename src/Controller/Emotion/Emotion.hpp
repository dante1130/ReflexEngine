#pragma once

#include <string>
#include <unordered_map>
#include <Model/Components/Agent.hpp>

#include <sol/sol.hpp>

namespace EmotionSystem {

	using definedEmotions = std::unordered_map<std::string, Component::mood>;

	/**
	 * @author Florian Robbins
	 * @class Emotion
	 * @brief An emotion is a class that is used to create an object of emotion.
	 * It is used to represent the emotions an AI agent may be experiencing.
	 */

	class Emotions {
	public:

		Emotions(float joy_sad, float tru_dis, float fea_ang, float sup_ant);

		auto lua_access() -> void;

		auto get_emotion(Component::Agent agent) -> const std::string&;

		auto get_emotional_state() -> const definedEmotions&;

		auto set_emotion(std::string emotion, float joy_sad, float tru_dis,
	                     float fea_ang, float sup_ant);

		auto set_current_emotion(std::string emotion);

	private:

	    definedEmotions emotion_state;
	};
}  // namespace Emotion