#pragma once

class EngineTime {
public:
	/**
	 * @brief	Updates the delta time
	 * @param	curr_time	- The current time
	 */
	static void update_delta_time(float curr_time);

	/**
	 * @brief	resets the fixed delta time back to 0
	 */
	static void reset_fixed_delta_time();

	/**
	 * @brief	Forces the new delta time
	 * @param	new_time	- The new delta time
	 */
	static void force_delta_time(float new_time);

	/**
	 * @brief	Sets if it should pause
	 * @param	new_pause	- Set if it should pause
	 */
	static void set_pause(bool new_pause);

	/**
	 * @brief	Changes the time scale of the engine
	 * @param	new_time_scale	- Changes the time scale of the engine
	 */
	static void set_time_scale(float new_time_scale);

	/**
	 * @brief	gets the fixed delta time
	 * @return	float	- the fixed delta time
	 */
	static float get_fixed_delta_time();

	/**
	 * @brief	gets the delta time
	 * @return	float	- delta time
	 */
	static float get_delta_time();

	/**
	 * @brief	gets the time unpaused
	 * @return	float	- the total time unpaused
	 */
	static float get_time_unpaused();
	
	static float get_time_step();

	static bool is_time_step_passed();

	/**
	 * @brief	gets if the game is paused
	 * @return	bool	- true is paused
	 */
	static bool is_paused();

	/**
	 * @brief	gets the time scale
	 * @return	float	- the time scale
	 */
	static float get_time_scale();

private:
	/// The previous time.
	static float prev_time_;
	/// The delta time.
	static float delta_time_;
	/// The fixed delta time.
	static float fixed_delta_time_;
	/// The time step for fixed update.
	static constexpr float time_step = 1.0F / 60.0F;
	/// The total unpaused time
	static float total_unpaused_time_;
	/// If the engine time is paused
	static bool paused_;
	/// The time scale of the engine
	static float time_scale_;
};
