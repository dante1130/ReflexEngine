#pragma once

#include <memory>
#include <unordered_map>

#include "Scene/ECSScene.hpp"

/**
 * @class SceneManager
 * @brief The scene manager.
 */
class SceneManager {
public:
	SceneManager() = default;

	/**
	 * @brief Register the scene manager to lua.
	 */
	void lua_access();

	/**
	 * @brief Create a scene with a given name and its master lua script.
	 *
	 * @param name The name of the scene.
	 * @param master_lua_script The master lua script of the scene.
	 */
	void create_scene(const std::string& name,
	                  const std::string& master_lua_script);

	/**
	 * @brief Load a scene with a given name.
	 *
	 * @param name The name of the scene.
	 *
	 * @pre The scene with the given name must exist.
	 * @post The scene with the given name is loaded, and usage of
	 * Scene.add_game_object is directed to the scene loaded.
	 */
	void load_scene(const std::string& name);

	/**
	 * @brief Reset a scene with a given name.
	 *
	 * @param name The name of the scene.
	 */
	void reset_scene(const std::string& name);

	/**
	 * @brief Get the current scene.
	 *
	 * @return ECSScene&
	 */
	ECSScene& current_scene() const;

private:
	/// The map of scenes.
	std::unordered_map<std::string, ECSScene> scene_map_;
	/// The current scene.
	ECSScene* current_scene_ = nullptr;
};