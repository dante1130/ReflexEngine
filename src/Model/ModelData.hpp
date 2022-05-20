#pragma once

#include <string>
#include <memory>
#include "View/Renderer/OpenGL/Objects/Shader.hpp"
#include "View/Renderer/OpenGL/Objects/Md2.hpp"

class ModelData {
public:
	ModelData(const std::string& model_name, const std::string& texture_name,
	          bool is_animated, bool is_loop_);

	void render(float delta_time);

	void set_fps(float fps);
	void set_loop(bool loop);
	void set_animation(md2::animation_type animation_type);
	void animate(float delta_time);

	bool get_is_animated() const;
	bool get_is_running() const;

private:
	void render_animated(float delta_time);
	void render_model();

	std::string model_name_;
	std::string texture_name_;

	md2::animstate_t animstate_;

	bool is_animation_done = false;
	bool is_loop_ = false;
	bool is_animated_ = false;
};
