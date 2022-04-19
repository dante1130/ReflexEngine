#pragma once

#include <unordered_map>

#include <GLFW/glfw3.h>

#include "Input.hpp"
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
	 * @brief Load the bindings from a Lua file.
	 *
	 * @param file_path
	 */
	void load_lua_bindings(const std::string& file_path);

	/**
	 * @brief Bind an input action to a key.
	 *
	 * @param input - The input
	 * @param key	- The key to bind
	 */
	void bind_key(Input input, int key);

	/**
	 * @brief Read the key states.
	 *
	 * @param window	- The window
	 */
	void read_keys(GLFWwindow* window);

	/**
	 * @brief Return the key state of an input action.
	 *
	 * @param input		- Input
	 * @return InputState	- Input state
	 */
	InputState get_key_state(Input input);

	// These are deleted as a singleton pattern is used.
	InputManager(InputManager& other) = delete;
	InputManager(const InputManager& other) = delete;
	void operator=(InputManager&&) = delete;
	void operator=(const InputManager&) = delete;

private:
	/**
	 * @brief Initialize bind map.
	 */
	void init_bind_map();

	/**
	 * @brief Initialize action map.
	 */
	void init_action_map();

	/**
	 * @brief Construct a new Input Manager object
	 */
	InputManager();

	/// A map of input actions to keys.
	std::unordered_map<Input, int> key_map;

	/// A map of lua action to input actions.
	std::unordered_map<std::string, Input> action_map;

	/// A map of lua keys to GLFW keys.
	std::unordered_map<std::string, int> bind_map;

	/// A boolean array of key states.
	InputState key_states[GLFW_KEY_LAST];
};
