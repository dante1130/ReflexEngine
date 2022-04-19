#pragma once

#include <GLFW/glfw3.h>

/**
 * @class InputState
 * @brief A class that represents the state of a key.
 */
class InputState {
public:
	/**
	 * @brief Construct a new Input State object.
	 */
	InputState() = default;

	/**
	 * @brief Set the key state.
	 *
	 * @param action
	 */
	void set_key_state(int action);

	/**
	 * @brief Returns a boolean whether the key is pressed.
	 *
	 * @return true
	 * @return false
	 */
	bool is_key_pressed();

	/**
	 * @brief Returns a boolean whether the key is held.
	 *
	 * @return true
	 * @return false
	 */
	bool is_key_hold();

	/**
	 * @brief Returns a boolean whether the key is released.
	 *
	 * @return true
	 * @return false
	 */
	bool is_key_released();

private:
	/// The current key state.
	int current_key_state = GLFW_RELEASE;

	/// The previous key state.
	int previous_key_state = GLFW_RELEASE;
};
