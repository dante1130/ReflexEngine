#include "PseudoRandomNumberGenerator.hpp"

void PseudoRandomNumberGenerator::lua_access() {
	sol::state& lua = LuaManager::get_instance().get_state();

	lua.set_function("init_random_generator", init_random);
	lua.set_function("random_generator", get_random);
}

void PseudoRandomNumberGenerator::init_random(int seed, bool useSeed) {
	m_useSeed = useSeed;
	m_seed = seed;

	if (m_useSeed == true) {
		srand(m_seed);
	} else {
		srand(time(nullptr));
	}
	m_initRandom = true;
}

int PseudoRandomNumberGenerator::get_random(int min, int max) {
	if (m_initRandom == false) {
		init_random(m_seed, m_useSeed);
	}
	return rand() % max + min;
}
