#pragma once

#include <unordered_map>
#include <array>

#include <GLFW/glfw3.h>

#include "InputState.hpp"

/**
 * @class InputManager
 * @brief A singleton class that manages input bindings.
 */
class InputManager {
public:
	/**
	 * @brief Get the instance.
	 *
	 * @return InputManager&
	 */
	static InputManager& get_instance();

	/**
	 * @brief Expose the InputManager to lua.
	 */
	void lua_access();

	/**
	 * @brief Read the key states.
	 *
	 * @param window The window.
	 */
	void read_keys(GLFWwindow* window);

	/**
	 * @brief Read the mouse button states.
	 *
	 * @param window
	 */
	void read_mouse_buttons(GLFWwindow* window);

	/**
	 * @brief Return the key state of an input action.
	 *
	 * @param bind The key binding.
	 * @return InputState
	 */
	const InputState& get_key_state(const std::string& bind);

	/**
	 * @brief Return the mouse key state of an input action.
	 *
	 * @param bind The mouse key binding.
	 * @return InputState
	 */
	const InputState& get_mouse_key_state(const std::string& bind);

	// These are deleted as a singleton pattern is used.
	InputManager(InputManager& other) = delete;
	InputManager(const InputManager& other) = delete;
	void operator=(InputManager&&) = delete;
	void operator=(const InputManager&) = delete;

private:
	/**
	 * @brief Construct a new Input Manager object
	 */
	InputManager();

	/// A map of lua keys to GLFW keys.
	std::unordered_map<std::string, int> bind_map;

	/// A map of lua keys to GLFW mouse buttons.
	std::unordered_map<std::string, int> mouse_bind_map;

	/// A boolean array of key states.
	std::array<InputState, GLFW_KEY_LAST> key_states;
};
