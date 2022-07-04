#include <functional>

#include "Controller/ReflexEngine/ReflexEngine.hpp"
#include "Controller/Input/InputManager.hpp"
#include "Controller/Audio/Audio.hpp"
#include "TestScene.hpp"
#include "Controller/AI/luaAccessScriptedFSM.hpp"
#include "Controller/RandomGenerators/PseudoRandomNumberGenerator.hpp"
#include "Model/RunTimeDataStorage/GlobalDataStorage.hpp"
#include "Controller/ReflexEngine/EngineAccess.hpp"

void TestScene::init() {
	sol::state& lua = LuaManager::get_instance().get_state();

	lua.set_function("addGameObject", &TestScene::addGameObject, this);
	luaAccessScriptedFSM::registerAllAI();
	lua.script_file("scripts/AI/statemachine.lua");
	lua.script_file(
	    "scripts/AI/setupPlayerFSM.lua");  // All player/NPC setup functions are
	                                       // found in here

	lua.script_file("scripts/_Materials.lua");
	lua.script_file("scripts/_Sounds.lua");
	lua.script_file("scripts/_MasterCreation.lua");
	lua.script_file("scripts/AI/_MasterCreation.lua");
}

void TestScene::addGameObject(const std::string& luaScript) {
	std::cout << "Adding " << luaScript << std::endl;
	game_objects_.emplace_back(GameAssetFactory::create(luaScript));
}

void TestScene::key_controls(double delta_time) {
	// auto& camera = ReflexEngine::get_instance().camera_;
	// auto& input_manager = InputManager::get_instance();

	// if (input_manager.get_key_state(Input::quit).is_key_pressed())
	// 	dataMgr.setDynamicBoolData(
	// 	    "show_credits", !dataMgr.getDynamicBoolData("show_credits", false));

	// camera.set_move_direction(glm::vec3(0, 0, 0));

	// if (!(input_manager.get_key_state(Input::move_forward).is_key_hold() &&
	//       input_manager.get_key_state(Input::move_backward).is_key_hold())) {
	// 	if (input_manager.get_key_state(Input::move_forward).is_key_hold())
	// 		camera.calculate_direction(Movement::forward);
	// 	if (input_manager.get_key_state(Input::move_backward).is_key_hold())
	// 		camera.calculate_direction(Movement::backward);
	// }

	// if (!(input_manager.get_key_state(Input::move_left).is_key_hold() &&
	//       input_manager.get_key_state(Input::move_right).is_key_hold())) {
	// 	if (input_manager.get_key_state(Input::move_left).is_key_hold())
	// 		camera.calculate_direction(Movement::left);
	// 	if (input_manager.get_key_state(Input::move_right).is_key_hold())
	// 		camera.calculate_direction(Movement::right);
	// }

	// if
	// (input_manager.get_key_state(Input::toggle_wireframe).is_key_pressed())
	// 	ReflexEngine::get_instance().renderer_.toggle_wireframe();

	// if (input_manager.get_key_state(Input::toggle_noclip).is_key_pressed())
	// 	camera.toggle_noclip();

	// if (input_manager.get_key_state(Input::pause_game).is_key_pressed())
	// 	EngineAccess::setIfPaused(!EngineAccess::getIfPaused());

	// if (input_manager.get_key_state(Input::help_menu).is_key_pressed())
	// 	dataMgr.setDynamicBoolData(
	// 	    "help_menu", !dataMgr.getDynamicBoolData("help_menu", false));

	// if (input_manager.get_key_state(Input::network_menu).is_key_pressed()) {
	// 	NetworkAccess::setNetworkMenuActive(
	// 	    !NetworkAccess::getNetworkMenuActive());
	// }
	// if
	// (input_manager.get_key_state(Input::network_pvp_menu).is_key_pressed()) {
	// 	NetworkAccess::setPvPNetworkMenuActive(
	// 	    !NetworkAccess::getPvPNetworkMenuActive());
	// }

	// if (input_manager.get_key_state(Input::shoot).is_key_pressed()) {
	// 	dataMgr.setDynamicBoolData("should_shoot", true);
	// }
}

void TestScene::mouse_controls(double xpos, double ypos) {
	auto& camera = ReflexEngine::get_instance().camera_;

	camera.mouse_move(xpos, ypos);
}

void TestScene::add_draw_call() {
	for (auto& game_object : game_objects_) {
		game_object->add_draw_call();
	}
}

void TestScene::update(double delta_time) {
	garbage_collection();

	for (size_t i = 0; i < game_objects_.size(); i++) {
		game_objects_.at(i)->update(delta_time);
	}

	Audio::get_instance().update_listener();

	NetworkAccess::networkUpdate();
}

void TestScene::fixed_update(double delta_time) {
	for (auto& game_object : game_objects_) {
		game_object->fixed_update(delta_time);
	}
	NetworkAccess::networkFixedUpdate();
	messageMgr.dispatchDelayedMessages();
}

void TestScene::saveGameObjects() {
	for (auto& game_object : game_objects_) {
		game_object->save_object();
	}
	dataMgr.setDynamicBoolData("save_game", false);
	std::cout << "done saving" << std::endl;
	ObjectSaving::setFreshSave();
}

void TestScene::loadSavedGameObjects() {
	for (size_t count = 1; count < game_objects_.size(); count++) {
		game_objects_[count]->remove = true;
	}

	entityMgr.killEntities();

	sol::state& lua = LuaManager::get_instance().get_state();
	if (dataMgr.getDynamicBoolData("reload_game", false) == false) {
		lua.script_file("scripts/save/_MasterCreation.lua");
	} else {
		game_objects_.clear();
		PseudoRandomNumberGenerator::init_random(0, true);
		Audio& a = Audio::get_instance();
		a.stop_all();
		lua.script_file("scripts/_MasterCreation.lua");
		lua.script_file("scripts/AI/_MasterCreation.lua");
		dataMgr.setDynamicBoolData("reload_game", false);
	}

	dataMgr.setDynamicBoolData("load_game", false);
}

void TestScene::garbage_collection() {
	constexpr int offset_y = -5000;

	for (size_t count = 0; count < game_objects_.size(); ++count) {
		// This checking for the y position should be in lua script.
		const bool is_should_remove =
		    game_objects_[count]->position.y < offset_y ||
		    game_objects_[count]->remove;

		if (is_should_remove) {
			game_objects_.erase(game_objects_.begin() + count);
			--count;
		}
	}
}
