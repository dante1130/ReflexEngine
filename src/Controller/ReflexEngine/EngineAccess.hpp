#pragma once
#include "Controller/ReflexEngine/EngineTime.hpp"
#include "Controller/ReflexEngine/ReflexEngine.hpp"
#include "Controller/LuaManager.hpp"

namespace EngineAccess {
/**
 *	Provides lua access to basic engine components (e.g., setting time scale)
 */
void lua_access();

/**
 * @brief Get the window width.
 * @return int
 */
int get_window_width();

/**
 * @brief Get the window height.
 * @return int
 */
int get_window_height();

/**
 * @brief	Gets time
 * @return	int	- The time
 */
int get_time();

/**
 * @brief	Gets if the game should be paused
 * @return	bool	- True if game is paused
 */
bool getIfPaused();

/**
 * @brief	Sets if the game should be paused
 * @param	val	- set true to pause game
 */
void setIfPaused(bool val);

/**
 * @brief	Exits the game
 */
void exitEngine();

/**
 * @brief	Changes the time scale of the engine
 * @param	double	- The time scale to change to.
 */
void setEngineTimeScale(double timeScale);

}  // namespace EngineAccess
