#include <functional>

#include "Controller/ReflexEngine/ReflexEngine.hpp"
#include "Controller/Input/InputManager.hpp"
#include "Controller/Audio/Audio.hpp"
#include "TestScene.hpp"
#include "AI/luaAccessScriptedFSM.hpp"

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
	auto& camera = ReflexEngine::get_instance().camera_;
	auto& input_manager = InputManager::get_instance();

	if (input_manager.get_key_state(Input::quit).is_key_pressed())
		GenericFunctions::set_if_credits_active(
		    !GenericFunctions::get_if_credits_active());

	camera.set_move_direction(glm::vec3(0, 0, 0));

	if (!(input_manager.get_key_state(Input::move_forward).is_key_hold() &&
	      input_manager.get_key_state(Input::move_backward).is_key_hold())) {
		if (input_manager.get_key_state(Input::move_forward).is_key_hold())
			camera.calculate_direction(Movement::forward);
		if (input_manager.get_key_state(Input::move_backward).is_key_hold())
			camera.calculate_direction(Movement::backward);
	}

	if (!(input_manager.get_key_state(Input::move_left).is_key_hold() &&
	      input_manager.get_key_state(Input::move_right).is_key_hold())) {
		if (input_manager.get_key_state(Input::move_left).is_key_hold())
			camera.calculate_direction(Movement::left);
		if (input_manager.get_key_state(Input::move_right).is_key_hold())
			camera.calculate_direction(Movement::right);
	}

	if (input_manager.get_key_state(Input::toggle_wireframe).is_key_pressed())
		ReflexEngine::get_instance().renderer_.toggle_wireframe();

	if (input_manager.get_key_state(Input::toggle_noclip).is_key_pressed())
		camera.toggle_noclip();

	if (input_manager.get_key_state(Input::pause_game).is_key_pressed())
		GenericFunctions::setIfPaused(!GenericFunctions::getIfPaused());

	if (input_manager.get_key_state(Input::help_menu).is_key_pressed())
		GenericFunctions::setifHelpMenuActive(
		    !GenericFunctions::getIfHelpMenuActive());

	if (input_manager.get_key_state(Input::network_menu).is_key_pressed()) {
		GenericFunctions::setNetworkMenuActive(
		    !GenericFunctions::getNetworkMenuActive());
	}
	if (input_manager.get_key_state(Input::network_pvp_menu).is_key_pressed()) {
		GenericFunctions::setPvPNetworkMenuActive(
		    !GenericFunctions::getPvPNetworkMenuActive());
	}

	if (input_manager.get_key_state(Input::shoot).is_key_pressed()) {
		GenericFunctions::setIfShouldShoot(true);
	}
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

	for (auto& game_object : game_objects_) {
		game_object->update(delta_time);
	}

	Audio::get_instance().update_listener();

	GenericFunctions::networkUpdate();
	messageMgr.dispatchDelayedMessages();
}

void TestScene::fixed_update(double delta_time) {
	for (auto& game_object : game_objects_) {
		game_object->fixed_update(delta_time);
	}
	GenericFunctions::networkFixedUpdate();
}

void TestScene::saveGameObjects() {
	for (auto& game_object : game_objects_) {
		game_object->save_object();
	}
	GenericFunctions::setIfSave(false);
	std::cout << "done saving" << std::endl;
	ObjectSaving::setFreshSave();
}

void TestScene::loadSavedGameObjects() {
	for (size_t count = 1; count < game_objects_.size(); count++) {
		game_objects_[count]->remove = true;
	}

	entityMgr.killEntities();
	physicsEntityMgr.killEntities();

	sol::state& lua = LuaManager::get_instance().get_state();
	if (GenericFunctions::getIfFullLoad() == false) {
		lua.script_file("scripts/save/_MasterCreation.lua");
	} else {
		game_objects_.clear();
		GenericFunctions::init_random(0, true);
		Audio& a = Audio::get_instance();
		a.stop_all();
		lua.script_file("scripts/_MasterCreation.lua");
		lua.script_file("scripts/AI/_MasterCreation.lua");
		GenericFunctions::setIfFullLoad(false);
	}

	GenericFunctions::setIfLoad(false);
}

void TestScene::garbage_collection() {
	constexpr int offset_y = -5000;

	for (size_t count = 0; count < game_objects_.size(); ++count) {
		// This checking for the y position should be in lua script.
		const bool is_should_remove =
		    game_objects_[count]->position.y < offset_y ||
		    game_objects_[count]->remove;

		if (is_should_remove) {
			physicsEntityMgr.garbage_collection();
			game_objects_.erase(game_objects_.begin() + count);
			--count;
		}
	}
}
