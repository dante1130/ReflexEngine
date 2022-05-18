#ifndef __STATEMACHINE_H
#define __STATEMACHINE_H

#include <iostream>
using namespace std;
#include "state.h"

template <class entity_type>
class stateMachine {
private:
	entity_type* owner;  // owner of the FSM
	State<entity_type>* previousState;
	State<entity_type>* currentState;
	State<entity_type>* globalState;

public:
	const stateMachine& operator=(const stateMachine& sm) {
		owner = sm.owner;
		previousState = sm.previousState;
		currentState = sm.currentState;
		globalState = sm.globalState;
		return *this;
	}

	stateMachine(entity_type* FSMowner) {
		owner = FSMowner;
		previousState = NULL;
		currentState = NULL;
		globalState = NULL;
	}

	// use the following methods to intialise the FSM
	void setPreviousState(State<entity_type>* st) { previousState = st; }
	void setCurrentState(State<entity_type>* st) { currentState = st; }
	void setGlobalState(State<entity_type>* st) { globalState = st; }

	void update() const {
		if (globalState) globalState->Execute(owner);
		if (currentState) currentState->Execute(owner);
	}

	void changeState(State<entity_type>* newState) {
		// save current state as previous state
		previousState = currentState;
		// call the exit function of the current state
		currentState->Exit(owner);

		// change current state to newState
		currentState = newState;
		// call the Enter function of the new currentState
		currentState->Enter(owner);
	}

	void revertToPreviousState() { currentState = previousState; }

	// accessor methods
	State<entity_type>* getPreviousState() { return previousState; }
	State<entity_type>* getCurrentState() { return currentState; }
	State<entity_type>* getGlobalState() { return globalState; }

	// returns true if the current state's type is equal to the type of the
	// class passed as a parameter.
	bool isInState(const State<entity_type>& st) const {
		return typeid(*currentState) == typeid(st);
	}

	bool handleMessage(const telegram& msg) {
		// first see if the current state is valid and that it can handle
		// the message
		if (currentState && currentState->onMessage(owner, msg)) {
			return true;
		}
		// if not, and if a global state has been implemented, send
		// the message to the global state
		if (globalState && globalState->onMessage(owner, msg)) {
			return true;
		}
		std::cout << "FAILED " << std::endl;
		return false;
	}

	virtual ~stateMachine() {}
};

#endif
