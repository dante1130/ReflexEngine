#include "PerformanceLogger.hpp"
#include "Controller/GUI/DebugLogger.hpp"

int PerformanceLogger::current_indent = 0;
std::vector<Performance_Log> PerformanceLogger::logs =
    std::vector<Performance_Log>();
double PerformanceLogger::reset_time = 500;
double PerformanceLogger::remove_time = 5000;
int PerformanceLogger::position_index = 0;
std::chrono::steady_clock::time_point PerformanceLogger::start_time =
    std::chrono::steady_clock::now();

constexpr float miliseconds_in_nanoseconds = 1000000.0;

void PerformanceLogger::Push(const std::string &id_name) {
	uint64_t size = logs.size();

	if (position_index != 0) {
		if (logs[position_index - 1].time_taken < 0) {
			current_indent++;
		}
	}

	if (size == position_index) {
		add_new_log(id_name);
	} else if (!logs[position_index].name._Equal(id_name)) {
		add_new_log(id_name);
	} else {
		DebugLogger::log("PL", "Updaing entry");
		logs[position_index].start_time = std::chrono::steady_clock::now();
		// logs[position_index].indent = current_indent;
	}

	position_index++;
}

void PerformanceLogger::Pop() {
	uint64_t size = logs.size();
	if (size == 0) {
		return;
	}
	std::chrono::steady_clock::time_point end_time =
	    std::chrono::steady_clock::now();
	double time_taken = 0;

	int index = position_index - 1;
	while (true) {
		if (logs[index].used) {
			if (logs[index].parent_index == -1) break;
			index = logs[index].parent_index;
		} else {
			time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(
			                 end_time - logs[index].start_time)
			                 .count() /
			             miliseconds_in_nanoseconds;

			logs[index].time_taken =
			    ((logs[index].time_taken * logs[index].amount) + time_taken) /
			    (logs[index].amount + 1.0);

			logs[index].amount = logs[index].amount + 1;
			current_indent = logs[index].indent;

			if (logs[index].max_time_taken < time_taken) {
				logs[index].max_time_taken = time_taken;
			}
			logs[index].used = true;
			break;
		}
	}
}

const std::vector<Performance_Log> &PerformanceLogger::GetLogs() {
	return logs;
}

void PerformanceLogger::ClearLogs() {
	current_indent = 0;
	position_index = 0;

	check_logs();

	int size = logs.size();
	for (int count = 0; count < size; count++) {
		logs[count].used = false;
	}

	std::chrono::steady_clock::time_point end_time =
	    std::chrono::steady_clock::now();
	double time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(
	                        end_time - start_time)
	                        .count() /
	                    miliseconds_in_nanoseconds;
	if (time_taken > remove_time) {
		logs.clear();
		DebugLogger::log("PL", "Resetting performance logs");
		start_time = end_time;
	} else if (time_taken > reset_time) {
		for (int count = 0; count < size; count++) {
			logs[count].amount = 0;
			logs[count].time_taken = -1;
		}
	}
}

void PerformanceLogger::add_new_log(const std::string &name) {
	Performance_Log new_log;

	new_log.name = name;
	new_log.start_time = std::chrono::steady_clock::now();
	if (!logs.empty()) {
		if (logs[position_index - 1].time_taken < 0) {
			new_log.parent_index = position_index - 1;
		} else {
			new_log.parent_index = logs[position_index - 1].parent_index;
		}
	}
	new_log.indent = current_indent;

	logs.insert(logs.begin() + position_index, new_log);
}

void PerformanceLogger::check_logs() {
	uint64_t size = logs.size();

	std::chrono::steady_clock::time_point end_time =
	    std::chrono::steady_clock::now();
	double time_taken = 0;
	for (uint64_t count = 0; count < size; count++) {
		time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(
		                 end_time - logs[count].start_time)
		                 .count() /
		             miliseconds_in_nanoseconds;

		if (time_taken > remove_time) {
			logs.erase(logs.begin() + count);
		}

		logs[count].used = false;
	}

	//
	//
	// Also need to change indent of all child logs
	//
	//
}