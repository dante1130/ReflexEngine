#pragma once

#include <string>
#include <unordered_map>
#include <Model/Components/Agent.hpp>

#include <sol/sol.hpp>

namespace Emotion {

using definedEmotions = std::unordered_map<std::string, Emotion::emotion>;
/**
 * @author Florian Robbins
 * @struct emotion
 * @brief The mood struct is used to store float values relating to an
 * agent's emotion
 */
struct emotion {
	float joy_sadness;
	float trust_disgust;
	float fear_anger;
	float surprise_anticipation;
	emotion(float joy_sad, float tru_dis, float fea_ang, float sup_ant) {
		joy_sadness = joy_sad;
		trust_disgust = tru_dis;
		fear_anger = fea_ang;
		surprise_anticipation = sup_ant;
	}
};

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
	static auto get_instance() -> Emotion::EmotionSystem&;

	/**
	 * @brief Expose the Emotions and the AgentEmotions classes to Lua.
	 */
	auto lua_access() -> void;

	/**
	 * @brief Sets a newly defined emotion for the definedEmotions map
	 *
	 * @param emotion The name of the emotion
	 * @param joy_sad The joy/sadness modifier (0.0f is sad, 1.0f is joy)
	 * @param tru_dis The trust/disgust modifier (0.0f is disgust, 1.0f is
	 * trust)
	 * @param fea_ang The fear/anger modifier (0.0f is fear, 1.0f is anger)
	 * @param sup_ant The surprise/anticipation modifier (0.0f is
	 * anticipation, 1.0f is surprise)
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
	auto find_emotion(std::string emotion) -> const Emotion::emotion&;

private:
	EmotionSystem() = default;
	/// An unordered map of emotions with a key of the emotion and a value of
	/// emotional values
	definedEmotions emotion_state;
};
}  // namespace Emotion
