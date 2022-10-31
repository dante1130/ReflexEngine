#include "SceneManager.hpp"

#include <iostream>

#include "Controller/LuaManager.hpp"
#include "ReflexAssertion.hpp"

void SceneManager::init(const std::string& master_lua_script) {
	auto& lua = LuaManager::get_instance().get_state();

	auto scene_table = lua["Scene"].get_or_create<sol::table>();

	scene_table.set_function("create_scene", &SceneManager::create_scene, this);

	scene_table["load_scene"] = [this](const std::string& name) {
		current_scene_name_ = name;
		flag_change_scene_ = true;
	};

	lua.script_file(master_lua_script);
}

void SceneManager::create_scene(const std::string& name,
                                const std::string& master_lua_script) {
	scene_map_.insert_or_assign(name, master_lua_script);
}

void SceneManager::load_scene(const std::string& name) {
	current_scene_ = std::make_unique<ECSScene>(scene_map_.at(name));
	scene_lua_access(*current_scene_);
	astar_lua_access(current_scene_->get_astar());
	current_scene_->init();

	flag_change_scene_ = false;
}

void SceneManager::clear_scenes() {
	scene_map_.clear();
	current_scene_.reset();
}

ECSScene& SceneManager::current_scene() {
	REFLEX_ASSERT(current_scene_ != nullptr, "No scene loaded.");
	return *current_scene_;
}

const std::string& SceneManager::current_scene_name() const {
	return current_scene_name_;
}

bool SceneManager::flag_change_scene() const { return flag_change_scene_; }

void SceneManager::scene_lua_access(ECSScene& scene) {
	auto& lua = LuaManager::get_instance().get_state();

	auto scene_table = lua["Scene"].get_or_create<sol::table>();

	scene_table["add_game_object"] = [&scene](const std::string& lua_script) {
		std::cout << "Loading game object: " << lua_script << std::endl;
		scene.add_game_object(lua_script);
	};

	scene_table["get_astar"] = [&scene]() { return scene.get_astar(); };
}

auto SceneManager::astar_lua_access(AStar& astar) -> void {
	auto& lua = LuaManager::get_instance().get_state();

	auto astar_type = lua.new_usertype<AStar>("AStar");

	astar_type["set_grid"] = &AStar::setGrid;
	astar_type["set_grid_ratio"] = &AStar::set_grid_ratio;
	astar_type["set_grid_offset"] = &AStar::set_grid_offset;
	astar_type["reset_grid"] = &AStar::reset_grid_to_original;
	astar_type["set_coordinate_value"] = &AStar::set_coordinate_value;
	astar_type["find_path"] = &AStar::findPath;
}
