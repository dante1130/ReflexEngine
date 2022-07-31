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
	 * @brief Log a message with a color.
	 *
	 * @param category The category of the message.
	 * @param message The message to log.
	 * @param color The color of the message.
	 */
	static void log_color(const std::string& category,
	                      const std::string& message, const ImVec4& color);

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
	/// The color of the log.
	static ImVector<ImVec4> colors_;
	/// Whether it should auto scroll.
	static bool auto_scroll_;
};