#pragma once

#include "ReflexEngine/ReflexEngine.hpp"
#include "LuaManager.hpp"
#include <time.h>
#include <random>

namespace GenericFunctions {
/**
 * @brief	Exposes generic functions methods to lua
 * @param	No param
 * @return	Void
 *
 * @pre		Nothing
 * @post	Exposes funciton to lua
 */
void lua_access();

/**
 * @brief	Initialises rand
 * @param	seed	- The seed of the random generator
 * @param	useSeed	- If you want to use the seed or just use time
 * @return	Void
 *
 * @pre		Nothing
 * @post	initialises rand
 */
void init_random(int seed, bool useSeed);

/**
 * @brief	Gets a random number
 * @param	min	- The minimum value
 * @param	max	- The maximum value
 * @return	int	- The value generated
 *
 * @pre		Nothing
 * @post	gets random number
 */
int get_random(int min, int max);

/**
 * @brief	gets if the game should be saved
 * @param	No param
 * @return	bool	- true if it should be saved
 *
 * @pre		Nothing
 * @post	retrieves value
 */
bool getIfSave();

/**
 * @brief	Sets if the game should be saved
 * @param	val	- If the game should be saved
 * @return	Void
 *
 * @pre		Nothing
 * @post	sets value
 */
void setIfSave(bool val);

/**
 * @brief	Gets if the game should load game objects from save
 * @param	No param
 * @return	bool	- If it should load
 *
 * @pre		Nothing
 * @post	retrieves value
 */
bool getIfLoad();

/**
 * @brief	Set if game should load objects from save
 * @param	val	- If it should load objects from save
 * @return	Void
 *
 * @pre		Nothing
 * @post	sets value
 */
void setIfLoad(bool val);

/**
 * @brief	Gets if the game should be paused
 * @param	No param
 * @return	bool	- True if game is paused
 *
 * @pre		Nothing
 * @post	retrieves value
 */
bool getIfPaused();

/**
 * @brief	Sets if the game should be paused
 * @param	val	- set true to pause game
 * @return	Void
 *
 * @pre		Nothing
 * @post	sets value
 */
void setIfPaused(bool val);

/**
 * @brief	Exits the game
 * @param	No param
 * @return	Void
 *
 * @pre		Nothing
 * @post	Exits engine
 */
void exitEngine();

void setifHelpMenuActive(bool val);

bool getIfHelpMenuActive();

};  // namespace GenericFunctions
