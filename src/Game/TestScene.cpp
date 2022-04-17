#include <functional>

#include "Controller/ReflexEngine/ReflexEngine.hpp"
#include "TestScene.hpp"
#include "guiManager.hpp"
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
	// MaterialLuaController::CreateLuaAccess();
	TextureManager& tm = ResourceManager::get_instance().get_texture_manager();
	ModelManager& mm = ResourceManager::get_instance().get_model_manager();
	lua.script_file("scripts/_Materials.lua");
	tm.get_texture("water");

	mm.get_model("cat");

	lua.set_function("addGameObject", &TestScene::addGameObject, this);
	lua.script_file("scripts/_MasterCreation.lua");

	gui::init(ReflexEngine::get_instance().window_.getWindow(), "#version 410");
	guiLuaAccess::exposeGui();
}

void TestScene::addGameObject(std::string luaScript) {
	game_objects_.emplace_back(gaf.create(luaScript));
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
	Camera& camera = ReflexEngine::get_instance().renderer_.get_camera();

	glm::vec3 lower_light = camera.GetCamPosition();
	lower_light.y -= 0.3f;

	glm::vec3 cam_direction = camera.GetCamDirection();

	flashlight_.SetFlash(lower_light, cam_direction);

	for (auto& game_object : game_objects_) {
		game_object->update(delta_time);
	}
}
