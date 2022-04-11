#include "guiManager.h"

void gui::init(GLFWwindow *window, std::string openglVersion)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(openglVersion.c_str());
}

void gui::mainLoopStart()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void gui::mainLoopEnd()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void gui::shutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void gui::begin(const std::string title)
{
	ImGui::Begin(title.c_str());
}

void gui::begin(const char * title)
{
	ImGui::Begin(title);
}

void gui::end()
{
	ImGui::End();
}

void gui::setWindowPos(int xPos, int yPos, int constraint)
{
	ImGui::SetNextWindowPos(ImVec2(xPos, yPos), constraint);
}

void gui::setWindowSize(int xSize, int ySize, int constraint)
{
	ImGui::SetNextWindowSize(ImVec2(xSize, ySize), constraint);
}

void gui::text(const std::string text)
{
	ImGui::Text(text.c_str());
}

void gui::text(const char * text)
{
	ImGui::Text(text);
}

void gui::checkbox(const std::string name, bool* option)
{
	ImGui::Checkbox(name.c_str(), option);
}

void gui::checkbox(const char * name, bool* option)
{
	ImGui::Checkbox(name, option);
}

void gui::sliderFloat(const std::string name, float* value, float min, float max)
{
	ImGui::SliderFloat(name.c_str(), value, min, max);
}

void gui::sliderFloat(const char * name, float* value, float min, float max)
{
	ImGui::SliderFloat(name, value, min, max);
}

void gui::sliderInt(const std::string name, int* value, int min, int max)
{
	sliderInt(name.c_str(), value, min, max);
}

void gui::sliderInt(const char * name, int* value, int min, int max)
{
	ImGui::SliderInt(name, value, min, max);
}

void gui::colourEdit3(const std::string name, float colour[3])
{
	colourEdit3(name.c_str(), colour);
}

void gui::colourEdit3(const char * name, float colour[3])
{
	ImGui::ColorEdit3(name, colour);
}

void gui::colourEdit4(const std::string name, float colour[4])
{
	colourEdit4(name.c_str(), colour);
}

void gui::colourEdit4(const char * name, float colour[4])
{
	ImGui::ColorEdit4(name, colour);
}

void gui::sliderAngle(const std::string name, float* angle, float min, float max)
{
	sliderAngle(name.c_str(), angle, min, max);
}

void gui::sliderAngle(const char * name, float* angle, float min, float max)
{
	ImGui::SliderAngle(name, angle, min, max);
}

float gui::guiFrameRate()
{
	return ImGui::GetIO().Framerate;
}

bool gui::button(const std::string name)
{
	return button(name.c_str());
}

bool gui::button(const char* name)
{
	return ImGui::Button(name);
}

bool gui::button(const std::string name, float xSize, float ySize)
{
	return button(name.c_str(), xSize, ySize);
}

bool gui::button(const char* name, float xSize, float ySize)
{
	return ImGui::Button(name, ImVec2(xSize, ySize));
}

bool gui::inputText(const std::string name, char* buffer, int size)
{
	return inputText(name.c_str(), buffer, size);
}

bool gui::inputText(const char* name, char* buffer, int size)
{
	return ImGui::InputText(name, buffer, size);
}

bool gui::collapsingHeader(const std::string name)
{
	return collapsingHeader(name.c_str());
}

bool gui::collapsingHeader(const char* name)
{
	return ImGui::CollapsingHeader(name);
}


void gui::plotLines(const std::string name, const float* values, int numOfEntries)
{
	plotLines(name.c_str(), values, numOfEntries);
}

void gui::plotLines(const char* name, const float* values, int numOfEntries)
{
	ImGui::PlotLines(name, values, numOfEntries);
}

void gui::plotLines(const std::string name, const float* values, int numOfEntries, float xWindowSize, float yWindowSize)
{
	plotLines(name.c_str(), values, numOfEntries, xWindowSize, yWindowSize);
}

void gui::plotLines(const char* name, const float* values, int numOfEntries, float xWindowSize, float yWindowSize)
{
	plotLines(name, values, numOfEntries, 0, 300, xWindowSize, yWindowSize);
}

void gui::plotLines(const std::string name, const float* values, int numOfEntries, float minVal, float maxVal, float xWindowSize, float yWindowSize)
{
	plotLines(name.c_str(), values, numOfEntries, minVal, maxVal, xWindowSize, yWindowSize);
}

void gui::plotLines(const char* name, const float* values, int numOfEntries, float minVal, float maxVal, float xWindowSize, float yWindowSize)
{
	ImGui::PlotLines(name, values, numOfEntries, 0, "", minVal, maxVal, ImVec2(xWindowSize, yWindowSize));
}

void gui::progressBar(float percentage)
{
	ImGui::ProgressBar(percentage / 100);
}
