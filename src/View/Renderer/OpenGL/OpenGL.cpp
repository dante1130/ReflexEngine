#include "OpenGL.hpp"

#include "Controller/ReflexEngine/ReflexEngine.hpp"

void OpenGL::init() {
	auto& engine = ReflexEngine::get_instance();

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	glViewport(0, 0, engine.window_.GetBufferWidth(),
	           engine.window_.GetBufferHeight());

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	shader_ = std::make_shared<Shader>();
	shader_->CompileFile("shaders/shader.vert", "shaders/shader.frag");

	directional_shadow_shader_ = std::make_shared<Shader>();
	directional_shadow_shader_->CompileFile(
	    "shaders/directional_shadow_map.vert",
	    "shaders/directional_shadow_map.frag");

	omni_shadow_shader_ = std::make_shared<Shader>();
	omni_shadow_shader_->CompileFile("shaders/omni_shadow_map.vert",
	                                 "shaders/omni_shadow_map.geom",
	                                 "shaders/omni_shadow_map.frag");
}

void OpenGL::draw() {
	render_pass();

	directional_lights_.clear();
	point_lights_.clear();
	spot_lights_.clear();
	draw_calls_.clear();
}

float m_last_time = 0;
void OpenGL::render_scene(std::shared_ptr<Shader> shader) {
	for (const auto& draw_call : draw_calls_) {
		draw_call(shader);
	}
}

void OpenGL::render_pass() {
	auto& engine = ReflexEngine::get_instance();

	GLint width = engine.window_.GetBufferWidth();
	GLint height = engine.window_.GetBufferHeight();

	glViewport(0, 0, width, height);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 projection = glm::perspective(
	    glm::radians(60.0f),
	    static_cast<float>(width) / static_cast<float>(height), 0.1f, 1000.0f);

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

	render_scene(shader_);
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

void OpenGL::directional_shadow_pass(const DirectionalLight& d_light) {
	directional_shadow_shader_->UseShader();

	glViewport(0, 0, d_light.GetShadowMap()->GetShadowWidth(),
	           d_light.GetShadowMap()->GetShadowHeight());

	d_light.GetShadowMap()->Write();
	glClear(GL_DEPTH_BUFFER_BIT);

	directional_shadow_shader_->SetDirectionalLightTransform(
	    d_light.CalculateLightTransform());

	directional_shadow_shader_->Validate();

	render_scene(directional_shadow_shader_);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGL::toggle_wireframe() {
	is_wireframe_ = !is_wireframe_;

	if (is_wireframe_)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

std::shared_ptr<Shader> OpenGL::get_shader() { return shader_; }

void OpenGL::set_skybox(const std::vector<std::string>& faces) {
	skybox_ = Skybox(faces);
}

void OpenGL::add_directional_light(const DirectionalLightData& light) {
	directional_lights_.emplace_back(
	    DirectionalLight(2048, 2048, light.color, light.ambient_intensity,
	                     light.direction, light.diffuse_intensity));
}

void OpenGL::add_point_light(const PointLightData& light_data) {
	if (point_lights_.size() < MAX_POINT_LIGHTS) {
		point_lights_.emplace_back(PointLight(
		    2048, 2048, 0.01f, 100.0f, light_data.color,
		    light_data.ambient_intensity, light_data.diffuse_intensity,
		    light_data.position, light_data.constant, light_data.linear,
		    light_data.quadratic));
	}
}

void OpenGL::add_spot_light(const SpotLight& light) {
	if (spot_lights_.size() < MAX_SPOT_LIGHTS) spot_lights_.push_back(light);
}

void OpenGL::add_draw_call(const DrawCall& draw_call) {
	draw_calls_.push_back(draw_call);
}
