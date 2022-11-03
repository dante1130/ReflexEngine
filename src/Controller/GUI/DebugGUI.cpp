#include "DebugGUI.hpp"

#include "View/guiManager.hpp"
#include "Controller/GUI/PerformanceLoggerGUI.hpp"
#include "Controller/ReflexEngine/PerformanceLogger.hpp"
#include "Model/RunTimeDataStorage/GlobalDataStorage.hpp"

constexpr float INDENT_AMOUNT = 25.0F;

void DebugGUI::draw() {
	constexpr ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoBackground;

	ImGui::Begin("Debug Menu", nullptr, window_flags);

	if (ImGui::CollapsingHeader("Physics Debug Renderer Options")) {
		ImGui::Indent(INDENT_AMOUNT);
		draw_physics_debug_render_options();
		ImGui::Indent(-INDENT_AMOUNT);
	}

	// Performance logger
	PERFORMANCE_LOGGER_POP();
	PerformanceLoggerGUI::draw();
	PERFORMANCE_LOGGER_PUSH("Total Engine Time");

	ImGui::End();
}

auto DebugGUI::draw_physics_debug_render_options() -> void {
	bool result =
	    dataMan::Instance().getDynamicBoolData("show_physics_debug", true);
	ImGui::Checkbox("show", &result);
	dataMan::Instance().setDynamicBoolData("show_physics_debug", result);
}