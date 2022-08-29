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
#include "Controller/GUI/DebugLogger.hpp"
#include "ReflexAssertion.hpp"
#include "Controller/ReflexEngine/PerformanceLogger.hpp"
#include "Controller/GUI/DebugGUI.hpp"

void ReflexEngine::run() {
	auto& engine = ReflexEngine::get_instance();

	if (!engine.window_.init()) return;

	engine.lua_access();

	DebugLogger::clear();

	engine.renderer_.init();
	gui::init(engine.window_.get_window(), "#version 410");

	engine.scene_manager_.init("game/_Scenes.lua");

	load_default_resources();

	auto& input_manager = InputManager::get_instance();

	while (!engine.window_.is_should_close()) {
		EngineTime::update_delta_time(glfwGetTime());
		engine.window_.update_window_buffer_size();

		glfwPollEvents();
		input_manager.read_keys(engine.window_.get_window());
		input_manager.read_mouse_buttons(engine.window_.get_window());

		gui::mainLoopStart();

		if (engine.scene_manager_.flag_change_scene()) {
			engine.scene_manager_.load_scene(
			    engine.scene_manager_.current_scene_name());
		}

		ECSScene& scene = engine.scene_manager_.current_scene();

		if (EngineTime::is_paused()) {
			EngineTime::force_delta_time(0.0);
		} else {
			scene.mouse_controls(engine.window_.get_x_offset(),
			                     engine.window_.get_y_offset());
		}

		if (dataMgr.getDynamicBoolData("load_game", false)) {
			scene.load("game/ECSScene/save");
			dataMgr.setDynamicBoolData("load_game", false);
		} else if (dataMgr.getDynamicBoolData("save_game", false)) {
			scene.save("game/ECSScene/save");
			dataMgr.setDynamicBoolData("save_game", false);
		} else {
			if (EngineTime::is_time_step_passed()) {
				Physics::updateWorld(EngineTime::get_fixed_delta_time());
				scene.fixed_update(EngineTime::get_fixed_delta_time());
			}
			PERFORMANCE_LOGGER_PUSH("Update");
			scene.update(EngineTime::get_delta_time());
			PERFORMANCE_LOGGER_POP();
			PERFORMANCE_LOGGER_PUSH("Garbage collection");
			scene.garbage_collection();
			PERFORMANCE_LOGGER_POP();
			PERFORMANCE_LOGGER_PUSH("Add draw call");
			scene.add_draw_call();
			PERFORMANCE_LOGGER_POP();
			PERFORMANCE_LOGGER_PUSH("Draw");
			engine.renderer_.draw();
			PERFORMANCE_LOGGER_POP();
		}

		DebugGUI::draw();  // DO NOT PERFORMANCE LOGGER THIS
		DebugLogger::draw();

		gui::mainLoopEnd();

		engine.window_.swap_buffers();

		if (EngineTime::is_time_step_passed()) {
			EngineTime::reset_fixed_delta_time();
		}
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

void ReflexEngine::load_default_resources() {
	auto& resource_manager = ResourceManager::get_instance();

	resource_manager.get_texture_manager().load_texture("default",
	                                                    "textures/default.png");
	resource_manager.get_model_manager().load_model("default",
	                                                "models/default.obj");
	resource_manager.get_material_manager().load_material("default", 32.0f,
	                                                      1.0f);
}

void ReflexEngine::lua_access() {
	InputManager::get_instance();
	DebugLogger::lua_access();
	CollectionsGUI::lua_access();

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
