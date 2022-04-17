#include "ReflexEngine.hpp"

#include "Game/TestScene.hpp"
#include "guiManager.hpp"

ReflexEngine::ReflexEngine() {
	if (window_.Init() == 1) return;
}

void ReflexEngine::run() {
	auto& engine = ReflexEngine::get_instance();

	engine.camera_ = Camera(glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
	                        -90.0f, 0.0f, 5.0f, 0.2f);

	engine.renderer_.init();

	engine.scenes_.emplace(std::make_shared<TestScene>());
	engine.scenes_.top()->init();

	float delta_time = 0.0f;
	float prev_time = glfwGetTime();

	glfwSetInputMode(ReflexEngine::get_instance().window_.getWindow(),
	                 GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	while (!engine.window_.IsShouldClose()) {
		float curr_time = glfwGetTime();
		delta_time = curr_time - prev_time;
		prev_time = curr_time;

		glfwPollEvents();

		engine.update_camera(delta_time);

		gui::mainLoopStart();

		engine.scenes_.top()->update(delta_time);
		engine.scenes_.top()->add_draw_call();
		engine.renderer_.draw();

		gui::mainLoopEnd();

		engine.window_.SwapBuffers();
	}
	gui::shutdown();
}

void ReflexEngine::update_camera(float delta_time) {
	camera_.KeyControl(window_.GetKeys(), delta_time);
	camera_.MouseControl(window_.GetXOffset(), window_.GetYOffset());
}

ReflexEngine& ReflexEngine::get_instance() {
	static ReflexEngine instance;
	return instance;
}
