#include "DebugGUI.hpp"

#include "View/guiManager.hpp"

void DebugGUI::draw() {
	constexpr ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoBackground;

	ImGui::Begin("Debug Menu", nullptr, window_flags);

	ImGui::End();
}