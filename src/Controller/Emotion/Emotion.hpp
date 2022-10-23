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

	    /**
	     * @brief Gets the emotion the agent is feeling.
	     *
	     * @param properties The properties of the affordance. (look at implementation, probably use the Component::mood instead of the agent itself)
		 * @return string The emotion the agent is experiencing currently
	     */
		auto get_emotion(Component::Agent agent) -> const std::string&;

	    /**
	     * @brief Gets the emotion values the agent is feeling.
	     *
	     *
	     * @return definedEmotions The emotion values the agent is currently experiencing
	     */
	    auto get_emotional_state(Component::Agent agent)
	        -> const definedEmotions&;

	    /**
	     * @brief Sets a newly defined emotion for the definedEmotions map
	     *
	     * @param emotion The name of the emotion
		 * @param joy_sad The joy/sadness modifier (0.0f is sad, 1.0f is joy)
		 * @param tru_dis The trust/disgust modifier (0.0f is disgust, 1.0f is trust)
		 * @param fea_ang The fear/anger modifier (0.0f is fear, 1.0f is anger)
		 * @param sup_ant The surprise/anticipation modifier (0.0f is anticipation, 1.0f is surprise)
	     */
		auto set_emotion(std::string emotion, float joy_sad, float tru_dis,
	                     float fea_ang, float sup_ant);

		auto set_current_emotion(std::string emotion);

	private:

	    definedEmotions emotion_state;
	};
}  // namespace Emotion