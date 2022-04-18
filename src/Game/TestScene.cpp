#include <functional>

#include "Controller/ReflexEngine/ReflexEngine.hpp"
#include "Controller/Input/InputManager.hpp"
#include "TestScene.hpp"
TestScene::TestScene() {}

GameAssetFactory gaf;
void TestScene::init() {
	directional_light_ =
	    DirectionalLight(2048, 2048, glm::vec3(1.0f, 0.53f, 0.3f), 0.2f,
	                     glm::vec3(-10.0f, -12.0f, 18.5f), 0.9f);

	flashlight_ =
	    SpotLight(1024, 1024, 0.01f, 100.0f, glm::vec3(1.0f, 1.0f, 1.0f), 0.0f,
	              2.0f, glm::vec3(0.0f, 0.0f, 0.0f),
	              glm::vec3(0.0f, -1.0f, 0.0f), 1.0f, 0.0f, 0.0f, 20.0f);

	sol::state& lua = LuaManager::get_instance().get_state();
	GenericFunctions::lua_access();

	lua.script_file("scripts/_Materials.lua");
	lua.set_function("addGameObject", &TestScene::addGameObject, this);
	lua.script_file("scripts/_MasterCreation.lua");

	InputManager::get_instance().load_lua_bindings("scripts/controls.lua");
}

std::vector<std::string> to_add;

void addGameObjectDuringRun(std::string luaScript) {
	to_add.push_back(luaScript);
}

void TestScene::addGameObject(std::string luaScript) {
	if (glfwGetTime() > (double)0.5) {
		addGameObjectDuringRun(luaScript);
	} else {
		std::cout << luaScript << std::endl;
		game_objects_.emplace_back(gaf.create(luaScript));
	}
}

void TestScene::key_controls(float delta_time) {
	auto& camera = ReflexEngine::get_instance().camera_;
	auto& input_manager = InputManager::get_instance();

	if (input_manager.get_key_state(Input::quit))
		ReflexEngine::get_instance().window_.set_should_close(true);

	if (input_manager.get_key_state(Input::move_forward))
		camera.move(CameraMovement::forward, delta_time);
	if (input_manager.get_key_state(Input::move_backward))
		camera.move(CameraMovement::backward, delta_time);
	if (input_manager.get_key_state(Input::move_left))
		camera.move(CameraMovement::left, delta_time);
	if (input_manager.get_key_state(Input::move_right))
		camera.move(CameraMovement::right, delta_time);
	//
	if (input_manager.get_key_state(Input::toggle_wireframe))
		ReflexEngine::get_instance().renderer_.toggle_wireframe();
	if (input_manager.get_key_state(Input::toggle_noclip))
		camera.toggle_noclip();

	if (input_manager.get_key_state(Input::pause_game))
		GenericFunctions::setIfPaused(!GenericFunctions::getIfPaused());

	if (input_manager.get_key_state(Input::help_menu))
		GenericFunctions::setifHelpMenuActive(
		    !GenericFunctions::getIfHelpMenuActive());

	if (input_manager.get_key_state(Input::shoot)) {
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
	renderer.add_spot_light(flashlight_);

	for (auto& game_object : game_objects_) {
		game_object->add_draw_call();
	}
}

void TestScene::update(float delta_time) {
	garbage_collection();
	add_new_game_objects();

	const auto& camera = ReflexEngine::get_instance().camera_;

	glm::vec3 lower_light = camera.get_position();
	lower_light.y -= 0.3f;

	glm::vec3 cam_direction = camera.get_direction();

	flashlight_.SetFlash(lower_light, cam_direction);

	for (auto& game_object : game_objects_) {
		game_object->update(delta_time);
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
	std::cout << "Number of game objects loaded after save: "
	          << game_objects_.size() << std::endl;

	GenericFunctions::setIfLoad(false);
	return;
}

void TestScene::garbage_collection() {
	for (int count = 0; count < game_objects_.size(); count++) {
		if (game_objects_[count]->position.y < -1000) {
			game_objects_.erase(game_objects_.begin() + count);
		}
	}
}

void TestScene::add_new_game_objects() {
	for (int count = 0; count < to_add.size(); count++) {
		std::cout << "Adding during runtime = " << to_add[count] << std::endl;
		game_objects_.emplace_back(gaf.create(to_add[count]));
	}
	to_add.clear();
}
