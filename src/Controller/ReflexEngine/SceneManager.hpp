#pragma once

#include <memory>
#include <unordered_map>

#include "Scene/ECSScene.hpp"

class SceneManager {
public:
	SceneManager() = default;

	void lua_access();

	void create_scene(const std::string& name,
	                  const std::string& master_lua_script);

	void load_scene(const std::string& name);

	void reset_scene(const std::string& name);

	ECSScene& current_scene() const;

private:
	std::unordered_map<std::string, ECSScene> scene_map_;
	ECSScene* current_scene_;
};