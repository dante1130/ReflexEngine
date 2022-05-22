#include "EngineTime.hpp"
float EngineTime::prev_time_ = 0.0f;
float EngineTime::delta_time_ = 0.0f;
float EngineTime::fixed_delta_time_ = 0.0f;
float EngineTime::total_unpaused_time_ = 0.0f;
bool EngineTime::paused_ = true;
float EngineTime::time_scale_ = 1.0f;

void EngineTime::update_delta_time(float curr_time) {
	curr_time *= time_scale_;

	delta_time_ = curr_time - prev_time_;
	fixed_delta_time_ += delta_time_;
	prev_time_ = curr_time;

	if (!paused_) {
		total_unpaused_time_ += delta_time_;
	}
}

void EngineTime::reset_fixed_delta_time() { fixed_delta_time_ = 0.0f; }

void EngineTime::force_delta_time(float new_time) { delta_time_ = new_time; }

void EngineTime::set_pause(bool new_pause) { paused_ = new_pause; }

void EngineTime::set_time_scale(float new_time_scale) {
	time_scale_ = new_time_scale;
}

float EngineTime::get_fixed_delta_time() { return fixed_delta_time_; }

float EngineTime::get_delta_time() { return delta_time_; }

float EngineTime::get_time_step() { return time_step; }

float EngineTime::get_time_unpaused() { return total_unpaused_time_; }

bool EngineTime::is_time_step_passed() { return fixed_delta_time_ > time_step; }

bool EngineTime::is_paused() { return paused_; }

float EngineTime::get_time_scale() { return time_scale_; }
