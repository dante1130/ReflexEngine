#pragma once

#include <functional>
#include <vector>

#include <glad/glad.h>

#include "Objects/Shader.hpp"
#include "View/Renderer/Renderer.hpp"

// A drawcall represents a drawable object that is rendered to the screen, this
// is done through this function pointer which is passed from the scene to the
// renderer.
using DrawCall = std::function<void(const Shader& shader)>;

using PointLights = std::vector<PointLight>;

using SpotLights = std::vector<SpotLight>;

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
	 * @brief Expose the OpenGL renderer to the scene.
	 */
	void lua_access();

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
	void render_scene(const Shader& shader);

	/**
	 * @brief Renders the skybox.
	 */
	void render_skybox(const glm::mat4& projection, const glm::mat4& view);

	/**
	 * @brief Enable and render lights.
	 */
	void render_lights(const DirectionalLight& d_light,
	                   const PointLights& p_lights, const SpotLights& s_lights);

	/**
	 * @brief The default render pass using the default shader.
	 */
	void render_pass(const DirectionalLight& d_light,
	                 const PointLights& p_lights, const SpotLights& s_lights);

	/**
	 * @brief The directional shadow map pass.
	 */
	void directional_shadow_pass(const DirectionalLight& d_light);

	/**
	 * @brief The omnidirectional shadow map pass.
	 */
	void omnidirectional_shadow_pass(const PointLights& p_lights,
	                                 const SpotLights& s_lights);

	/// A boolean to toggle between wireframe and normal rendering.
	bool is_wireframe_ = false;

	/// A vector of draw calls.
	std::vector<DrawCall> draw_calls_ = {};

	/// The default shader.
	Shader shader_ = {};

	/// The directional shadow shader.
	Shader directional_shadow_shader_ = {};

	/// The omnidirectional shadow shader.
	Shader omni_shadow_shader_ = {};
};
