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

/**
 * @author Daniel Rodic
 * @brief A log to store all the different values needed to determine
 * performance of a function
 *
 */
struct Performance_Log {
	/// The name for the performance log
	std::string name;
	/// The time taken for the test
	double time_taken = -1;
	/// The start time of the log
	std::chrono::steady_clock::time_point start_time;
	/// The indent for recursive logs
	int indent = 0;
	/// The parent index for recursive logs
	uint64_t parent_index = -1;
};

/**
 * @author Daniel Rodic
 * @brief Provides methods for determining the performance of different methods
 * inside the engine
 *
 */
class PerformanceLogger {
public:
	/**
	 * @brief Starts a new log recording for a particular section of code (until
	 * pop method is called)
	 *
	 * @param name The name of for the new log
	 */
	static void Push(const std::string& name);

	/**
	 * @brief Ends the performance log recording of a section of code
	 */
	static void Pop();

	/**
	 * @brief Get the Logs object
	 *
	 * @return const std::vector<Performance_Log>&
	 */

	static const std::vector<Performance_Log>& GetLogs();
	/**
	 * @brief Clears all stored logs for the next bunch
	 */
	static void ClearLogs();

private:
	/// The log storage
	static std::vector<Performance_Log> logs;
	/// The current index (recursion)
	static int current_indent;
};
