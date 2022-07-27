#include "ECSScene.hpp"

#include "Controller/ReflexEngine/ReflexEngine.hpp"
#include "Controller/LuaManager.hpp"
#include "Controller/ECSGameAssetFactory.hpp"
#include "Controller/Audio/Audio.hpp"
#include "Controller/ECS/System.hpp"

ECSScene::ECSScene(const std::string& master_lua_script)
    : Scene(master_lua_script) {}

void ECSScene::init() {
	LuaManager::get_instance().get_state().script_file(master_lua_script_);
}

void ECSScene::add_game_object(const std::string& lua_script) {
	ECSGameAssetFactory::create(ecs_, lua_script);
}

void ECSScene::mouse_controls(double xpos, double ypos) {
	ReflexEngine::get_instance().camera_.mouse_move(xpos, ypos);
}

void ECSScene::update(double delta_time) {
	ecs_.update(delta_time);
	Audio::get_instance().update_listener();
}

void ECSScene::fixed_update(double delta_time) {
	ecs_.fixed_update(delta_time);
}

void ECSScene::add_draw_call() { ecs_.draw(); }

void ECSScene::save_game_objects() {}

void ECSScene::load_saved_game_objects() {}

void ECSScene::garbage_collection() { System::update_remove(ecs_); }

const std::string& ECSScene::get_master_lua_script() const {
	return master_lua_script_;
}
