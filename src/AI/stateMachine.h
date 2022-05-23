#pragma once

#include <iostream>
using namespace std;
#include "state.h"

template <class entity_type>
class stateMachine {
private:
	/// The owner of the FSM
	entity_type* owner;
	/// The previous state
	std::string previousState;
	/// The current state
	std::string currentState;
	/// THe global state
	std::string globalState;

public:
	/**
	 * @brief	Assigns a state machine
	 * @param	sm	 - The new state machine object
	 */
	const stateMachine& operator=(const stateMachine& sm) {
		owner = sm.owner;
		previousState = sm.previousState;
		currentState = sm.currentState;
		globalState = sm.globalState;
		return *this;
	}

	/**
	 * @brief	Copy constructor
	 * @param	FSMowner	- FSM to copy over
	 */
	stateMachine(entity_type* FSMowner) { owner = FSMowner; }

	/**
	 * @brief	Sets the previous state
	 * @param	st	- The new state
	 */
	void setPreviousState(std::string st) { previousState = st; }

	/**
	 * @brief	Sets the current state
	 * @param	st	- The new state
	 */
	void setCurrentState(std::string st) {
		sol::state& lua = LuaManager::get_instance().get_state();
		sol::function exe;
		exe = lua[st]["enter"];
		exe(owner);

		currentState = st;
	}

	/**
	 * @brief	Sets the global state
	 * @param	st	- The new state
	 */
	void setGlobalState(std::string st) {
		sol::state& lua = LuaManager::get_instance().get_state();
		sol::function exe;
		exe = lua[st]["enter"];
		exe(owner);

		globalState = st;
	}

	/**
	 * @brief	Calls the states execute functions
	 */
	void update() const {
		sol::state& lua = LuaManager::get_instance().get_state();

		sol::function exe;

		exe = lua[globalState]["execute"];
		exe(owner);

		exe = lua[currentState]["execute"];
		exe(owner);
	}

	/**
	 * @brief	Sets the current state and moves the previous current state to
	 * the previous state section & call respective enter & exit functions
	 * @param	sewState	- The new state
	 */
	void changeState(std::string newState) {
		sol::state& lua = LuaManager::get_instance().get_state();
		sol::function exe;

		// save current state as previous state
		previousState = currentState;
		// call the exit function of the current state

		exe = lua[currentState]["exit"];
		exe(owner);

		// change current state to newState
		currentState = newState;
		// call the Enter function of the new currentState
		exe = lua[currentState]["enter"];
		exe(owner);
	}

	/**
	 * @brief	Reverts to the previous state
	 */
	void revertToPreviousState() { currentState = previousState; }

	/**
	 * @brief	Gets the previous state
	 * return	sol::table	- the state
	 */
	std::string getPreviousState() { return previousState; }

	/**
	 * @brief	Gets the current state
	 * return	sol::table	- the state
	 */
	std::string getCurrentState() { return currentState; }

	/**
	 * @brief	Gets the global state
	 * return	sol::table	- the state
	 */
	std::string getGlobalState() { return globalState; }

	// returns true if the current state's type is equal to the type of the
	// class passed as a parameter.
	/**
	 * @brief	Checks if the state is currently being used
	 * @param	st	- the state to check against
	 * @return	bool	- True if current state is same as one passed
	 */
	bool isInState(const State<entity_type>& st) const {
		return typeid(*currentState) == typeid(st);
	}

	/**
	 * @brief	Handles a message
	 * @return	bool	- successfully handled the message
	 */
	bool handleMessage(const telegram& msg) {
		sol::state& lua = LuaManager::get_instance().get_state();
		sol::function exe;

		exe = lua[currentState]["onMessage"];
		exe(owner, msg);
		return true;
	}
};
