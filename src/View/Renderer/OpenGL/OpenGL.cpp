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
	auto& light_manager = ResourceManager::get_instance().get_light_manager();

	shader_->SetDirectionalLight(light_manager.get_directional_light());

	std::vector<PointLight> point_lights;
	std::vector<SpotLight> spot_lights;

	std::copy_if(light_manager.get_point_lights().begin(),
	             light_manager.get_point_lights().end(),
	             std::back_inserter(point_lights),
	             [](const PointLight& light) { return light.is_active(); });

	std::copy_if(light_manager.get_spot_lights().begin(),
	             light_manager.get_spot_lights().end(),
	             std::back_inserter(spot_lights),
	             [](const SpotLight& light) { return light.is_active(); });

	shader_->SetPointLights(point_lights.data(), point_lights.size(), 0, 0);

	shader_->SetSpotLights(spot_lights.data(), spot_lights.size(), 0, 0);

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

void OpenGL::add_draw_call(const DrawCall& draw_call) {
	draw_calls_.emplace_back(draw_call);
}
