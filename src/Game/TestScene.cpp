#include <functional>

#include "Controller/ReflexEngine/ReflexEngine.hpp"
#include "TestScene.hpp"
#include "guiManager.hpp"
#include "GameAssetFactory.hpp"
#include "Model/GameObject/Body.hpp"
#include "Model/GameObject/BodyRigid.hpp"
#include "Model/GameObject/PhysicsObject.hpp"

TestScene::TestScene() {}

std::vector<std::shared_ptr<GameObject>> go;

void TestScene::init() {
	directional_light_ =
	    DirectionalLight(2048, 2048, glm::vec3(1.0f, 0.53f, 0.3f), 1.0f,
	                     glm::vec3(-10.0f, -12.0f, 18.5f), 0.9f);

	sol::state& lua = LuaManager::get_instance().get_state();
	lua.set_function("addGameObject", &TestScene::addGameObject, TestScene());
	lua.script_file("scripts/_MasterCreation.lua");
	for (int count = 0; count < go.size(); count++) {
		game_objects_.emplace_back(go[count]);
	}
	std::cout << "Number of objects loaded: " << game_objects_.size()
	          << std::endl;

	gui::init(ReflexEngine::get_instance().window_.getWindow(), "#version 410");
}

void TestScene::addGameObject(std::string luaScript) {
	std::cout << "adding game object: " << luaScript << std::endl;
	GameAssetFactory gaf;
	go.emplace_back(gaf.create(luaScript));
}

void TestScene::add_draw_call() {
	auto& renderer = ReflexEngine::get_instance().renderer_;

	renderer.add_directional_light(directional_light_);

	for (auto& game_object : game_objects_) {
		game_object->add_draw_call();
	}
}

void TestScene::update(float delta_time) {
	for (auto& game_object : game_objects_) {
		game_object->update(delta_time);
	}
}
