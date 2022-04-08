#pragma once

#include <glad/glad.h>
#include <functional>

#include "Window.hpp"
#include "Camera.hpp"
#include "Shader.hpp"
#include "Skybox.hpp"
#include "../Renderer.hpp"

using DrawCall = std::function<void(std::shared_ptr<Shader>)>;

class OpenGL : public Renderer {
public:
	OpenGL() = default;

	void init() override;

	void draw() override;

	void toggle_wireframe() override;

	std::shared_ptr<Shader> get_shader();

	void update_camera(Window& window, float delta_time);

	void add_draw_call(const DrawCall& draw_call);

private:
	bool is_wireframe_ = true;

	Camera camera_ = {};

	Skybox skybox_ = {};

	std::vector<DrawCall> draw_calls_ = {};

	std::shared_ptr<Shader> shader_ = nullptr;
	std::shared_ptr<Shader> directional_shadow_shader_ = nullptr;
	std::shared_ptr<Shader> omni_shadow_shader_ = nullptr;
};
