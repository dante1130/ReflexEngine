#include "EngineTime.hpp"

#include "Controller/LuaManager.hpp"

double EngineTime::curr_time_ = 0.0;
double EngineTime::prev_time_ = 0.0;
double EngineTime::delta_time_ = 0.0;
double EngineTime::fixed_delta_time_ = 0.0;
double EngineTime::time_step_ = 1.0 / 120.0;
double EngineTime::total_unpaused_time_ = 0.0;
bool EngineTime::paused_ = false;
double EngineTime::time_scale_ = 1.0;

void EngineTime::lua_access() {
	auto& lua = LuaManager::get_instance().get_state();

	auto engine_time = lua.create_named_table("Time");

	engine_time.set_function("get_delta_time", &EngineTime::get_delta_time);
	engine_time.set_function("get_fixed_delta_time",
	                         &EngineTime::get_fixed_delta_time);
	engine_time.set_function("get_time_step", &EngineTime::get_time_step);
	engine_time.set_function("get_time_scale", &EngineTime::get_time_scale);
	engine_time.set_function("get_time_unpaused",
	                         &EngineTime::get_time_unpaused);

	engine_time.set_function("set_pause", &EngineTime::set_pause);
	engine_time.set_function("set_time_scale", &EngineTime::set_time_scale);

	engine_time.set_function("is_time_step_passed",
	                         &EngineTime::is_time_step_passed);
	engine_time.set_function("is_paused", &EngineTime::is_paused);
}

void EngineTime::update_delta_time(double curr_time) {
	curr_time_ = curr_time;
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

double EngineTime::get_current_time() { return curr_time_; }

double EngineTime::get_time_unpaused() { return total_unpaused_time_; }

bool EngineTime::is_time_step_passed() {
	return fixed_delta_time_ > time_step_;
}

bool EngineTime::is_paused() { return paused_; }

double EngineTime::get_time_scale() { return time_scale_; }
