#include "ReflexEngine.hpp"

#include "Game/TestScene.hpp"
#include "View/guiManager.hpp"
#include "NetworkManager.hpp"
#include "Controller/NetworkAccess.h"
#include "Controller/ReflexEngine/EngineAccess.hpp"
#include "Controller/ECS/ECSAccess.hpp"
#include "Controller/Input/InputManager.hpp"
#include "Controller/Audio/Audio.hpp"
#include "Controller/Physics/Physics.hpp"
#include "Controller/RandomGenerators/PseudoRandomNumberGenerator.hpp"
#include "Model/RunTimeDataStorage/GlobalDataStorage.hpp"
#include "Controller/Terrain/TerrainManager.hpp"

void ReflexEngine::run() {
	auto& engine = ReflexEngine::get_instance();

	if (!engine.window_.init()) return;

	engine.lua_access();

	engine.camera_ = Camera(glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
	                        -90.0f, 0.0f, 5.0f, 0.2f);

	engine.renderer_.init();
	gui::init(engine.window_.get_window(), "#version 410");

	engine.scenes_.emplace(std::make_unique<TestScene>());
	engine.scenes_.top()->init();

	glfwSetInputMode(engine.window_.get_window(), GLFW_CURSOR,
	                 GLFW_CURSOR_NORMAL);

	auto& input_manager = InputManager::get_instance();

	while (!engine.window_.is_should_close()) {
		EngineTime::update_delta_time(glfwGetTime());
		engine.window_.update_window_buffer_size();

		glfwPollEvents();
		input_manager.read_keys(engine.window_.get_window());
		input_manager.read_mouse_buttons(engine.window_.get_window());

		gui::mainLoopStart();

		if (EngineTime::is_paused()) {
			EngineTime::force_delta_time(0);
		} else {
			Physics::updateWorld(EngineTime::get_delta_time());
			engine.scenes_.top()->mouse_controls(engine.window_.get_x_offset(),
			                                     engine.window_.get_y_offset());
		}

		if (dataMgr.getDynamicBoolData("load_game", false))
			engine.scenes_.top()->load_saved_game_objects();
		else if (dataMgr.getDynamicBoolData("save_game", false))
			engine.scenes_.top()->save_game_objects();
		else {
			if (EngineTime::is_time_step_passed()) {
				engine.scenes_.top()->fixed_update(
				    EngineTime::get_fixed_delta_time());
				EngineTime::reset_fixed_delta_time();
			}

			engine.scenes_.top()->update(EngineTime::get_delta_time());
			engine.scenes_.top()->add_draw_call();
			engine.renderer_.draw();
		}

		gui::mainLoopEnd();

		engine.window_.swap_buffers();
	}

	while (!engine.scenes_.empty()) {
		engine.scenes_.pop();
	}
	entityMgr.killEntities();
	entityMgr.killManager();

	Physics::destroyWorld();
	gui::shutdown();
}

ReflexEngine& ReflexEngine::get_instance() {
	static ReflexEngine instance;
	return instance;
}

void ReflexEngine::lua_access() {
	InputManager::get_instance().lua_access();
	NetworkAccess::lua_access();
	EngineAccess::lua_access();
	ECSAccess::register_ecs();
	PseudoRandomNumberGenerator::lua_access();
	GlobalDataStorage::lua_access();
	TerrainManager::lua_access();
	ResourceManager::get_instance();
	Audio::get_instance();
	Physics::createWorld();

	camera_.lua_access();
}
