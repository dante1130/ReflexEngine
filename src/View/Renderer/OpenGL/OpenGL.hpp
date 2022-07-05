#pragma once

#include <glad/glad.h>
#include <functional>

#include "Objects/Shader.hpp"
#include "Objects/Skybox.hpp"
#include "CommonValues.hpp"
#include "View/Renderer/Renderer.hpp"
#include "Model/LightData.hpp"

// A drawcall represents a drawable object that is rendered to the screen, this
// is done through this function pointer which is passed from the scene to the
// renderer.
using DrawCall = std::function<void(const Shader& shader)>;

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
	 * @brief Set the skybox with given texture paths to faces.
	 *
	 * @param faces
	 */
	void set_skybox(const std::vector<std::string>& faces);

	/**
	 * @brief Adds a directional light to the renderer.
	 *
	 * @param light_data
	 */
	void add_directional_light(const DirectionalLightData& light_data);

	/**
	 * @brief Adds a point light to the renderer.
	 *
	 * @param light_data
	 */
	void add_point_light(const PointLightData& light_data);

	/**
	 * @brief Adds a spot light to the renderer.
	 *
	 * @param light_data
	 */
	void add_spot_light(const SpotLightData& light_data);

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
	 * @brief Enable and render lights.
	 */
	void render_lights();

	/**
	 * @brief The default render pass using the default shader.
	 */
	void render_pass();

	/// A boolean to toggle between wireframe and normal rendering.
	bool is_wireframe_ = false;

	/// The skybox.
	Skybox skybox_ = {};

	/// A vector of directional lights.
	std::vector<DirectionalLight> directional_lights_;

	/// An vector of point lights.
	std::vector<PointLight> point_lights_;

	/// An vector of spot lights.
	std::vector<SpotLight> spot_lights_;

	/// A vector of draw calls.
	std::vector<DrawCall> draw_calls_ = {};

	/// The default shader.
	std::unique_ptr<Shader> shader_ = nullptr;
};
