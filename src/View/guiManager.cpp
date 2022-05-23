#include "guiManager.hpp"

#include "Controller/ResourceManager/ResourceManager.hpp"
#include "Controller/LuaManager.hpp"

void GuiManager::init(GLFWwindow* window, const std::string& openglVersion) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(openglVersion.c_str());

	lua_access();
}

void GuiManager::lua_access() {
	auto& lua = LuaManager::get_instance().get_state();

	lua.set_function("gui_begin", GuiManager::begin);
	lua.set_function("gui_end", GuiManager::end);
	lua.set_function("gui_text", GuiManager::text);
	lua.set_function("gui_setWindowPos", GuiManager::setWindowPos);
	lua.set_function("gui_setWindowSize", GuiManager::setWindowSize);
	lua.set_function("gui_luaCheckbox", GuiManager::luaCheckBox);
	lua.set_function("gui_sliderFloat", GuiManager::sliderFloat);
	lua.set_function("gui_sliderInt", GuiManager::sliderInt);
	lua.set_function("gui_sliderAngle", GuiManager::sliderAngle);
	lua.set_function("gui_colourEdit3", GuiManager::colourEdit3);
	lua.set_function("gui_colourEdit4", GuiManager::colourEdit4);
	lua.set_function("gui_luaInputText", GuiManager::luaInputText);
	lua.set_function("gui_collapsingHeader", GuiManager::collapsingHeader);
	lua.set_function("gui_progressBar", GuiManager::progressBar);
	lua.set_function("gui_guiFrameRate", GuiManager::guiFrameRate);
	lua.set_function("gui_button", GuiManager::button);
	lua.set_function("gui_image", GuiManager::lua_image);
	//  lua.set_function("gui_plotLines", gui::plotLines);
}

void GuiManager::mainLoopStart() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void GuiManager::mainLoopEnd() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GuiManager::shutdown() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void GuiManager::begin(const std::string& title) {
	ImGui::Begin(title.c_str());
}

void GuiManager::end() { ImGui::End(); }

void GuiManager::setWindowPos(int xPos, int yPos, int constraint) {
	ImGui::SetNextWindowPos(ImVec2(xPos, yPos), constraint);
}

void GuiManager::setWindowSize(int xSize, int ySize, int constraint) {
	ImGui::SetNextWindowSize(ImVec2(xSize, ySize), constraint);
}

void GuiManager::text(const std::string& text) { ImGui::Text(text.c_str()); }

void GuiManager::checkbox(const std::string& name, bool* option) {
	ImGui::Checkbox(name.c_str(), option);
}

bool GuiManager::luaCheckBox(const std::string& name, bool state) {
	static std::map<std::string, bool> checkBoxes;
	if (checkBoxes.find(name) == checkBoxes.end()) {
		checkBoxes.insert(std::pair<std::string, bool>(name, state));
	}

	ImGui::Checkbox(name.c_str(), &checkBoxes[name]);
	return checkBoxes[name];
}

void GuiManager::sliderFloat(const std::string& name, float* value, float min,
                             float max) {
	ImGui::SliderFloat(name.c_str(), value, min, max);
}

void GuiManager::sliderInt(const std::string& name, int* value, int min,
                           int max) {
	ImGui::SliderInt(name.c_str(), value, min, max);
}

void GuiManager::colourEdit3(const std::string& name, float colour[3]) {
	ImGui::ColorEdit3(name.c_str(), colour);
}

void GuiManager::colourEdit4(const std::string& name, float colour[4]) {
	ImGui::ColorEdit4(name.c_str(), colour);
}

void GuiManager::lua_image(const std::string& texture_name) {
	auto& texture_manager =
	    ResourceManager::get_instance().get_texture_manager();

	const auto& texture = texture_manager.get_texture(texture_name);

	GuiManager::image(texture.get_texture_id(), texture.get_width(),
	                  texture.get_height());
}

void GuiManager::image(uint32_t texture_id, int width, int height) {
	ImGui::Image((void*)(intptr_t)texture_id, ImVec2(width, height));
}

void GuiManager::sliderAngle(const std::string& name, float* angle, float min,
                             float max) {
	ImGui::SliderAngle(name.c_str(), angle, min, max);
}

float GuiManager::guiFrameRate() { return ImGui::GetIO().Framerate; }

bool GuiManager::button(const std::string& name, int xSize, int ySize) {
	return ImGui::Button(name.c_str(), ImVec2(xSize, ySize));
}

std::string GuiManager::luaInputText(const std::string& name) {
	char newBuffer[30] =
	    {};  // Could make this static to fix it but its such a crappy way to do
	         // it (as you can only have one InputText really)
	ImGui::InputText(name.c_str(), newBuffer, 30);
	/*
	if (ret) {
	    std::string savedBuffer(newBuffer);
	    return savedBuffer;
	} else {
	    return newBuffer;
	}
	*/
	return newBuffer;
}

bool GuiManager::inputText(const std::string& name, char* buffer, int size) {
	return ImGui::InputText(name.c_str(), buffer, size);
}

bool GuiManager::collapsingHeader(const std::string& name) {
	return ImGui::CollapsingHeader(name.c_str());
}

void GuiManager::plotLines(const std::string& name, const float* values,
                           int numOfEntries) {
	ImGui::PlotLines(name.c_str(), values, numOfEntries);
}

void GuiManager::plotLines(const std::string& name, const float* values,
                           int numOfEntries, float xWindowSize,
                           float yWindowSize) {
	plotLines(name, values, numOfEntries, xWindowSize, yWindowSize);
}

void GuiManager::plotLines(const std::string& name, const float* values,
                           int numOfEntries, float minVal, float maxVal,
                           float xWindowSize, float yWindowSize) {
	ImGui::PlotLines(name.c_str(), values, numOfEntries, 0, "", minVal, maxVal,
	                 ImVec2(xWindowSize, yWindowSize));
}

void GuiManager::progressBar(float percentage) {
	ImGui::ProgressBar(percentage / 100);
}
