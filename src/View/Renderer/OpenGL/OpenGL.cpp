#include "OpenGL.hpp"

#include "Controller/ReflexEngine/ReflexEngine.hpp"
#include "Controller/LuaManager.hpp"
#include "Controller/ResourceManager/ResourceManager.hpp"

void OpenGL::lua_access() {
	auto& lua = LuaManager::get_instance().get_state();

	auto renderer = lua.create_named_table("Renderer");

	renderer.set_function("toggle_wireframe", &OpenGL::toggle_wireframe, this);
}

void OpenGL::init() {
	auto& engine = ReflexEngine::get_instance();

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	glViewport(0, 0, engine.window_.get_buffer_width(),
	           engine.window_.get_buffer_height());
	//
	// Enable depth testing.
	glEnable(GL_DEPTH_TEST);
	// Enable face culling.
	glEnable(GL_CULL_FACE);
	// Enable blending. (For transparency)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Default shader.
	shader_.CompileFile("shaders/shader.vert", "shaders/shader.frag");

	// Directional shadow shader.
	directional_shadow_shader_.CompileFile(
	    "shaders/directional_shadow_map.vert",
	    "shaders/directional_shadow_map.frag");

	// Omni-directional shadow shader.
	omni_shadow_shader_.CompileFile("shaders/omni_shadow_map.vert",
	                                "shaders/omni_shadow_map.geom",
	                                "shaders/omni_shadow_map.frag");

	lua_access();
}

void OpenGL::draw() {
	auto& light_manager = ResourceManager::get_instance().get_light_manager();

	const auto& directional_light = light_manager.get_directional_light();

	std::vector<PointLight> point_lights;
	std::vector<SpotLight> spot_lights;

	point_lights.reserve(light_manager.get_point_lights().size());
	spot_lights.reserve(light_manager.get_spot_lights().size());

	std::copy_if(light_manager.get_point_lights().begin(),
	             light_manager.get_point_lights().end(),
	             std::back_inserter(point_lights),
	             [](const PointLight& light) { return light.is_active(); });

	std::copy_if(light_manager.get_spot_lights().begin(),
	             light_manager.get_spot_lights().end(),
	             std::back_inserter(spot_lights),
	             [](const SpotLight& light) { return light.is_active(); });

	render_pass(directional_light, point_lights, spot_lights);
	directional_shadow_pass(directional_light);
	render_pass(directional_light, point_lights, spot_lights);

	draw_calls_.clear();
}

void OpenGL::render_scene(const Shader& shader) {
	for (const auto& draw_call : draw_calls_) {
		draw_call(shader);
	}
}

void OpenGL::render_pass(const DirectionalLight& d_light,
                         const PointLights& p_lights,
                         const SpotLights& s_lights) {
	auto& engine = ReflexEngine::get_instance();

	glViewport(0, 0, engine.window_.get_buffer_width(),
	           engine.window_.get_buffer_height());

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 projection = glm::perspective(
	    glm::radians(60.0f), engine.window_.get_ratio(), 0.1f, 1000.0f);

	glm::mat4 view = engine.camera_.calc_view_matrix();

	// Creates projection matrix mode
	glUniformMatrix4fv(shader_.GetProjectionLocation(), 1, GL_FALSE,
	                   glm::value_ptr(projection));

	// Create view matrix mode
	glUniformMatrix4fv(shader_.GetViewLocation(), 1, GL_FALSE,
	                   glm::value_ptr(view));

	// Set the eye position.
	glUniform3fv(shader_.GetEyePositionLocation(), 1,
	             glm::value_ptr(engine.camera_.get_position()));

	render_skybox(projection, view);

	shader_.UseShader();

	render_lights(d_light, p_lights, s_lights);

	shader_.Validate();

	render_scene(shader_);
}

void OpenGL::directional_shadow_pass(const DirectionalLight& d_light) {
	d_light.get_shadow_map().write();

	glViewport(0, 0, d_light.get_shadow_map().get_shadow_width(),
	           d_light.get_shadow_map().get_shadow_height());

	glClear(GL_DEPTH_BUFFER_BIT);

	directional_shadow_shader_.UseShader();

	directional_shadow_shader_.SetDirectionalLightTransform(
	    d_light.calculate_light_transform());

	directional_shadow_shader_.Validate();

	render_scene(directional_shadow_shader_);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGL::omnidirectional_shadow_pass(const PointLights& p_lights,
                                         const SpotLights& s_lights) {}

void OpenGL::render_skybox(const glm::mat4& projection, const glm::mat4& view) {
	auto& skybox_manager = ResourceManager::get_instance().get_skybox_manager();

	skybox_manager.get_skybox().DrawSkybox(projection, view);
}

void OpenGL::render_lights(const DirectionalLight& d_light,
                           const PointLights& p_lights,
                           const SpotLights& s_lights) {
	shader_.SetDirectionalLight(d_light);
	shader_.SetDirectionalLightTransform(d_light.calculate_light_transform());

	shader_.SetPointLights(p_lights.data(), p_lights.size(), 0, 0);
	shader_.SetSpotLights(s_lights.data(), s_lights.size(), 0, 0);

	d_light.get_shadow_map().read(GL_TEXTURE2);

	shader_.SetTexture(1);
	shader_.SetDirectionalShadowMap(2);
	shader_.set_detail_map(3);
}

void OpenGL::toggle_wireframe() {
	is_wireframe_ = !is_wireframe_;

	if (is_wireframe_)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void OpenGL::add_draw_call(const DrawCall& draw_call) {
	draw_calls_.emplace_back(draw_call);
}