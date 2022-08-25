#include "PerformanceLogger.hpp"

int PerformanceLogger::current_indent = 0;
std::vector<Performance_Log> PerformanceLogger::logs =
    std::vector<Performance_Log>();

constexpr float miliseconds_in_nanoseconds = 1000000;

void PerformanceLogger::Push(const std::string &id_name) {
	uint64_t size = logs.size();
	Performance_Log new_log;

	new_log.name = id_name;
	new_log.start_time = std::chrono::steady_clock::now();
	if (size != 0) {
		if (logs[size - 1].time_taken < 0) {
			current_indent++;
			new_log.parent_index = size - 1;
		} else {
			new_log.parent_index = logs[size - 1].parent_index;
		}
	}
	new_log.indent = current_indent;

	logs.push_back(new_log);
}

void PerformanceLogger::Pop() {
	uint64_t size = logs.size();
	if (size == 0) {
		return;
	}
	std::chrono::steady_clock::time_point end_time =
	    std::chrono::steady_clock::now();
	Performance_Log &log = logs[size - 1];
	if (log.time_taken >= 0) {
		current_indent--;
		logs[log.parent_index].time_taken =
		    std::chrono::duration_cast<std::chrono::nanoseconds>(
		        end_time - logs[log.parent_index].start_time)
		        .count() /
		    miliseconds_in_nanoseconds;
	} else {
		log.time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(
		                     end_time - log.start_time)
		                     .count() /
		                 miliseconds_in_nanoseconds;
	}
}

const std::vector<Performance_Log> &PerformanceLogger::GetLogs() {
	return logs;
}

void PerformanceLogger::ClearLogs() { logs.clear(); }
