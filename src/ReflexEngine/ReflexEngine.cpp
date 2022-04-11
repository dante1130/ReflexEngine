#include "ReflexEngine.hpp"

#include "Game/TestScene.hpp"

ReflexEngine::ReflexEngine() {
	if (window_.Init() == 1) return;
}

void ReflexEngine::run() {
	auto& engine = ReflexEngine::get_instance();

	engine.renderer_.init();

	engine.scenes_.emplace(std::make_shared<TestScene>());
	engine.scenes_.top()->init();

	float delta_time = 0.0f;
	float prev_time = glfwGetTime();

	while (!engine.window_.IsShouldClose()) {
		float curr_time = glfwGetTime();
		delta_time = curr_time - prev_time;
		prev_time = curr_time;

		glfwPollEvents();

		engine.renderer_.update_camera(engine.window_, delta_time);

		engine.scenes_.top()->add_draw_call();
		engine.renderer_.draw();

		engine.window_.SwapBuffers();
	}
}

ReflexEngine& ReflexEngine::get_instance() {
	static ReflexEngine instance;
	return instance;
}
