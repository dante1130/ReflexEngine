#pragma once

#include <string>
#include <unordered_map>

#include <sol/sol.hpp>

namespace Emotion {

/**
 * @author Florian Robbins
 * @struct emotion
 * @brief The mood struct using the arousal and valence circumplex model is used
 * to store float values relating to an agent's emotion. All values are between
 * -1 and 1. With 0 being neutral.
 */
struct EmotionState {
	float arousal = 0.0F;
	float valence = 0.0F;

	EmotionState() = default;

	EmotionState(const EmotionState&) = default;

	EmotionState(float arousal, float valence)
	    : arousal(arousal), valence(valence) {}
};

using DefinedEmotions = std::unordered_map<std::string, EmotionState>;

/**
 * @author Florian Robbins
 * @class Emotion
 * @brief An emotion is a class that is used to create an object of emotion.
 * It is used to represent the emotions an AI agent may be experiencing.
 */
class EmotionSystem {
public:
	/**
	 * @brief Get the instance of the Emotions.
	 *
	 * @return Emotions&
	 */
	static auto get_instance() -> EmotionSystem&;

	/**
	 * @brief Expose the Emotions and the AgentEmotions classes to Lua.
	 */
	auto lua_access() -> void;

	/**
	 * @brief Sets a newly defined emotion for the DefinedEmotions map
	 *
	 * @param emotion_name The name of the emotion.
	 * @param emotion The emotion.
	 */
	auto set_emotion(const std::string& emotion_name,
	                 const EmotionState& emotion) -> void;

	/**
	 * @brief Finds an emotion for the agent to feel
	 *
	 * @param emotion_name The name of the emotion
	 *
	 * @return Component::mood The mood values of the emotion. Returns 0.0F for
	 * all mood values if emotion was undefined in DefinedEmotions map
	 */
	auto find_emotion(const std::string& emotion_name) -> EmotionState;

private:
	EmotionSystem() = default;
	/// An unordered map of emotions with a key of the emotion and a value of
	/// emotional values
	DefinedEmotions emotion_state;
};
}  // namespace Emotion
