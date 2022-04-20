#include "OpenGL.hpp"

#include "Controller/ReflexEngine/ReflexEngine.hpp"
#include "BttController.hpp"

BttController bttControl;


void OpenGL::init() {
	auto& engine = ReflexEngine::get_instance();

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	glViewport(0, 0, engine.window_.GetBufferWidth(),
	           engine.window_.GetBufferHeight());

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

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

	camera_ = Camera(glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f,
	                 5.0f, 0.2f);

	std::vector<std::string> skyboxFaces;
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	skyboxFaces.push_back(
	    "textures/skyboxes/cupertin-lake/cupertin-lake_rt.tga");
	skyboxFaces.push_back(
	    "textures/skyboxes/cupertin-lake/cupertin-lake_lf.tga");
	skyboxFaces.push_back(
	    "textures/skyboxes/cupertin-lake/cupertin-lake_up.tga");
	skyboxFaces.push_back(
	    "textures/skyboxes/cupertin-lake/cupertin-lake_dn.tga");
	skyboxFaces.push_back(
	    "textures/skyboxes/cupertin-lake/cupertin-lake_bk.tga");
	skyboxFaces.push_back(
	    "textures/skyboxes/cupertin-lake/cupertin-lake_ft.tga");

	skybox_ = Skybox(skyboxFaces);

	bttControl.gen_faultformation(64, 161, 0, 255, 0.5);
	bttControl.set_scale(glm::vec3(1.0f, 0.1f, 1.0f));

	//Tiles: 20, Amount of vertices per tile: 9, n: 3
	bttControl.CreateTerrain(20, 9, 3);
}

void OpenGL::draw() {
	// Not working yet.
	// for (const auto& d_light : directional_lights_) {
	// 	directional_shadow_pass(d_light);
	// }

	render_pass();

	directional_lights_.clear();
	draw_calls_.clear();
}

void OpenGL::render_scene(std::shared_ptr<Shader> shader) {
	for (const auto& draw_call : draw_calls_) {
		draw_call(shader);
	}
	bttControl.Update(camera_.GetCamPosition());
	bttControl.render(ReflexEngine::get_instance().renderer_.get_shader());
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
	    static_cast<float>(width) / static_cast<float>(height), 0.1f, 10000.0f);

	glm::mat4 view = camera_.CalculateViewMatrix();

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
		shader_->SetDirectionalLightTransform(
		    d_light.CalculateLightTransform());
		d_light.GetShadowMap()->Read(GL_TEXTURE2);
	}

	shader_->SetTexture(1);
	shader_->SetDirectionalShadowMap(2);
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

void OpenGL::add_directional_light(const DirectionalLight& light) {
	directional_lights_.push_back(light);
}

void OpenGL::add_draw_call(const DrawCall& draw_call) {
	draw_calls_.push_back(draw_call);
}

void OpenGL::update_camera(Window& window, float delta_time) {
	camera_.KeyControl(window.GetKeys(), delta_time);
	camera_.MouseControl(window.GetXOffset(), window.GetYOffset());
}
