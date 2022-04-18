#include "InputManager.hpp"

#include <cctype>

#include "Controller/LuaManager.hpp"

InputManager& InputManager::get_instance() {
	static InputManager instance;
	return instance;
}

void InputManager::load_lua_bindings(const std::string& file_path) {
	auto& lua = LuaManager::get_instance().get_state();
	lua.script_file(file_path);

	sol::table bindings = lua["Bindings"];

	for (const auto& binding : bindings) {
		std::string action = binding.first.as<std::string>();
		std::string bind = binding.second.as<std::string>();

		Input input = action_map[action];

		if (bind.length() > 1) {
			int key = bind_map[bind];
			bind_key(input, key);
		} else {
			int key = toupper(bind[0]);
			bind_key(input, key);
		}
	}
}

void InputManager::bind_key(Input input, int key) { key_map[input] = key; }

void InputManager::read_keys(int key, int action) {
	if (action == GLFW_PRESS) {
		key_states[key] = true;
	} else if (action == GLFW_RELEASE) {
		key_states[key] = false;
	}
}

bool InputManager::get_key_state(Input input) {
	return key_states[key_map[input]];
}

void InputManager::init_bind_map() {
	bind_map["escape"] = GLFW_KEY_ESCAPE;
	bind_map["mouse1"] = GLFW_MOUSE_BUTTON_1;
	bind_map["mouse2"] = GLFW_MOUSE_BUTTON_2;
	bind_map["mouse3"] = GLFW_MOUSE_BUTTON_3;
	bind_map["lshift"] = GLFW_KEY_LEFT_SHIFT;
	bind_map["rshift"] = GLFW_KEY_RIGHT_SHIFT;
	bind_map["lctrl"] = GLFW_KEY_LEFT_CONTROL;
	bind_map["rctrl"] = GLFW_KEY_RIGHT_CONTROL;
	bind_map["lalt"] = GLFW_KEY_LEFT_ALT;
	bind_map["ralt"] = GLFW_KEY_RIGHT_ALT;
}

void InputManager::init_action_map() {
	action_map["quit"] = Input::quit;
	action_map["move_forward"] = Input::move_forward;
	action_map["move_backward"] = Input::move_backward;
	action_map["move_left"] = Input::move_left;
	action_map["move_right"] = Input::move_right;
	action_map["sprint"] = Input::sprint;
	action_map["crouch"] = Input::crouch;
	action_map["shoot"] = Input::shoot;
	action_map["toggle_wireframe"] = Input::toggle_wireframe;
	action_map["toggle_noclip"] = Input::toggle_noclip;
	action_map["pause_game"] = Input::pause_game;
}

InputManager::InputManager() {
	init_bind_map();
	init_action_map();
}
