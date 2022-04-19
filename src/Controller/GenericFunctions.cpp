#include "GenericFunctions.h"

bool m_initRandom = false;
bool m_useSeed = true;
int m_seed = 0;

bool shouldSave = false;
bool shouldLoad = false;
int last_save_time_ = -100;
int last_load_time_ = -100;
bool paused = false;
bool helpMenu = false;
bool networkMenu = false;
bool shouldShoot;
float lastShot = 0;
float shot_delay = 0;

void GenericFunctions::init_random(int seed, bool useSeed) {
	m_useSeed = useSeed;
	m_seed = seed;

	if (m_useSeed == true) {
		srand(m_seed);
	} else {
		srand(time(NULL));
	}
	m_initRandom = true;
}

void GenericFunctions::lua_access() {
	sol::state& lua = LuaManager::get_instance().get_state();

	lua.set_function("random_generator", &GenericFunctions::get_random);
	lua.set_function("current_time", &GenericFunctions::get_time);
	lua.set_function("save_game", &GenericFunctions::setIfSave);
	lua.set_function("load_game", &GenericFunctions::setIfLoad);
	lua.set_function("time_since_last_save", &GenericFunctions::timeAtLastSave);
	lua.set_function("time_since_last_load", &GenericFunctions::timeAtLastLoad);
	lua.set_function("set_pause_game", &GenericFunctions::setIfPaused);
	lua.set_function("get_pause_game", &GenericFunctions::getIfPaused);
	lua.set_function("exit_game", &GenericFunctions::exitEngine);
	lua.set_function("set_help_menu", &GenericFunctions::setifHelpMenuActive);
	lua.set_function("get_help_menu", &GenericFunctions::getIfHelpMenuActive);
	lua.set_function("camera_pos_x", &GenericFunctions::luaCamPosX);
	lua.set_function("camera_pos_y", &GenericFunctions::luaCamPosY);
	lua.set_function("camera_pos_z", &GenericFunctions::luaCamPosZ);
	lua.set_function("camera_look_x", &GenericFunctions::luaCamLookX);
	lua.set_function("camera_look_y", &GenericFunctions::luaCamLookY);
	lua.set_function("camera_look_z", &GenericFunctions::luaCamLookZ);

	lua.set_function("create_network_manager", &GenericFunctions::createNetworkManager);
	lua.set_function("exit_network_menu", &GenericFunctions::setNetworkMenuActive);
	lua.set_function("get_network_menu", &GenericFunctions::getNetworkMenuActive);

	lua.set_function("set_last_shot", &GenericFunctions::setLastShot);
	lua.set_function("set_shot_delay", &GenericFunctions::setShotDelay);
	lua.set_function("set_if_should_shoot",
	                 &GenericFunctions::setIfShouldShoot);
	lua.set_function("get_if_should_shoot",
	                 &GenericFunctions::getIfShouldShoot);
}

int GenericFunctions::get_random(int min, int max) {
	if (m_initRandom == false) {
		init_random(0, true);
	}
	return rand() % max + min;
}

int GenericFunctions::get_time() { return glfwGetTime(); }

bool GenericFunctions::getIfSave() { return shouldSave; }

void GenericFunctions::setIfSave(bool val) {
	shouldSave = val;
	if (val) {
		last_save_time_ = glfwGetTime();
	}
}

int GenericFunctions::timeAtLastSave() { return last_save_time_; }

int GenericFunctions::timeAtLastLoad() { return last_load_time_; }

bool GenericFunctions::getIfLoad() { return shouldLoad; }

void GenericFunctions::setIfLoad(bool val) {
	shouldLoad = val;
	if (val) {
		last_load_time_ = glfwGetTime();
	}
}

bool GenericFunctions::getIfPaused() { return paused; }

void GenericFunctions::setIfPaused(bool val) {
	paused = val;

	if (paused) {
		glfwSetInputMode(ReflexEngine::get_instance().window_.get_window(),
		                 GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	} else {
		glfwSetInputMode(ReflexEngine::get_instance().window_.get_window(),
		                 GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}

void GenericFunctions::exitEngine() {
	ReflexEngine::get_instance().window_.set_should_close(true);
}

void GenericFunctions::setifHelpMenuActive(bool val) { helpMenu = val; }

bool GenericFunctions::getIfHelpMenuActive() { return helpMenu; }

float GenericFunctions::luaCamPosX() {
	return ReflexEngine::get_instance().camera_.get_position().x;
}
float GenericFunctions::luaCamPosY() {
	return ReflexEngine::get_instance().camera_.get_position().y;
}
float GenericFunctions::luaCamPosZ() {
	return ReflexEngine::get_instance().camera_.get_position().z; 
}

float GenericFunctions::luaCamLookX() {
	std::cout << ReflexEngine::get_instance().camera_.get_direction().x << " : "
	          << ReflexEngine::get_instance().camera_.get_direction().y << " : "
	          << ReflexEngine::get_instance().camera_.get_direction().z
	          << std::endl;
	return ReflexEngine::get_instance().camera_.get_direction().x;
}
float GenericFunctions::luaCamLookY() {
	return ReflexEngine::get_instance().camera_.get_direction().y;
}
float GenericFunctions::luaCamLookZ() {
	return ReflexEngine::get_instance().camera_.get_direction().z;
}

void GenericFunctions::setLastShot() { lastShot = glfwGetTime(); }
void GenericFunctions::setShotDelay(float delay) { shot_delay = delay; }
void GenericFunctions::setIfShouldShoot(bool val) {
	if (lastShot < glfwGetTime() - shot_delay) {
		shouldShoot = val;
	} else if (val == false) {
		shouldShoot = val;
	}
}
bool GenericFunctions::getIfShouldShoot() { return shouldShoot; }

void GenericFunctions::createNetworkManager() { }

void GenericFunctions::setNetworkMenuActive(bool active) {
	networkMenu = active;
	/*
	if (networkMenu) {
		glfwSetInputMode(ReflexEngine::get_instance().window_.get_window(),
		                 GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	} else {
		glfwSetInputMode(ReflexEngine::get_instance().window_.get_window(),
		                 GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	*/
}

bool GenericFunctions::getNetworkMenuActive() { return (networkMenu); }