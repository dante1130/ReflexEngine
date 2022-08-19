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

private:
	/// The map of scenes, <scene name, path to master lua script>.
	std::unordered_map<std::string, std::string> scene_map_;
	/// The current scene name.
	std::unique_ptr<ECSScene> current_scene_;

	/**
	 * @brief Expose the add game object function to Lua for the scene.
	 */
	static void scene_lua_access(ECSScene& scene);
};