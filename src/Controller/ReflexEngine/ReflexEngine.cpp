#include "ReflexEngine.hpp"

#include "View/guiManager.hpp"
#include "NetworkManager.hpp"
#include "Controller/Networking/NetworkAccess.h"
#include "Controller/MathAccess.hpp"
#include "Controller/ECS/ECSAccess.hpp"
#include "Controller/AI/luaAccessScriptedFSM.hpp"
#include "Controller/Input/InputManager.hpp"
#include "Controller/Audio/Audio.hpp"
#include "Controller/Physics/Physics.hpp"
#include "Controller/RandomGenerators/PseudoRandomNumberGenerator.hpp"
#include "Model/RunTimeDataStorage/GlobalDataStorage.hpp"
#include "Controller/Terrain/TerrainManager.hpp"
#include "Model/singletons.h"

void ReflexEngine::run() {
	auto& engine = ReflexEngine::get_instance();

	if (!engine.window_.init()) return;

	engine.lua_access();

	engine.renderer_.init();
	gui::init(engine.window_.get_window(), "#version 410");

	engine.scene_manager_.init("game/_Scenes.lua");

	auto& input_manager = InputManager::get_instance();

	while (!engine.window_.is_should_close()) {
		EngineTime::update_delta_time(glfwGetTime());
		engine.window_.update_window_buffer_size();

		glfwPollEvents();
		input_manager.read_keys(engine.window_.get_window());
		input_manager.read_mouse_buttons(engine.window_.get_window());

		gui::mainLoopStart();

		ECSScene& scene = engine.scene_manager_.current_scene();

		if (EngineTime::is_paused()) {
			EngineTime::force_delta_time(0);
		} else {
			Physics::updateWorld(EngineTime::get_delta_time());
			scene.mouse_controls(engine.window_.get_x_offset(),
			                     engine.window_.get_y_offset());
		}

		if (dataMgr.getDynamicBoolData("load_game", false))
			scene.load_saved_game_objects();
		else if (dataMgr.getDynamicBoolData("save_game", false))
			scene.save_game_objects();
		else {
			if (EngineTime::is_time_step_passed()) {
				scene.fixed_update(EngineTime::get_fixed_delta_time());
				EngineTime::reset_fixed_delta_time();
			}

			scene.update(EngineTime::get_delta_time());
			scene.garbage_collection();
			scene.add_draw_call();
			engine.renderer_.draw();
		}

		gui::mainLoopEnd();

		engine.window_.swap_buffers();
	}

	engine.scene_manager_.clear_scenes();

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
	InputManager::get_instance();
	NetworkAccess::lua_access();
	MathAccess::lua_access();
	ECSAccess::register_ecs();
	PseudoRandomNumberGenerator::lua_access();
	GlobalDataStorage::lua_access();
	OldTerrainManager::lua_access();
	ResourceManager::get_instance();
	Audio::get_instance();
	Physics::createWorld();
	luaAccessScriptedFSM::registerAllAI();
	EngineTime::lua_access();

	window_.lua_access();
	camera_.lua_access();
}
