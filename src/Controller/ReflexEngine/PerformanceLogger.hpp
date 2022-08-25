#pragma once

#include <string>
#include <vector>
#include <chrono>

#ifndef NDEBUG
#define PERFORMANCE_LOGGER_PUSH(Name) PerformanceLogger::Push(Name)
#define PERFORMANCE_LOGGER_POP() PerformanceLogger::Pop()
#else
#define PERFORMANCE_LOGGER_PUSH(Name)
#define PERFORMANCE_LOGGER_POP()
#endif

struct Performance_Log {
	std::string name;
	double time_taken = -1;
	std::chrono::steady_clock::time_point start_time;
	int indent = 0;
	uint64_t parent_index = -1;
};

class PerformanceLogger {
public:
	static void Push(const std::string& name);
	static void Pop();
	static const std::vector<Performance_Log>& GetLogs() { return logs; }
	static void ClearLogs() { logs.clear(); }

private:
	static std::vector<Performance_Log> logs;
	static int current_indent;
};
