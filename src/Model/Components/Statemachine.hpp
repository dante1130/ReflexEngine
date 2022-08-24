#pragma once

#include <string>

#include "Model/RunTimeDataStorage/idManager.hpp"

#include <sol/sol.hpp>
#include <Controller/LuaManager.hpp>

#include "Controller/ECS/Entity.hpp"

namespace Component {

/**
 * @author Daniel Rodic
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
	/// A pointer to the entity that the statemachine is attached to.
	Reflex::Entity* entity = nullptr;

	Statemachine() {
		unique_statemachine_identifier = statemachineIDMgr.increment_count();
	}
};
}  // namespace Component
