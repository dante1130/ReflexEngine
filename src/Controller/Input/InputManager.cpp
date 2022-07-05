#include "InputManager.hpp"

#include <cctype>

#include "Controller/LuaManager.hpp"

InputManager& InputManager::get_instance() {
	static InputManager instance;
	return instance;
}

void InputManager::lua_access() {
	auto& lua = LuaManager::get_instance().get_state();

	auto input_state_type = lua.new_usertype<InputState>(
	    "InputState", sol::constructors<InputState()>());

	input_state_type["is_key_pressed"] = &InputState::is_key_pressed;
	input_state_type["is_key_released"] = &InputState::is_key_released;
	input_state_type["is_key_hold"] = &InputState::is_key_hold;

	auto input_manager = lua.create_named_table("Input");

	input_manager.set_function("get_key_state", &InputManager::get_key_state,
	                           this);
	input_manager.set_function("get_mouse_key_state",
	                           &InputManager::get_mouse_key_state, this);
}

void InputManager::read_keys(GLFWwindow* window) {
	for (const auto& [bind, key] : bind_map) {
		const int state = glfwGetKey(window, key);

		if (state == GLFW_PRESS || state == GLFW_RELEASE) {
			key_states.at(bind_map.at(bind)).set_key_state(state);
		}
	}

	// Check for ASCII key presses.
	constexpr size_t ascii_size = 256ULL;

	for (size_t i = 0; i < ascii_size; ++i) {
		const int state = glfwGetKey(window, i);

		if (state == GLFW_PRESS || state == GLFW_RELEASE) {
			key_states.at(i).set_key_state(state);
		}
	}
}

void InputManager::read_mouse_buttons(GLFWwindow* window) {
	for (const auto& [bind, key] : mouse_bind_map) {
		const int state = glfwGetMouseButton(window, key);

		if (state == GLFW_PRESS || state == GLFW_RELEASE) {
			key_states.at(mouse_bind_map.at(bind)).set_key_state(state);
		}
	}
}

const InputState& InputManager::get_key_state(const std::string& bind) {
	if (bind.length() > 1) {
		return key_states.at(bind_map.at(bind));
	} else {
		return key_states.at(toupper(bind[0]));
	}
}

const InputState& InputManager::get_mouse_key_state(const std::string& bind) {
	return key_states.at(mouse_bind_map.at(bind));
}

InputManager::InputManager()
    : bind_map({{"escape", GLFW_KEY_ESCAPE},
                {"lshift", GLFW_KEY_LEFT_SHIFT},
                {"rshift", GLFW_KEY_RIGHT_SHIFT},
                {"lctrl", GLFW_KEY_LEFT_CONTROL},
                {"rctrl", GLFW_KEY_RIGHT_CONTROL},
                {"lalt", GLFW_KEY_LEFT_ALT},
                {"ralt", GLFW_KEY_RIGHT_ALT},
                {"up", GLFW_KEY_UP},
                {"down", GLFW_KEY_DOWN},
                {"left", GLFW_KEY_LEFT},
                {"right", GLFW_KEY_RIGHT},
                {"space", GLFW_KEY_SPACE},
                {"tab", GLFW_KEY_TAB},
                {"backspace", GLFW_KEY_BACKSPACE},
                {"enter", GLFW_KEY_ENTER},
                {"insert", GLFW_KEY_INSERT},
                {"delete", GLFW_KEY_DELETE},
                {"home", GLFW_KEY_HOME},
                {"end", GLFW_KEY_END},
                {"pageup", GLFW_KEY_PAGE_UP},
                {"pagedown", GLFW_KEY_PAGE_DOWN},
                {"f1", GLFW_KEY_F1},
                {"f2", GLFW_KEY_F2},
                {"f3", GLFW_KEY_F3},
                {"f4", GLFW_KEY_F4},
                {"f5", GLFW_KEY_F5},
                {"f6", GLFW_KEY_F6},
                {"f7", GLFW_KEY_F7},
                {"f8", GLFW_KEY_F8},
                {"f9", GLFW_KEY_F9},
                {"f10", GLFW_KEY_F10},
                {"f11", GLFW_KEY_F11},
                {"f12", GLFW_KEY_F12}}),
      mouse_bind_map({{"mouse1", GLFW_MOUSE_BUTTON_1},
                      {"mouse2", GLFW_MOUSE_BUTTON_2},
                      {"mouse3", GLFW_MOUSE_BUTTON_3},
                      {"mouse4", GLFW_MOUSE_BUTTON_4},
                      {"mouse5", GLFW_MOUSE_BUTTON_5},
                      {"mouse6", GLFW_MOUSE_BUTTON_6},
                      {"mouse7", GLFW_MOUSE_BUTTON_7},
                      {"mouse8", GLFW_MOUSE_BUTTON_8}}) {}
