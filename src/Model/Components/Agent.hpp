#pragma once

#include <string>

namespace Component {
// Chuck into the agent component (will have the affordance stuff and emotional
// state + current emotion) These values would be the 'mood' (long term).
// set_emotion() would be short term emotions passed through.

/**
 * @author Florian Robbins
 * @struct mood
 * @brief The mood struct is used to store float values relating to an
 * agent's mood
 */
struct mood {
	float joy_sadness;
	float trust_disgust;
	float fear_anger;
	float surprise_anticipation;
	mood(float joy_sad, float tru_dis, float fea_ang, float sup_ant) {
		joy_sadness = joy_sad;
		trust_disgust = tru_dis;
		fear_anger = fea_ang;
		surprise_anticipation = sup_ant;
	}
};

/**
 * @author Florian Robbins
 * @struct Agent
 * @brief The agent component is used to store the mood of the agent and
 * the current emotion the agent is experiencing
 */
struct Agent {
	mood mood_state;

	std::string current_emotion;

	Agent() = default;

	Agent(const Agent&) = default;

	Agent(const mood& mood_state, const std::string& current_emotion)
	    : mood_state(mood_state), current_emotion(current_emotion) {}
};
};  // namespace Component