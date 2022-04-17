#include <functional>

#include "Controller/ReflexEngine/ReflexEngine.hpp"
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

	gui::init(ReflexEngine::get_instance().window_.getWindow(), "#version 410");
	guiLuaAccess::exposeGui();
}

void TestScene::addGameObject(std::string luaScript) {
	game_objects_.emplace_back(gaf.create(luaScript));
}

void TestScene::key_controls(const bool* keys, float delta_time) {
	auto& renderer = ReflexEngine::get_instance().renderer_;
	auto& camera = ReflexEngine::get_instance().camera_;

	if (keys[GLFW_KEY_W]) camera.move(CameraMovement::forward, delta_time);
	if (keys[GLFW_KEY_S]) camera.move(CameraMovement::backward, delta_time);
	if (keys[GLFW_KEY_A]) camera.move(CameraMovement::left, delta_time);
	if (keys[GLFW_KEY_D]) camera.move(CameraMovement::right, delta_time);

	if (keys[GLFW_KEY_C]) renderer.toggle_wireframe();
	if (keys[GLFW_KEY_Z]) camera.toggle_noclip();
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
	const auto& camera = ReflexEngine::get_instance().camera_;

	glm::vec3 lower_light = camera.get_position();
	lower_light.y -= 0.3f;

	glm::vec3 cam_direction = camera.get_direction();

	flashlight_.SetFlash(lower_light, cam_direction);

	for (auto& game_object : game_objects_) {
		game_object->update(delta_time);
	}
}
