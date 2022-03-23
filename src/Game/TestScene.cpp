#include <functional>
#include "ReflexEngine/ReflexEngine.hpp"
#include "TestScene.hpp"

TestScene::TestScene() {}

void TestScene::init() {
	game_objects_.emplace_back(
	    std::make_shared<Item>("models/12221_Cat_v1_l3.obj", 256, 4.0f));

	game_objects_[0]->position = glm::vec3(0.0f, 0.0f, 0.0f);
}

void TestScene::draw() {
	for (auto& game_object : game_objects_) {
		game_object->add_draw_call();
	}
}
