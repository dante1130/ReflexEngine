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
	/**
	 * @brief Draws an entry
	 *
	 * @param name Name of the entry logged
	 * @param time How long it took to run
	 */
	static void draw_entry(std::string name, double time);

	/**
	 * @brief Draws a header entry
	 *
	 * @param name Name of entry logged
	 * @param time How long it took to run
	 * @return true if header is opened
	 * @return false if header is closed
	 */
	static bool draw_header_entry(std::string name, double time);
};