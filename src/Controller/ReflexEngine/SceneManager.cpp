#include "SceneManager.hpp"

#include "Controller/LuaManager.hpp"

void SceneManager::lua_access() {
	auto& lua = LuaManager::get_instance().get_state();

	auto scene_table = lua["Scene"].get_or_create<sol::table>();

	scene_table.set_function("create_scene", &SceneManager::create_scene, this);
	scene_table.set_function("load_scene", &SceneManager::load_scene, this);
	scene_table.set_function("reset_scene", &SceneManager::reset_scene, this);
}

void SceneManager::create_scene(const std::string& name,
                                const std::string& master_lua_script) {
	auto& scene = scene_map_[name] = ECSScene(master_lua_script);
	scene.init();
}

void SceneManager::load_scene(const std::string& name) {
	current_scene_ = &scene_map_.at(name);

	auto& lua = LuaManager::get_instance().get_state();

	auto scene_table = lua["Scene"].get_or_create<sol::table>();

	lua["add_game_object"] = [this](const std::string& lua_script) {
		current_scene_->add_game_object(lua_script);
	};
}

void SceneManager::reset_scene(const std::string& name) {
	auto& scene = scene_map_.at(name);
	scene = ECSScene(scene.get_master_lua_script());
	scene.init();
}

ECSScene& SceneManager::current_scene() const {
	assert(current_scene_ != nullptr, "No scene loaded!");
	return *current_scene_;
}
