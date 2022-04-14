#pragma once

#include <glad/glad.h>
#include <functional>

#include "Window.hpp"
#include "Camera.hpp"
#include "Shader.hpp"
#include "Skybox.hpp"
#include "../Renderer.hpp"

// A drawcall represents a drawable object that is rendered to the screen, this
// is done through this function pointer which is passed from the scene to the
// renderer.
using DrawCall = std::function<void(std::shared_ptr<Shader>)>;

/**
 * @brief The OpenGL renderer.
 */
class OpenGL : public Renderer {
public:
	/**
	 * @brief Default constructor.
	 */
	OpenGL() = default;

	/**
	 * @brief Initializes OpenGL, shaders, camera and the skybox.
	 */
	void init() override;

	/**
	 * @brief Draws the scene.
	 */
	void draw() override;

	/**
	 * @brief Toggles between normal and wireframe rendering.
	 */
	void toggle_wireframe() override;

	/**
	 * @brief Getter for the default shader object.
	 *
	 * @return std::shared_ptr<Shader>
	 */
	std::shared_ptr<Shader> get_shader();

	/**
	 * @brief Updates the camera's position and perspective.
	 *
	 * @param window
	 * @param delta_time
	 */
	void update_camera(Window& window, float delta_time);

	/**
	 * @brief Adds a directional light to the renderer.
	 *
	 * @param light
	 */
	void add_directional_light(const DirectionalLight& light);

	/**
	 * @brief Adds a draw call to the renderer.
	 *
	 * @param draw_call
	 */
	void add_draw_call(const DrawCall& draw_call);

private:
	/**
	 * @brief Renders the draw calls using the shader given by parameter.
	 *
	 * @param shader
	 */
	void render_scene(std::shared_ptr<Shader> shader);

	/**
	 * @brief Enable and render lights.
	 */
	void render_lights();

	/**
	 * @brief The default render pass using the default shader.
	 */
	void render_pass();

	/**
	 * @brief The directional shadow pass using the directional shadow shader.
	 *
	 * @param d_light
	 */
	void directional_shadow_pass(const DirectionalLight& d_light);

	/// A boolean to toggle between wireframe and normal rendering.
	bool is_wireframe_ = true;

	/// The camera.
	Camera camera_ = {};

	/// The skybox.
	Skybox skybox_ = {};

	/// A vector of directional lights.
	std::vector<DirectionalLight> directional_lights_;

	/// A vector of draw calls.
	std::vector<DrawCall> draw_calls_ = {};

	/// The default shader.
	std::shared_ptr<Shader> shader_ = nullptr;

	/// The directional shadow shader.
	std::shared_ptr<Shader> directional_shadow_shader_ = nullptr;

	/// The directional shadow map.
	std::shared_ptr<Shader> omni_shadow_shader_ = nullptr;
};