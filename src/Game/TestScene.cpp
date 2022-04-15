#include <functional>

#include "Controller/ReflexEngine/ReflexEngine.hpp"
#include "TestScene.hpp"
#include "guiManager.hpp"
#include "GameAssetFactory.hpp"
#include "Model/GameObject/Body.hpp"
#include "Model/GameObject/BodyRigid.hpp"

TestScene::TestScene() {}

void TestScene::init() {
	directional_light_ =
	    DirectionalLight(2048, 2048, glm::vec3(1.0f, 0.53f, 0.3f), 1.0f,
	                     glm::vec3(-10.0f, -12.0f, 18.5f), 0.9f);

	GameAssetFactory gaf;
	game_objects_.emplace_back(gaf.create("scripts/Cat.lua"));
	game_objects_.emplace_back(gaf.create("scripts/Water.lua"));

	Body* b = new Body();
	b->init();
	game_objects_.emplace_back(b);

	BodyRigid* rb = new BodyRigid();
	rb->rotation = glm::vec3(1, 0, 0);
	rb->angle = -90;
	rb->createBR(glm::vec3(0, 25, 0), rb->rotation, rb->angle);
	rb->setType(2);
	rb->enableGravity(true);
	rb->addSphereCollider(glm::vec3(0, 0, 0), 2, 0.5, 0.5);
	game_objects_.emplace_back(rb);

	game_objects_.emplace_back(gaf.create("scripts/Cat.lua"));

	rb = new BodyRigid();
	rb->createBR(glm::vec3(0, 0, 0), rb->rotation, rb->angle);
	rb->position = glm::vec3(0, 0, 0);
	rb->setType(1);
	rb->enableGravity(false);
	rb->addSphereCollider(glm::vec3(0, 0, 0), 2, 0.5, 0.5);
	game_objects_.emplace_back(rb);

	b = new Body();
	b->init();
	b->setCreator(false);
	game_objects_.emplace_back(b);

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
	game_objects_[0]->position = game_objects_[3]->position;
	game_objects_[0]->rotation = game_objects_[3]->rotation;
	game_objects_[0]->angle = game_objects_[3]->angle;

	game_objects_[4]->position = game_objects_[5]->position;

	for (auto& game_object : game_objects_) {
		game_object->update(delta_time);
	}
}
