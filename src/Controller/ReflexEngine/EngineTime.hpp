#pragma once

class EngineTime {
public:
	/**
	 * @brief Register the EngineTime class to the Lua state.
	 */
	static void lua_access();

	/**
	 * @brief	Updates the delta time
	 * @param	curr_time The current time
	 */
	static void update_delta_time(double curr_time);

	/**
	 * @brief	resets the fixed delta time back to 0
	 */
	static void reset_fixed_delta_time();

	/**
	 * @brief	Forces the new delta time
	 * @param	new_time The new delta time
	 */
	static void force_delta_time(double new_time);

	/**
	 * @brief	Sets if it should pause
	 * @param	new_pause Set if it should pause
	 */
	static void set_pause(bool new_pause);

	/**
	 * @brief	Changes the time scale of the engine
	 * @param	new_time_scale Changes the time scale of the engine
	 */
	static void set_time_scale(double new_time_scale);

	/**
	 * @brief	gets the fixed delta time
	 * @return	double	- the fixed delta time
	 */
	static double get_fixed_delta_time();

	/**
	 * @brief	gets the delta time
	 * @return	double	- delta time
	 */
	static double get_delta_time();

	/**
	 * @brief Get the current time of runtime.
	 * @return double - The current time of runtime.
	 */
	static double get_current_time();

	/**
	 * @brief	gets the time unpaused
	 * @return	double	- the total time unpaused
	 */
	static double get_time_unpaused();

	/**
	 * @brief Get the time step of the fixed update.
	 * @return double
	 */
	static double get_time_step();

	/**
	 * @brief Returns whether the fixed delta time has exceeded the time step.
	 *
	 * @return true
	 * @return false
	 */
	static bool is_time_step_passed();

	/**
	 * @brief	gets if the game is paused
	 * @return	bool	- true is paused
	 */
	static bool is_paused();

	/**
	 * @brief	gets the time scale
	 * @return	double	- the time scale
	 */
	static double get_time_scale();

private:
	/// The current time.
	static double curr_time_;
	/// The previous time.
	static double prev_time_;
	/// The delta time.
	static double delta_time_;
	/// The fixed delta time.
	static double fixed_delta_time_;
	/// The time step for fixed update.
	static double time_step_;
	/// The total unpaused time
	static double total_unpaused_time_;
	/// If the engine time is paused
	static bool paused_;
	/// The time scale of the engine
	static double time_scale_;
};
