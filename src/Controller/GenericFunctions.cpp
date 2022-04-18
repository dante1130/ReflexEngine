#include "GenericFunctions.h"

bool m_initRandom = false;
bool m_useSeed = true;
int m_seed = 0;

bool shouldSave = false;
bool shouldLoad = false;
bool paused = false;
bool helpMenu = false;

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
	lua.set_function("save_game", &GenericFunctions::setIfSave);
	lua.set_function("load_game", &GenericFunctions::setIfLoad);
	lua.set_function("set_pause_game", &GenericFunctions::setIfPaused);
	lua.set_function("get_pause_game", &GenericFunctions::getIfPaused);
	lua.set_function("exit_game", &GenericFunctions::exitEngine);
	lua.set_function("set_help_menu", &GenericFunctions::setifHelpMenuActive);
	lua.set_function("get_help_menu", &GenericFunctions::getIfHelpMenuActive);
}

int GenericFunctions::get_random(int min, int max) {
	if (m_initRandom == false) {
		init_random(0, true);
	}
	return rand() % max + min;
}

bool GenericFunctions::getIfSave() { return shouldSave; }

void GenericFunctions::setIfSave(bool val) { shouldSave = val; }

bool GenericFunctions::getIfLoad() { return shouldLoad; }

void GenericFunctions::setIfLoad(bool val) { shouldLoad = val; }

bool GenericFunctions::getIfPaused() { return paused; }

void GenericFunctions::setIfPaused(bool val) { paused = val; }

void GenericFunctions::exitEngine() {
	ReflexEngine::get_instance().window_.set_should_close(true);
}

void GenericFunctions::setifHelpMenuActive(bool val) { helpMenu = val; }

bool GenericFunctions::getIfHelpMenuActive() { return helpMenu; }
