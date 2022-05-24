#include "EngineTime.hpp"

double EngineTime::prev_time_ = 0.0;
double EngineTime::delta_time_ = 0.0;
double EngineTime::fixed_delta_time_ = 0.0;
double EngineTime::total_unpaused_time_ = 0.0;
bool EngineTime::paused_ = true;
double EngineTime::time_scale_ = 1.0;

void EngineTime::update_delta_time(double curr_time) {
	curr_time *= time_scale_;

	delta_time_ = curr_time - prev_time_;
	fixed_delta_time_ += delta_time_;
	prev_time_ = curr_time;

	if (!paused_) {
		total_unpaused_time_ += delta_time_;
	}
}

void EngineTime::reset_fixed_delta_time() { fixed_delta_time_ = 0.0f; }

void EngineTime::force_delta_time(double new_time) { delta_time_ = new_time; }

void EngineTime::set_pause(bool new_pause) { paused_ = new_pause; }

void EngineTime::set_time_scale(double new_time_scale) {
	time_scale_ = new_time_scale;
}

double EngineTime::get_fixed_delta_time() { return fixed_delta_time_; }

double EngineTime::get_delta_time() { return delta_time_; }

double EngineTime::get_time_step() { return time_step_; }

double EngineTime::get_time_unpaused() { return total_unpaused_time_; }

bool EngineTime::is_time_step_passed() {
	return fixed_delta_time_ > time_step_;
}

bool EngineTime::is_paused() { return paused_; }

double EngineTime::get_time_scale() { return time_scale_; }
