#include "DebugLogger.hpp"

#include "Controller/ReflexEngine/EngineTime.hpp"
#include "Controller/LuaManager.hpp"

ImGuiTextBuffer DebugLogger::buffer_;
ImGuiTextFilter DebugLogger::filter_;
ImVector<int> DebugLogger::line_offsets_;
ImVector<ImVec4> DebugLogger::colors_;
bool DebugLogger::auto_scroll_ = true;

void DebugLogger::lua_access() {
	auto& lua = LuaManager::get_instance().get_state();

	auto debug_logger = lua.create_named_table("DebugLogger");

	debug_logger.set_function("log", &DebugLogger::log);
	debug_logger.set_function("log_color", &DebugLogger::log_color);
	debug_logger.set_function("clear", &DebugLogger::clear);
}

void DebugLogger::clear() {
	buffer_.clear();
	line_offsets_.clear();
	line_offsets_.push_back(0);
	colors_.clear();
}

void DebugLogger::log(const std::string& category, const std::string& message) {
	log_color(category, message, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
}

void DebugLogger::log_color(const std::string& category,
                            const std::string& message, const ImVec4& color) {
	int old_size = buffer_.size();

	buffer_.appendf("[%.2f] [%s] %s\n", EngineTime::get_current_time(),
	                category.c_str(), message.c_str());

	for (int new_size = buffer_.size(); old_size < new_size; ++old_size) {
		if (buffer_[old_size] == '\n') {
			line_offsets_.push_back(old_size + 1);
		}
	}

	colors_.push_back(color);
}

void DebugLogger::draw() {
	ImGui::Begin("Debug Log", nullptr, ImGuiWindowFlags_NoBackground);

	ImGui::Checkbox("Auto-scroll", &auto_scroll_);
	ImGui::SameLine();
	bool clear = ImGui::Button("Clear");
	ImGui::SameLine();
	bool copy = ImGui::Button("Copy");
	ImGui::SameLine();
	filter_.Draw("Filter", -100.0f);

	ImGui::Separator();
	ImGui::BeginChild("scrolling", ImVec2(0, 0), false,
	                  ImGuiWindowFlags_HorizontalScrollbar);

	if (clear) DebugLogger::clear();
	if (copy) ImGui::LogToClipboard();

	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
	const char* buf = buffer_.begin();
	const char* buf_end = buffer_.end();

	if (filter_.IsActive()) {
		for (int line_no = 0; line_no < line_offsets_.Size; ++line_no) {
			const char* line_start = buf + line_offsets_[line_no];
			const char* line_end = (line_no + 1 < line_offsets_.Size)
			                           ? (buf + line_offsets_[line_no + 1] - 1)
			                           : buf_end;
			if (filter_.PassFilter(line_start, line_end)) {
				const ImVec4& color = (line_no < colors_.Size)
				                          ? colors_[line_no]
				                          : ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
				ImGui::PushStyleColor(ImGuiCol_Text, color);
				ImGui::TextUnformatted(line_start, line_end);
				ImGui::PopStyleColor();
			}
		}
	} else {
		ImGuiListClipper clipper;
		clipper.Begin(line_offsets_.Size);
		while (clipper.Step()) {
			for (int line_no = clipper.DisplayStart;
			     line_no < clipper.DisplayEnd; ++line_no) {
				const char* line_start = buf + line_offsets_[line_no];
				const char* line_end =
				    (line_no + 1 < line_offsets_.Size)
				        ? (buf + line_offsets_[line_no + 1] - 1)
				        : buf_end;

				const ImVec4& color = (line_no < colors_.Size)
				                          ? colors_[line_no]
				                          : ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
				ImGui::PushStyleColor(ImGuiCol_Text, color);
				ImGui::TextUnformatted(line_start, line_end);
				ImGui::PopStyleColor();
			}
		}
		clipper.End();
	}
	ImGui::PopStyleVar();

	if (auto_scroll_ && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
		ImGui::SetScrollHereY(1.0f);

	ImGui::EndChild();

	ImGui::End();
}