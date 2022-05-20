#ifndef __STATEMACHINE_H
#define __STATEMACHINE_H

#include <iostream>
using namespace std;
#include "state.h"

template <class entity_type>
class stateMachine {
private:
	entity_type* owner;  // owner of the FSM
	sol::table previousState;
	sol::table currentState;
	sol::table globalState;

public:
	const stateMachine& operator=(const stateMachine& sm) {
		owner = sm.owner;
		previousState = sm.previousState;
		currentState = sm.currentState;
		globalState = sm.globalState;
		return *this;
	}

	stateMachine(entity_type* FSMowner) { owner = FSMowner; }

	// use the following methods to intialise the FSM
	void setPreviousState(sol::table st) { previousState = st; }
	void setCurrentState(sol::table st) {
		if (st.valid()) {
			sol::function exe;
			exe = st["enter"];
			exe(owner);
		}
		currentState = st;
	}
	void setGlobalState(sol::table st) {
		if (st.valid()) {
			sol::function exe;
			exe = st["enter"];
			exe(owner);
		}
		globalState = st;
	}

	void update() const {
		sol::function exe;
		if (globalState.valid()) {
			exe = globalState["execute"];
			exe(owner);
		}
		if (currentState.valid()) {
			exe = currentState["execute"];
			exe(owner);
		}
	}

	void changeState(sol::table newState) {
		sol::function exe;

		// save current state as previous state
		previousState = currentState;
		// call the exit function of the current state
		if (currentState.valid()) {
			std::cout << "exit" << std::endl;
			exe = currentState["exit"];
			exe(owner);
		}

		// change current state to newState
		currentState = newState;
		// call the Enter function of the new currentState
		exe = currentState["enter"];
		exe(owner);
	}

	void revertToPreviousState() { currentState = previousState; }

	// accessor methods
	sol::table getPreviousState() { return previousState; }
	sol::table getCurrentState() { return currentState; }
	sol::table getGlobalState() { return globalState; }

	// returns true if the current state's type is equal to the type of the
	// class passed as a parameter.
	bool isInState(const State<entity_type>& st) const {
		return typeid(*currentState) == typeid(st);
	}

	bool handleMessage(const telegram& msg) {
		sol::function exe;
		// first see if the current state is valid and that it can handle
		// the message
		if (currentState.valid()) {
			exe = currentState["onMessage"];
			exe(owner, msg);
			return true;
		}
		// if not, and if a global state has been implemented, send
		// the message to the global state
		if (globalState.valid()) {
			exe = globalState["onMessage"];
			exe(owner, msg);
			return true;
		}
		std::cout << "FAILED " << std::endl;
		return false;
	}

	virtual ~stateMachine() {}
};

#endif
