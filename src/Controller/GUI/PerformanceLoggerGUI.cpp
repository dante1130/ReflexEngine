#include "PerformanceLoggerGUI.hpp"
#include <iostream>
#include "View/guiManager.hpp"
#include "Controller/GUI/DebugLogger.hpp"
#include <unordered_map>

constexpr float INDENT_AMOUNT = 25.0f;

void PerformanceLoggerGUI::draw() {
	std::vector<Performance_Log> logs = PerformanceLogger::GetLogs();
	int size = static_cast<int>(logs.size());
	std::unordered_map<int, bool> opened_headers;
	bool open = false;
	for (int count = 0; count < size - 1; count++) {
		// Should be a header
		if (logs[count].indent < logs[count + 1].indent) {
			if (logs[count].indent != 0) {
				if (opened_headers[logs[count].indent]) {
					open = draw_header_entry(logs[count].name,
					                         logs[count].time_taken);
					opened_headers.insert({logs[count].indent + 1, open});
					opened_headers[logs[count].indent + 1] = open;  // Yes
				}
			} else {  // If not a header
				open =
				    draw_header_entry(logs[count].name, logs[count].time_taken);
				opened_headers.insert({logs[count].indent + 1, open});
				opened_headers[logs[count].indent + 1] = open;  // Yes
			}

		} else if (opened_headers[logs[count].indent]) {
			draw_entry(logs[count].name, logs[count].time_taken);
		}

		// Sets the indents
		if (logs[count].indent < logs[count + 1].indent) {
			ImGui::Indent(INDENT_AMOUNT);
		} else if (logs[count].indent > logs[count + 1].indent) {
			ImGui::Indent(-INDENT_AMOUNT);
			opened_headers[logs[count].indent] =
			    false;  // Close up open header after it de-indents
		}
	}

	if (opened_headers[logs[size - 1].indent]) {
		draw_entry(logs[size - 1].name, logs[size - 1].time_taken);
	}

	PerformanceLogger::ClearLogs();
}

void PerformanceLoggerGUI::draw_entry(std::string name, double time) {
	ImGui::Text(name.c_str());
	ImGui::SameLine(ImGui::GetWindowWidth() - 75.0f);
	ImGui::Text(std::to_string(time).c_str());
}

bool PerformanceLoggerGUI::draw_header_entry(std::string name, double time) {
	bool open = ImGui::CollapsingHeader(name.c_str(),
	                                    ImGuiTreeNodeFlags_AllowItemOverlap);
	ImGui::SameLine(ImGui::GetWindowWidth() - 75.0f);
	ImGui::Text(std::to_string(time).c_str());
	return open;
}