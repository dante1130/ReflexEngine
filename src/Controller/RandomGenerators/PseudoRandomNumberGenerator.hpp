#pragma once

#include <random>
#include <time.h>

#include "Controller/LuaManager.hpp"

class PseudoRandomNumberGenerator {
public:
	/**
	 * @brief	Provides lua access to the pseudo random number generator
	 */
	static void lua_access();

	/*
	 * @brief	Initialises the random number generator
	 * @param	seed	- The seed to initialise with
	 * @param	useSeed	- true to use the seed, false to use time
	 */
	static void init_random(int seed, bool useSeed);

	/*
	 * @brief	Generates a random number
	 * @param	min	- The min value
	 * @param	max	- The max value
	 * @return	int	- The number generated
	 */
	static int get_random(int min, int max);

private:
	/// If the generator has been initialised
	inline static bool m_initRandom = false;
	/// If you want to use the seed or not
	inline static bool m_useSeed = true;
	/// The seed being used (if used seed is true)
	inline static int m_seed = 0;
};
