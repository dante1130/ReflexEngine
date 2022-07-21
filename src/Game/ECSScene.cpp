#include "ECSScene.hpp"

#include "Controller/ReflexEngine/ReflexEngine.hpp"
#include "Controller/LuaManager.hpp"
#include "Controller/ECSGameAssetFactory.hpp"

void ECSScene::init() {
	auto& lua = LuaManager::get_instance().get_state();

	lua.set_function("add_game_object", &ECSScene::add_game_object, this);

	lua.script_file("scripts/ECSScene/_Materials.lua");
	lua.script_file("scripts/ECSScene/_MasterCreation.lua");
}

void ECSScene::add_game_object(const std::string& lua_script) {
	ECSGameAssetFactory::create(ecs_, lua_script);
}

void ECSScene::mouse_controls(double xpos, double ypos) {
	ReflexEngine::get_instance().camera_.mouse_move(xpos, ypos);
}

void ECSScene::update(double delta_time) { ecs_.update(delta_time); }

void ECSScene::fixed_update(double delta_time) {
	ecs_.fixed_update(delta_time);
}

void ECSScene::add_draw_call() { ecs_.draw(); }

void ECSScene::save_game_objects() {}

void ECSScene::load_saved_game_objects() {}

void ECSScene::garbage_collection() {}