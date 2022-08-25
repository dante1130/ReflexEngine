#include "DebugGUI.hpp"

#include "View/guiManager.hpp"
#include "Controller/GUI/PerformanceLoggerGUI.hpp"
#include "Controller/ReflexEngine/PerformanceLogger.hpp"

constexpr float INDENT_AMOUNT = 25;

void DebugGUI::draw() {
	constexpr ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoBackground;

	ImGui::Begin("Debug Menu", nullptr, window_flags);

	if (ImGui::CollapsingHeader("Performance Times",
	                            ImGuiTreeNodeFlags_AllowItemOverlap)) {
		PERFORMANCE_LOGGER_POP();
		ImGui::Indent(INDENT_AMOUNT);
		PerformanceLoggerGUI::draw();
		ImGui::Indent(-INDENT_AMOUNT);
		PERFORMANCE_LOGGER_PUSH("Total Engine Time");
	}

	ImGui::End();
}