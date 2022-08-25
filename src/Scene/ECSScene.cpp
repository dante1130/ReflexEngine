#include "ECSScene.hpp"

#include <filesystem>

#include "Controller/ReflexEngine/ReflexEngine.hpp"
#include "Controller/LuaManager.hpp"
#include "Controller/ECSGameAssetFactory.hpp"
#include "Controller/Audio/Audio.hpp"
#include "Controller/ECS/System.hpp"
#include "Controller/ECS/EntitySerializer.hpp"
#include "Controller/GUI/DebugGUI.hpp"

ECSScene::ECSScene(const std::string& master_lua_script)
    : Scene(master_lua_script) {}

void ECSScene::init() {
	Audio::get_instance().stop_all();
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

void ECSScene::add_draw_call() {
	ecs_gui_.draw(ecs_);
	ecs_.draw();
}

void ECSScene::save(const std::string& dir_path) {
	EntitySerializer::serialize(dir_path, ecs_);
}

void ECSScene::load(const std::string& dir_path) {
	if (!std::filesystem::exists(dir_path)) {
		return;
	}

	Audio::get_instance().stop_all();
	ecs_.clear_entities();

	std::filesystem::path path(dir_path);
	path /= "_SaveCreation.lua";

	LuaManager::get_instance().get_state().script_file(path.string());
}

void ECSScene::garbage_collection() { System::update_remove(ecs_); }

const std::string& ECSScene::get_master_lua_script() const {
	return master_lua_script_;
}
