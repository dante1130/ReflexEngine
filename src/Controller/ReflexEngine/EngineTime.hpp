#pragma once

class EngineTime {
public:
	static void update_delta_time(float curr_time);

	static void reset_fixed_delta_time();

	static void force_delta_time(float new_time);

	static void set_pause(bool new_pause);

	static void set_time_scale(float new_time_scale);

	static float get_fixed_delta_time();

	static float get_delta_time();

	static float get_time_step();

	static float get_time_unpaused();

	static bool is_time_step_passed();

	static bool is_paused();

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
