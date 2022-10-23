#pragma once

#include <string>

namespace Component {
	// Chuck into the agent component (will have the affordance stuff and emotional
	// state + current emotion) These values would be the 'mood' (long term).
	// set_emotion() would be short term emotions passed through.
	struct mood {
	float joy_sadness;
	float trust_disgust;
	float fear_anger;
	float surprise_anticipation;
	};

	struct Agent {
	    mood mood_state;
	    std::string current_emotion;
	};
 }