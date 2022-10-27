#pragma once

#include <string>

#include "Controller/Emotion/Emotion.hpp"

namespace Component {
// Chuck into the agent component (will have the affordance stuff and
// emotional state + current emotion) These values would be the 'mood' (long
// term). set_emotion() would be short term emotions passed through.

/**
 * @author Florian Robbins
 * @struct Agent
 * @brief The agent component is used to store the mood of the agent and
 * the current emotion the agent is experiencing
 */
struct Agent {
	Emotion::EmotionState mood_state;

	std::string current_emotion;

	Agent() = default;

	Agent(const Agent&) = default;

	Agent(const Emotion::EmotionState& mood_state,
	      const std::string& current_emotion)
	    : mood_state(mood_state), current_emotion(current_emotion) {}
};
};  // namespace Component
