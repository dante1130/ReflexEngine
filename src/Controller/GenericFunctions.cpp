#include "GenericFunctions.h"

bool m_initRandom = false;
bool m_useSeed = true;
int m_seed = 0;

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
}

int GenericFunctions::get_random(int min, int max) {
	if (m_initRandom == false) {
		init_random(0, true);
	}
	return rand() % max + min;
}

bool shouldSave = false;
bool shouldLoad = false;

bool GenericFunctions::getIfSave() { return shouldSave; }
void GenericFunctions::setIfSave(bool val) { shouldSave = val; }
bool GenericFunctions::getIfLoad() { return shouldLoad; }
void GenericFunctions::setIfLoad(bool val) { shouldLoad = val; }
