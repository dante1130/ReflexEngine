#include "DebugGUI.hpp"

#include "View/guiManager.hpp"
#include "Controller/ReflexEngine/PerformanceLogger.hpp"

void DebugGUI::draw() {
	constexpr ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoBackground;

	ImGui::Begin("Debug Menu", nullptr, window_flags);
	PERFORMANCE_LOGGER_PUSH("Testing");
	PERFORMANCE_LOGGER_POP();

	std::vector<Performance_Log> logs = PerformanceLogger::GetLogs();
	std::string line;
	for (int count = 0; count < logs.size(); count++) {
		line = logs[count].name +
		       " time: " + std::to_string(logs[count].time_taken);
		ImGui::Text(line.c_str());
	}

	PerformanceLogger::ClearLogs();

	ImGui::End();
}