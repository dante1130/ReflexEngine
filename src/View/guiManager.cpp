#include "guiManager.hpp"

#include "Controller/ResourceManager/ResourceManager.hpp"

void gui::init(GLFWwindow* window, std::string openglVersion) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(openglVersion.c_str());
}

void gui::mainLoopStart() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void gui::mainLoopEnd() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void gui::shutdown() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
//
void gui::begin(const std::string title) { ImGui::Begin(title.c_str()); }

void gui::end() { ImGui::End(); }

void gui::setWindowPos(int xPos, int yPos, int constraint) {
	ImGui::SetNextWindowPos(ImVec2(xPos, yPos), constraint);
}

void gui::setWindowSize(int xSize, int ySize, int constraint) {
	ImGui::SetNextWindowSize(ImVec2(xSize, ySize), constraint);
}

void gui::text(const std::string text) { ImGui::Text(text.c_str()); }

void gui::checkbox(const std::string name, bool* option) {
	ImGui::Checkbox(name.c_str(), option);
}

bool gui::luaCheckBox(const std::string name, bool state) {
	static std::map<std::string, bool> checkBoxes;
	if (checkBoxes.find(name) == checkBoxes.end()) {
		checkBoxes.insert(std::pair<std::string, bool>(name, state));
	}

	ImGui::Checkbox(name.c_str(), &checkBoxes[name]);
	return checkBoxes[name];
}

void gui::sliderFloat(const std::string name, float* value, float min,
                      float max) {
	ImGui::SliderFloat(name.c_str(), value, min, max);
}

void gui::sliderInt(const std::string name, int* value, int min, int max) {
	ImGui::SliderInt(name.c_str(), value, min, max);
}

void gui::colourEdit3(const std::string name, float colour[3]) {
	ImGui::ColorEdit3(name.c_str(), colour);
}

void gui::colourEdit4(const std::string name, float colour[4]) {
	ImGui::ColorEdit4(name.c_str(), colour);
}

void gui::lua_image(const std::string& texture_name) {
	auto& texture_manager =
	    ResourceManager::get_instance().get_texture_manager();

	const auto& texture = texture_manager.get_texture(texture_name);

	gui::image(texture.get_texture_id(), texture.get_width(),
	           texture.get_height());
}

void gui::image(uint32_t textureID, int width, int height) {
	ImGui::Image((void*)(intptr_t)textureID, ImVec2(width, height));
}

void gui::sliderAngle(const std::string name, float* angle, float min,
                      float max) {
	ImGui::SliderAngle(name.c_str(), angle, min, max);
}

float gui::guiFrameRate() { return ImGui::GetIO().Framerate; }

bool gui::button(const std::string name, int xSize, int ySize) {
	return ImGui::Button(name.c_str(), ImVec2(xSize, ySize));
}

std::string gui::luaInputText(const std::string name) {
	char newBuffer[30] =
	    {};  // Could make this static to fix it but its such a crappy way to do
	         // it (as you can only have one InputText really)
	bool ret;
	ret = ImGui::InputText(name.c_str(), newBuffer, 30);
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

bool gui::inputText(const std::string name, char* buffer, int size) {
	return ImGui::InputText(name.c_str(), buffer, size);
}

bool gui::collapsingHeader(const std::string name) {
	return ImGui::CollapsingHeader(name.c_str());
}

void gui::plotLines(const std::string name, const float* values,
                    int numOfEntries) {
	ImGui::PlotLines(name.c_str(), values, numOfEntries);
}

void gui::plotLines(const std::string name, const float* values,
                    int numOfEntries, float xWindowSize, float yWindowSize) {
	plotLines(name, values, numOfEntries, xWindowSize, yWindowSize);
}

void gui::plotLines(const std::string name, const float* values,
                    int numOfEntries, float minVal, float maxVal,
                    float xWindowSize, float yWindowSize) {
	ImGui::PlotLines(name.c_str(), values, numOfEntries, 0, "", minVal, maxVal,
	                 ImVec2(xWindowSize, yWindowSize));
}

void gui::progressBar(float percentage) {
	ImGui::ProgressBar(percentage / 100);
}
