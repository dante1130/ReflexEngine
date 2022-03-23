#include <functional>
#include "ReflexEngine/ReflexEngine.hpp"
#include "TestScene.hpp"

TestScene::TestScene() {}

void TestScene::init() {
	directional_light_ =
	    DirectionalLight(2048, 2048, glm::vec3(1.0f, 0.53f, 0.3f), 0.1f,
	                     glm::vec3(-10.0f, -12.0f, 18.5f), 0.9f);

	game_objects_.emplace_back(
	    std::make_shared<Item>("models/12221_Cat_v1_l3.obj", 256, 4.0f));

	game_objects_[0]->position = glm::vec3(0.0f, -2.0f, 4.0f);
}

void TestScene::draw() {
	auto shader = ReflexEngine::get_instance().renderer_.get_shader();

	shader->SetDirectionalLight(directional_light_);

	shader->SetDirectionalLightTransform(
	    directional_light_.CalculateLightTransform());

	directional_light_.GetShadowMap()->Read(GL_TEXTURE2);

	shader->SetTexture(1);
	shader->SetDirectionalShadowMap(2);

	for (auto& game_object : game_objects_) {
		game_object->add_draw_call();
	}
}
