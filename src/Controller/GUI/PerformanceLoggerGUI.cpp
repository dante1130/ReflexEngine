#include "PerformanceLoggerGUI.hpp"
#include <iostream>
#include "View/guiManager.hpp"
#include "Controller/GUI/DebugLogger.hpp"

constexpr float INDENT_AMOUNT = 25.0f;

void PerformanceLoggerGUI::draw() {
	std::vector<Performance_Log> logs = PerformanceLogger::GetLogs();
	for (int count = 0; count < logs.size(); count++) {
		std::string name =
		    logs[count].name + " " + std::to_string(logs[count].indent);
		DebugLogger::log("Performance logger", name);
	}

	if (logs.size() != 0) {
		draw_recursive(logs, 0, 0);
	}

	PerformanceLogger::ClearLogs();
}

int PerformanceLoggerGUI::draw_recursive(std::vector<Performance_Log> &logs,
                                         int index, int indent) {
	std::string input_line = logs[index].name;
	uint64_t size = logs.size();
	bool open;
	bool draw = true;
	for (int count = index; count < size; count++) {
		// If not at end
		if (count + 1 < size) {
			if (logs[count].indent < logs[count + 1].indent && draw) {
				open = ImGui::CollapsingHeader(
				    logs[count].name.c_str(),
				    ImGuiTreeNodeFlags_AllowItemOverlap);
				ImGui::SameLine(ImGui::GetWindowWidth() - 75.0f);
				ImGui::Text(std::to_string(logs[count].time_taken).c_str());

				indent = logs[count].indent;
				if (open) {
					ImGui::Indent(INDENT_AMOUNT);
					count = draw_recursive(logs, count + 1, indent);
					ImGui::Indent(-INDENT_AMOUNT);
					draw = true;
				} else {
					draw = false;
				}
			} else if (logs[count].indent > logs[count + 1].indent && draw) {
				draw_entry(logs[count].name, logs[count].time_taken);
				return count;
			} else if (draw) {
				draw_entry(logs[count].name, logs[count].time_taken);
			}

		} else if (draw || logs[count].indent <= indent) {  // If at end
			draw_entry(logs[count].name, logs[count].time_taken);
		}
	}
	return size;
}

void PerformanceLoggerGUI::draw_entry(std::string name, double time) {
	ImGui::Text(name.c_str());
	ImGui::SameLine(ImGui::GetWindowWidth() - 75.0f);
	ImGui::Text(std::to_string(time).c_str());
}