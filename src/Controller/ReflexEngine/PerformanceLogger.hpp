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
	/// The average time taken over x seconds
	double time_taken = -1;
	/// How many times are stored in time_taken
	int amount = 0;
	/// The max time taken over x seconds
	double max_time_taken = -1;
	/// The start time of the log
	std::chrono::steady_clock::time_point start_time;
	/// The indent for recursive logs
	int indent = 0;
	/// The parent index for recursive logs
	int parent_index = -1;
	bool used = false;
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
	/// When to reset the values in the Performance Logs
	static double reset_time;
	/// When to remove old values in the Performance Logs
	static double remove_time;
	/// The current position in the logs
	static int position_index;
	/// The start time of the new batch of logs
	static std::chrono::steady_clock::time_point start_time;

	/**
	 * @brief Adds a new log to the performance log list
	 *
	 * @param name the name of the log you are adding
	 */
	static void add_new_log(const std::string& name);
};
