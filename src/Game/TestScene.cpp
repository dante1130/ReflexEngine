#include <functional>

#include "Controller/ReflexEngine/ReflexEngine.hpp"
#include "Controller/Input/InputManager.hpp"
#include "TestScene.hpp"
#include "AI/NPC.hpp"
#include "AI/playerStates.h"
#include "AI/entityManager.h"
#include "AI/messageDispatcher.h"

void TestScene::init() {
	directional_light_ =
	    DirectionalLight(2048, 2048, glm::vec3(0.22f, 0.40f, 0.59f), 0.1f,
	                     glm::vec3(-15.0f, -15.0f, 18.5f), 0.5f);

	sol::state& lua = LuaManager::get_instance().get_state();

	lua.set_function("addGameObject", &TestScene::addGameObject, this);

	lua.script_file("scripts/_Materials.lua");
	lua.script_file("scripts/_MasterCreation.lua");
	lua.script_file("scripts/_Sounds.lua");

	NPC* player = new NPC();
	player->set_id(0);
	player->set_faction(1);
	player->position = glm::vec3(90, 5, 45);
	player->initModel("human", "shiny");

	/*
	NPC* patroller = new NPC();
	patroller->set_id(1);
	patroller->position = glm::vec3(100, 5, 65);
	patroller->scale = glm::vec3(0.01f);
	patroller->angle = 180;
	patroller->new_state(&patrol_state::Instance());
	patroller->initModel("ghost", "shiny");

	NPC* sentry = new NPC();
	sentry->set_id(2);
	sentry->position = glm::vec3(105, 5, 70);
	sentry->scale = glm::vec3(0.01f);
	sentry->angle = 0;
	sentry->new_state(&patrol_state::Instance());
	sentry->initModel("ghost", "shiny");
	*/

	game_objects_.emplace_back(player);
	// game_objects_.emplace_back(patroller);
	// game_objects_.emplace_back(sentry);
	entityMgr.registerEntity(player);
	// entityMgr.registerEntity(patroller);
	// entityMgr.registerEntity(sentry);
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

	if (input_manager.get_key_state(Input::toggle_wireframe).is_key_pressed()) {
		ReflexEngine::get_instance().renderer_.toggle_wireframe();
		glm::vec3 direction = camera.get_direction();

		std::cout << "Direction: " << direction.x << " " << direction.y << " "
		          << direction.z << std::endl;
	}

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
	messageMgr.dispatchDelayedMessages();
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

static bool done = false;
void TestScene::garbage_collection() {
	int size = game_objects_.size();
	for (int count = 0; count < size; count++) {
		if (game_objects_[count]->position.y < -5000 ||
		    game_objects_[count]->remove) {
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

	if (!done) {
		gameWorld.show_world();
		done = true;
	}
}
