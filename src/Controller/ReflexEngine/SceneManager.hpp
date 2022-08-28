#pragma once

#include <memory>
#include <unordered_map>

#include "Scene/ECSScene.hpp"

/**
 * @author Andrew Ho
 * @class SceneManager
 * @brief The scene manager.
 */
class SceneManager {
public:
	SceneManager() = default;

	/**
	 * @brief Runs the scene master lua script, which creates all the scenes
	 * into the scene manager.
	 *
	 * @param master_lua_script The master lua script.
	 */
	void init(const std::string& master_lua_script);

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
	 * @brief Clears all the scenes from the scene manager.
	 */
	void clear_scenes();

	/**
	 * @brief Get the current scene.
	 *
	 * @return ECSScene&
	 */
	ECSScene& current_scene();

	/**
	 * @brief Get the current scene name.
	 *
	 * @return const std::string&
	 */
	const std::string& current_scene_name() const;

	/**
	 * @brief Returns a boolean whether the current scene is changed.
	 *
	 * @return bool
	 */
	bool flag_change_scene() const;

private:
	/// The map of scenes, <scene name, path to master lua script>.
	std::unordered_map<std::string, std::string> scene_map_;
	/// The current scene.
	std::unique_ptr<ECSScene> current_scene_;
	/// The current scene name.
	std::string current_scene_name_;

	/// Flags whenever a scene is prompted to load from Lua.
	bool flag_change_scene_ = false;

	/**
	 * @brief Expose the add game object function to Lua for the scene.
	 */
	static void scene_lua_access(ECSScene& scene);
};