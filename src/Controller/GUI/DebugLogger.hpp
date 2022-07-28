#pragma once

#include "View/guiManager.hpp"

/**
 * @class DebugLogger
 * @brief A class that logs debug messages using ImGui.
 */
class DebugLogger {
public:
	/**
	 * @brief Expose the DebugLogger to Lua.
	 */
	static void lua_access();

	/**
	 * @brief Clear the log.
	 */
	static void clear();

	/**
	 * @brief Log a message.
	 *
	 * @param category The category of the message.
	 * @param message The message to log.
	 */
	static void log(const std::string& category, const std::string& message);

	/**
	 * @brief Draws the DebugLogger.
	 */
	static void draw();

private:
	/// The text buffer.
	static ImGuiTextBuffer buffer_;
	/// The text filter.
	static ImGuiTextFilter filter_;
	/// Line offsets.
	static ImVector<int> line_offsets_;
	/// Whether it should auto scroll.
	static bool auto_scroll_;
};