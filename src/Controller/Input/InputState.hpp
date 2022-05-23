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
	 * @param action The action of the key. E.g. GLFW_PRESS.
	 */
	void set_key_state(int action);

	/**
	 * @brief Returns a boolean whether the key is pressed.
	 *
	 * @return bool
	 */
	bool is_key_pressed() const;

	/**
	 * @brief Returns a boolean whether the key is held.
	 *
	 * @return bool
	 */
	bool is_key_hold() const;

	/**
	 * @brief Returns a boolean whether the key is released.
	 *
	 * @return bool
	 */
	bool is_key_released() const;

private:
	/// The current key state.
	int current_key_state = GLFW_RELEASE;

	/// The previous key state.
	int previous_key_state = GLFW_RELEASE;
};
