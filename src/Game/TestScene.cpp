#include <functional>

#include "Controller/ReflexEngine/ReflexEngine.hpp"
#include "TestScene.hpp"
#include "guiManager.hpp"

TestScene::TestScene() {}

void TestScene::init() {
	directional_light_ =
	    DirectionalLight(2048, 2048, glm::vec3(1.0f, 0.53f, 0.3f), 1.0f,
	                     glm::vec3(-10.0f, -12.0f, 18.5f), 0.9f);

	game_objects_.emplace_back(
	    std::make_shared<Item>("models/12221_Cat_v1_l3.obj", 256, 4.0f));

	game_objects_.emplace_back(std::make_shared<Water>("textures/water.png"));

	game_objects_[0]->position = glm::vec3(0.0f, -2.0f, 4.0f);
	game_objects_[1]->position = glm::vec3(0.0f, -1.0f, 0.0f);

	gui::init(ReflexEngine::get_instance().window_.getWindow(), "#version 410");
}

void TestScene::add_draw_call() {
	auto& renderer = ReflexEngine::get_instance().renderer_;

	renderer.add_directional_light(directional_light_);

	for (auto& game_object : game_objects_) {
		game_object->add_draw_call();
	}
}

void TestScene::update(float delta_time) {
	auto& renderer = ReflexEngine::get_instance().renderer_;

	for (auto& game_object : game_objects_) {
		game_object->update(delta_time);
	}
}
