#include "OpenGL.hpp"

#include "Controller/ReflexEngine/ReflexEngine.hpp"
#include "Controller/LuaManager.hpp"

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
	shader_ = std::make_unique<Shader>();
	shader_->CompileFile("shaders/shader.vert", "shaders/shader.frag");

	static const std::vector<std::string> default_skybox = {
	    "textures/skyboxes/default/right.jpg",
	    "textures/skyboxes/default/left.jpg",
	    "textures/skyboxes/default/top.jpg",
	    "textures/skyboxes/default/bottom.jpg",
	    "textures/skyboxes/default/front.jpg",
	    "textures/skyboxes/default/back.jpg"};

	skybox_ = Skybox(default_skybox);

	lua_access();
}

void OpenGL::draw() {
	render_pass();

	directional_lights_.clear();
	point_lights_.clear();
	spot_lights_.clear();
	draw_calls_.clear();
}

void OpenGL::render_scene(const Shader& shader) {
	for (const auto& draw_call : draw_calls_) {
		draw_call(shader);
	}
}

void OpenGL::render_pass() {
	auto& engine = ReflexEngine::get_instance();

	glViewport(0, 0, engine.window_.get_buffer_width(),
	           engine.window_.get_buffer_height());

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 projection = glm::perspective(
	    glm::radians(60.0f), engine.window_.get_ratio(), 0.1f, 1000.0f);

	glm::mat4 view = engine.camera_.calc_view_matrix();

	// Creates projection matrix mode
	glUniformMatrix4fv(shader_->GetProjectionLocation(), 1, GL_FALSE,
	                   glm::value_ptr(projection));

	// Create view matrix mode
	glUniformMatrix4fv(shader_->GetViewLocation(), 1, GL_FALSE,
	                   glm::value_ptr(view));

	skybox_.DrawSkybox(projection, view);

	shader_->UseShader();

	render_lights();

	shader_->Validate();

	render_scene(*shader_);
}

void OpenGL::render_lights() {
	for (const auto& d_light : directional_lights_) {
		shader_->SetDirectionalLight(d_light);
	}

	shader_->SetPointLights(point_lights_.data(), point_lights_.size(), 3, 0);

	shader_->SetSpotLights(spot_lights_.data(), spot_lights_.size(),
	                       3 + point_lights_.size(), point_lights_.size());

	shader_->SetTexture(1);
	shader_->SetDirectionalShadowMap(2);
	shader_->set_detail_map(3);
}

void OpenGL::toggle_wireframe() {
	is_wireframe_ = !is_wireframe_;

	if (is_wireframe_)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void OpenGL::set_skybox(const std::vector<std::string>& faces) {
	skybox_ = Skybox(faces);
}

void OpenGL::add_directional_light(const DirectionalLightData& light) {
	directional_lights_.emplace_back(
	    DirectionalLight(light.color, light.ambient_intensity, light.direction,
	                     light.diffuse_intensity));
}

void OpenGL::add_point_light(const PointLightData& light_data) {
	if (point_lights_.size() < MAX_POINT_LIGHTS) {
		point_lights_.emplace_back(PointLight(
		    light_data.color, light_data.ambient_intensity,
		    light_data.diffuse_intensity, light_data.position,
		    light_data.constant, light_data.linear, light_data.quadratic));
	}
}

void OpenGL::add_spot_light(const SpotLightData& light_data) {
	if (spot_lights_.size() < MAX_SPOT_LIGHTS) {
		spot_lights_.emplace_back(SpotLight(
		    light_data.color, light_data.ambient_intensity,
		    light_data.diffuse_intensity, light_data.position,
		    light_data.direction, light_data.constant, light_data.linear,
		    light_data.quadratic, light_data.edge));
	}
}

void OpenGL::add_draw_call(const DrawCall& draw_call) {
	draw_calls_.emplace_back(draw_call);
}
