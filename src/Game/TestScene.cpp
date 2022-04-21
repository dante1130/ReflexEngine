#include <functional>

#include "Controller/ReflexEngine/ReflexEngine.hpp"
#include "Controller/Input/InputManager.hpp"
#include "TestScene.hpp"

void TestScene::init() {
	directional_light_ =
	    DirectionalLight(2048, 2048, glm::vec3(1.0f, 0.53f, 0.3f), 0.2f,
	                     glm::vec3(-10.0f, -12.0f, 18.5f), 0.9f);

	sol::state& lua = LuaManager::get_instance().get_state();
	GenericFunctions::lua_access();

	lua.script_file("scripts/_Materials.lua");
	lua.set_function("addGameObject", &TestScene::addGameObject, this);
	lua.script_file("scripts/_MasterCreation.lua");

	InputManager::get_instance().load_lua_bindings("scripts/controls.lua");
}

void TestScene::add_game_object_during_run(std::string luaScript) {
	to_add_.push_back(luaScript);
}

void TestScene::addGameObject(std::string luaScript) {
	if (glfwGetTime() > (double)0.5) {
		add_game_object_during_run(luaScript);
	} else {
		std::cout << luaScript << std::endl;
		game_objects_.emplace_back(GameAssetFactory::create(luaScript));
	}
}

void TestScene::key_controls(float delta_time) {
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

	if (input_manager.get_key_state(Input::shoot).is_key_pressed()) {
		GenericFunctions::setIfShouldShoot(true);
	}
}

void TestScene::mouse_controls(float xpos, float ypos) {
	auto& camera = ReflexEngine::get_instance().camera_;

	camera.mouse_move(xpos, ypos);
}

void TestScene::add_draw_call() {
	auto& renderer = ReflexEngine::get_instance().renderer_;

	renderer.add_directional_light(directional_light_);

	for (auto& game_object : game_objects_) {
		game_object->add_draw_call();
	}
}

void TestScene::update(float delta_time) {
	garbage_collection();
	add_new_game_objects();

	for (auto& game_object : game_objects_) {
		game_object->update(delta_time);
	}
	GenericFunctions::networkUpdate();
}

void TestScene::fixed_update(float delta_time) {
	for (auto& game_object : game_objects_) {
		game_object->fixed_update(delta_time);
	}
}

void TestScene::saveGameObjects() {
	for (auto& game_object : game_objects_) {
		game_object->save_object();
	}
	GenericFunctions::setIfSave(false);
	std::cout << "done saving" << std::endl;
	ObjectSaving::setFreshSave();
	return;
}

void TestScene::loadSavedGameObjects() {
	game_objects_.clear();

	sol::state& lua = LuaManager::get_instance().get_state();
	lua.script_file("scripts/save/_MasterCreation.lua");

	GenericFunctions::setIfLoad(false);
	return;
}

void TestScene::garbage_collection() {
	int size = game_objects_.size();
	for (int count = 0; count < size; count++) {
		if (game_objects_[count]->position.y < -5000) {
			game_objects_.erase(game_objects_.begin() + count);
			size--;
			count--;
		}
	}
}

void TestScene::add_new_game_objects() {
	for (int count = 0; count < to_add_.size(); count++) {
		std::cout << "Adding during runtime = " << to_add_[count] << std::endl;
		game_objects_.emplace_back(GameAssetFactory::create(to_add_[count]));
	}
	to_add_.clear();
}
