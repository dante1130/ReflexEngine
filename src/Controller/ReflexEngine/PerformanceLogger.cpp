#include "PerformanceLogger.hpp"

int PerformanceLogger::current_indent = 0;
std::vector<Performance_Log> PerformanceLogger::logs =
    std::vector<Performance_Log>();

void PerformanceLogger::Push(const std::string &id_name) {
	uint64_t size = logs.size();
	Performance_Log new_log;
	time_t timer;

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
		    std::chrono::duration_cast<std::chrono::microseconds>(
		        end_time - logs[log.parent_index].start_time)
		        .count();
	} else {
		log.time_taken = std::chrono::duration_cast<std::chrono::microseconds>(
		                     end_time - log.start_time)
		                     .count();
	}
}
