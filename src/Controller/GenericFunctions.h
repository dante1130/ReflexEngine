#pragma once

#include "ReflexEngine/ReflexEngine.hpp"
#include "LuaManager.hpp"
#include <time.h>
#include <random>
#include "Controller/ReflexEngine/Camera.hpp"

namespace GenericFunctions {
/**
 * @brief	Exposes generic functions methods to lua
 *
 * @pre		Nothing
 * @post	Exposes funciton to lua
 */
void lua_access();

/**
 * @brief	Initialises rand
 * @param	seed	- The seed of the random generator
 * @param	useSeed	- If you want to use the seed or just use time
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
 * @return	bool	- true if it should be saved
 *
 * @pre		Nothing
 * @post	retrieves value
 */
bool getIfSave();

/**
 * @brief	Sets if the game should be saved
 * @param	val	- If the game should be saved
 *
 * @pre		Nothing
 * @post	sets value
 */
void setIfSave(bool val);

/**
 * @brief	Gets time when the game was last saved
 * @return	int	- When the game was last saved
 */
int timeAtLastSave();

/**
 * @brief	Gets time when the game was last loaded
 * @return	int	- When the game was last loaded
 */
int timeAtLastLoad();

/**
 * @brief	Gets time
 * @return	int	- The time
 */
int get_time();

/**
 * @brief	Gets if the game should load game objects from save
 * @return	bool	- If it should load
 *
 * @pre		Nothing
 * @post	retrieves value
 */
bool getIfLoad();

/**
 * @brief	Set if game should load objects from save
 * @param	val	- If it should load objects from save
 *
 * @pre		Nothing
 * @post	sets value
 */
void setIfLoad(bool val);

/**
 * @brief	Gets if the game should be paused
 * @return	bool	- True if game is paused
 *
 * @pre		Nothing
 * @post	retrieves value
 */
bool getIfPaused();

/**
 * @brief	Sets if the game should be paused
 * @param	val	- set true to pause game
 *
 * @pre		Nothing
 * @post	sets value
 */
void setIfPaused(bool val);

/**
 * @brief	Exits the game
 *
 * @pre		Nothing
 * @post	Exits engine
 */
void exitEngine();

/**
 * @brief	Sets if the game should show the help menu
 * @param	val	- set true to show help menu
 *
 * @pre		Nothing
 * @post	sets value
 */
void setifHelpMenuActive(bool val);

/**
 * @brief	gets if the game should show the help menu
 * @return	bool	- True if should show help menu
 *
 * @pre		Nothing
 * @post	gets value
 */
bool getIfHelpMenuActive();

/**
 * @brief	gets camera x position
 * @return	float	- x position
 *
 * @pre		Nothing
 * @post	gets value
 */
float luaCamPosX();

/**
 * @brief	gets camera y position
 * @return	float	- y position
 *
 * @pre		Nothing
 * @post	gets value
 */
float luaCamPosY();

/**
 * @brief	gets camera z position
 * @return	float	- z position
 *
 * @pre		Nothing
 * @post	gets value
 */
float luaCamPosZ();

/**
 * @brief	gets camera x look
 * @return	float	- x look
 *
 * @pre		Nothing
 * @post	gets value
 */
float luaCamLookX();

/**
 * @brief	gets camera y look
 * @return	float	- y look
 *
 * @pre		Nothing
 * @post	gets value
 */
float luaCamLookY();

/**
 * @brief	gets camera z look
 * @return	float	- z look
 *
 * @pre		Nothing
 * @post	gets value
 */
float luaCamLookZ();

/**
 * @brief	Sets when the last shoot was fired (time of this function being
 * called)
 *
 * @pre		Nothing
 * @post	sets last shoot
 */
void setLastShot();

/**
 * @brief	Sets delay between shots
 * @param	delay	- The delay between shots
 *
 * @pre		Nothing
 * @post	sets delay
 */
void setShotDelay(float delay);

/**
 * @brief	Sets if the player should shoot
 * @param	bool	- True if the player should shoot
 * @return	float	- z look
 *
 * @pre		Nothing
 * @post	gets value
 */
void setIfShouldShoot(bool val);

/**
 * @brief	Gets if the player should shoot
 * @return	bool	- true if should shoot
 *
 * @pre		Nothing
 * @post	gets value
 */
bool getIfShouldShoot();

};  // namespace GenericFunctions
