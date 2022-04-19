#include "InputState.hpp"

#include <iostream>

void InputState::set_key_state(int action) {
	previous_key_state = current_key_state;
	current_key_state = action;
}

bool InputState::is_key_pressed() {
	return current_key_state == GLFW_PRESS &&
	       previous_key_state == GLFW_RELEASE;
}

bool InputState::is_key_hold() { return current_key_state == GLFW_PRESS; }

bool InputState::is_key_released() { return current_key_state == GLFW_RELEASE; }
