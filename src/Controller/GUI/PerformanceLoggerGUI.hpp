#pragma once

#include <vector>
#include "Controller/ReflexEngine/PerformanceLogger.hpp"

/**
 * @author Daniel Rodic
 * @brief Displays the information gained from the performance logger to the GUI
 */
class PerformanceLoggerGUI {
public:
	/**
	 * @brief Draws the performance logger information
	 *
	 */
	static void draw();

private:
	static int draw_recursive(std::vector<Performance_Log> &logs, int index,
	                          int indent);

	static void draw_entry(std::string name, double time);
};