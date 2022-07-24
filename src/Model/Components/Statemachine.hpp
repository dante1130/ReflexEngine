#pragma once

#include <string>

#include <Model/singletons.h>

namespace Component {

/**
 * @struct	statemachine
 * @brief	Used the store the current state of a statemachine along with its
 * unqiue identifier
 */
struct Statemachine {
	/// The unqiue identifier for the state machine
	int unique_statemachine_identifier;
	/// The global state of the state machine
	std::string global_state;
	/// The current state of the state machine
	std::string current_state;
	/// The previous state of the state machine
	std::string previous_state;
	/// lua_variables
	sol::table lua_variables;

	Statemachine() { unique_statemachine_identifier = idMgr.increment_count(); }
};
}  // namespace Component
