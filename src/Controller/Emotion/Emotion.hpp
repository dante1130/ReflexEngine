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
}  // namespace Emotion
