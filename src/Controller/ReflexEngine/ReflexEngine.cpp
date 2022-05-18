#include "ReflexEngine.hpp"

#include "Game/TestScene.hpp"
#include "View/guiManager.hpp"
#include "NetworkManager.hpp"
#include "Controller/GenericFunctions.h"
#include "Controller/Input/InputManager.hpp"
#include "Controller/Audio/Audio.hpp"
#include "Controller/Physics/Physics.hpp"

ReflexEngine::ReflexEngine() {
	if (window_.Init() == 1) return;
}

void ReflexEngine::run() {
	auto& engine = ReflexEngine::get_instance();

	GenericFunctions::lua_access();
	InputManager::get_instance().load_lua_bindings("scripts/_Controls.lua");
	ResourceManager::get_instance();
	Audio::get_instance();
	Physics::createWorld();

	engine.camera_ = Camera(glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
	                        -90.0f, 0.0f, 5.0f, 0.2f);

	engine.renderer_.init();
	gui::init(engine.window_.get_window(), "#version 410");
	guiLuaAccess::exposeGui();

	engine.scenes_.emplace(std::make_shared<TestScene>());
	engine.scenes_.top()->init();

	auto& input_manager = InputManager::get_instance();

	glfwSetInputMode(engine.window_.get_window(), GLFW_CURSOR,
	                 GLFW_CURSOR_NORMAL);

	while (!engine.window_.IsShouldClose()) {
		EngineTime::update_delta_time(glfwGetTime());

		glfwPollEvents();
		input_manager.read_keys(engine.window_.get_window());

		gui::mainLoopStart();

		if (!GenericFunctions::getNetworkMenuActive()) {
			engine.scenes_.top()->key_controls(engine.delta_time_);
		}

		if (EngineTime::is_paused()) {
			EngineTime::force_delta_time(0);
		} else {
			Physics::updateWorld(EngineTime::get_delta_time());
			engine.scenes_.top()->mouse_controls(engine.window_.GetXOffset(),
			                                     engine.window_.GetYOffset());
		}

		if (GenericFunctions::getIfLoad())
			engine.scenes_.top()->loadSavedGameObjects();
		else if (GenericFunctions::getIfSave())
			engine.scenes_.top()->saveGameObjects();
		else {
			if (EngineTime::get_fixed_delta_time() >= time_step) {
				engine.scenes_.top()->fixed_update(
				    EngineTime::get_fixed_delta_time());
				EngineTime::reset_fixed_delta_time();
			}

			engine.scenes_.top()->update(EngineTime::get_delta_time());
			engine.scenes_.top()->add_draw_call();
			engine.renderer_.draw();
		}

		gui::mainLoopEnd();

		engine.window_.SwapBuffers();
	}
	Physics::destroyWorld();
	gui::shutdown();
}

void ReflexEngine::update_delta_time() {
	float curr_time = glfwGetTime();
	delta_time_ = curr_time - prev_time_;
	fixed_delta_time_ += delta_time_;
	prev_time_ = curr_time;
}

ReflexEngine& ReflexEngine::get_instance() {
	static ReflexEngine instance;
	return instance;
}
