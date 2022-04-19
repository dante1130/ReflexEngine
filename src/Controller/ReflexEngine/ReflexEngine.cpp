#include "ReflexEngine.hpp"

#include "Game/TestScene.hpp"
#include "guiManager.hpp"
//#include "NetworkManager.hpp"
#include "Controller/GenericFunctions.h"
#include "Controller/Input/InputManager.hpp"

ReflexEngine::ReflexEngine() {
	if (window_.Init() == 1) return;
}

void ReflexEngine::run() {
	auto& engine = ReflexEngine::get_instance();
	ResourceManager::get_instance();

	engine.camera_ = Camera(glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
	                        -90.0f, 0.0f, 5.0f, 0.2f);

	engine.renderer_.init();

	gui::init(ReflexEngine::get_instance().window_.get_window(),
	          "#version 410");
	guiLuaAccess::exposeGui();

	engine.scenes_.emplace(std::make_shared<TestScene>());
	engine.scenes_.top()->init();

	float delta_time = 0.0f;
	float prev_time = glfwGetTime();

	auto& input_manager = InputManager::get_instance();

	while (!engine.window_.IsShouldClose()) {
		float curr_time = glfwGetTime();
		delta_time = curr_time - prev_time;
		prev_time = curr_time;

		glfwPollEvents();
		input_manager.read_keys(engine.window_.get_window());

		gui::mainLoopStart();

		if (GenericFunctions::getIfPaused()) delta_time = 0;

		if (GenericFunctions::getIfLoad()) {
			engine.scenes_.top()->loadSavedGameObjects();
		} else if (GenericFunctions::getIfSave()) {
			engine.scenes_.top()->saveGameObjects();
		} else {
			engine.scenes_.top()->update(delta_time);
			engine.scenes_.top()->add_draw_call();
			engine.renderer_.draw();

			if (GenericFunctions::getIfPaused() == false) {
				engine.scenes_.top()->mouse_controls(
				    engine.window_.GetXOffset(), engine.window_.GetYOffset());
			}
			engine.scenes_.top()->key_controls(delta_time);
		}

		gui::mainLoopEnd();

		engine.window_.SwapBuffers();
	}
	gui::shutdown();
}

ReflexEngine& ReflexEngine::get_instance() {
	static ReflexEngine instance;
	return instance;
}
