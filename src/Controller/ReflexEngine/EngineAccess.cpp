#include "EngineAccess.hpp"

void EngineAccess::lua_access() {
	auto& lua = LuaManager::get_instance().get_state();

	lua.set_function("current_time", get_time);
	lua.set_function("set_pause_game", setIfPaused);
	lua.set_function("get_pause_game", getIfPaused);
	lua.set_function("exit_game", exitEngine);
	lua.set_function("window_width", get_window_width);
	lua.set_function("window_height", get_window_height);

	auto engine_time = lua.create_named_table("EngineTime");

	engine_time.set_function("get_delta_time", &EngineTime::get_delta_time);
	engine_time.set_function("get_fixed_delta_time",
	                         &EngineTime::get_fixed_delta_time);
}

int EngineAccess::get_window_width() {
	return ReflexEngine::get_instance().window_.get_buffer_width();
}

int EngineAccess::get_window_height() {
	return ReflexEngine::get_instance().window_.get_buffer_height();
}

int EngineAccess::get_time() { return glfwGetTime(); }

bool EngineAccess::getIfPaused() { return EngineTime::is_paused(); }

void EngineAccess::setIfPaused(bool val) {
	EngineTime::set_pause(val);

	if (val) {
		glfwSetInputMode(ReflexEngine::get_instance().window_.get_window(),
		                 GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	} else {
		glfwSetInputMode(ReflexEngine::get_instance().window_.get_window(),
		                 GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}

void EngineAccess::exitEngine() {
	ReflexEngine::get_instance().window_.set_should_close(true);
}

void EngineAccess::setEngineTimeScale(double timeScale) {
	EngineTime::set_time_scale(timeScale);
}
