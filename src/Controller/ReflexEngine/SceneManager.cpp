#include "SceneManager.hpp"

#include "Controller/LuaManager.hpp"
#include <iostream>

void SceneManager::init(const std::string& master_lua_script) {
	auto& lua = LuaManager::get_instance().get_state();

	auto scene_table = lua["Scene"].get_or_create<sol::table>();

	scene_table.set_function("create_scene", &SceneManager::create_scene, this);
	scene_table.set_function("load_scene", &SceneManager::load_scene, this);
	scene_table.set_function("reset_scene", &SceneManager::reset_scene, this);

	lua.script_file(master_lua_script);
}

void SceneManager::create_scene(const std::string& name,
                                const std::string& master_lua_script) {
	auto& scene = scene_map_[name] =
	    std::make_unique<ECSScene>(master_lua_script);

	scene_lua_access(*scene);

	scene->init();

	// If a scene is loaded,
	// return Scene.add_game_object access back to the current scene.
	if (!current_scene_name_.empty()) {
		scene_lua_access(*scene_map_.at(current_scene_name_));
	}
}

void SceneManager::load_scene(const std::string& name) {
	current_scene_name_ = name;
	scene_lua_access(*scene_map_.at(current_scene_name_));
}

void SceneManager::reset_scene(const std::string& name) {
	auto& scene = scene_map_.at(name);
	scene = std::make_unique<ECSScene>(scene->get_master_lua_script());
	scene->init();
}

ECSScene& SceneManager::current_scene() const {
	return *scene_map_.at(current_scene_name_);
}

void SceneManager::scene_lua_access(ECSScene& scene) {
	auto& lua = LuaManager::get_instance().get_state();

	auto scene_table = lua["Scene"].get_or_create<sol::table>();

	scene_table["add_game_object"] = [&scene](const std::string& lua_script) {
		std::cout << "Loading game object: " << lua_script << std::endl;
		scene.add_game_object(lua_script);
	};
}
