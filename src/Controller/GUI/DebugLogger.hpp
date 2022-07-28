#pragma once

#include "View/guiManager.hpp"

class DebugLogger {
public:
	DebugLogger();

	static void lua_access();

	static void clear();

	static void log(const std::string& category, const std::string& message);

	static void draw();

private:
	static ImGuiTextBuffer buffer_;
	static ImGuiTextFilter filter_;
	static ImVector<int> line_offsets_;
	static bool auto_scroll_;
};