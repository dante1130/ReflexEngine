#include "SceneManager.hpp"

#include "Controller/LuaManager.hpp"
#include <iostream>

void SceneManager::init(const std::string& master_lua_script) {
	auto& lua = LuaManager::get_instance().get_state();

	auto scene_table = lua["Scene"].get_or_create<sol::table>();

	scene_table.set_function("create_scene", &SceneManager::create_scene, this);
	scene_table.set_function("load_scene", &SceneManager::load_scene, this);

	lua.script_file(master_lua_script);
}

void SceneManager::create_scene(const std::string& name,
                                const std::string& master_lua_script) {
	scene_map_.insert_or_assign(name, master_lua_script);
}

void SceneManager::load_scene(const std::string& name) {
	current_scene_ = std::make_unique<ECSScene>(scene_map_.at(name));
	scene_lua_access(*current_scene_);
	current_scene_->init();
}

void SceneManager::clear_scenes() {
	scene_map_.clear();
	current_scene_.reset();
}

ECSScene& SceneManager::current_scene() {
	assert(current_scene_ != nullptr);
	return *current_scene_;
}

void SceneManager::scene_lua_access(ECSScene& scene) {
	auto& lua = LuaManager::get_instance().get_state();

	auto scene_table = lua["Scene"].get_or_create<sol::table>();

	scene_table["add_game_object"] = [&scene](const std::string& lua_script) {
		std::cout << "Loading game object: " << lua_script << std::endl;
		scene.add_game_object(lua_script);
	};
}
