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

	    /**
	     * @brief Get the instance of the Emotions.
	     *
	     * @return Emotions&
	     */
		static auto get_instance() -> Emotions&;

	    /**
	     * @brief Expose the Emotions and the AgentEmotions classes to Lua.
	     */
		auto lua_access() -> void;

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

		/**
	     * @brief Finds an emotion for the agent to feel
	     *
	     * @param emotion The name of the emotion
	     * 
		 * @return Component::mood The mood values of the emotion. Returns -1.0f for
		 * all mood values if emotion was undefined in definedEmotions map
	     */
		auto find_emotion(std::string emotion)
	        -> const Component::mood&;

	private:

		Emotions() = default;
	    /// An unordered map of emotions with a key of the emotion and a value of emotional values
	    definedEmotions emotion_state;
	};

	class AgentEmotions {
	public:

		/**
	     * @brief Gets the emotion the agent is feeling.
	     *
	     * @param agent The agent to find. (look at implementation, probably use
	     * the Component::mood instead of the agent itself)
	     * @return string The emotion the agent is experiencing currently
	     */
	    auto get_emotion(Component::Agent agent) -> const std::string&;

	    /**
	     * @brief Gets the emotion values the agent is feeling.
	     *
	     *
	     * @return mood_state The emotion values the agent is currently
	     * experiencing
	     */
	    auto get_emotional_state(Component::Agent agent);

		/**
	     * @brief Sets an emotion for the agent to start experiencing.
	     *
	     *
	     * @param emotion The name of the emotion the agent is to experience
	     */
		auto set_current_emotion(std::string emotion, Component::Agent agent);

	};
    }  // namespace Emotion