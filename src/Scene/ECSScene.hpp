#pragma once

#include <vector>

#include "Scene.hpp"

#include "Controller/ECS/ECS.hpp"
#include "Controller/GUI/ECSGui.hpp"

/**
 * @class ECSScene
 * @brief A scene using ECS
 */
class ECSScene : public Scene {
public:
	/**
	 * @brief Construct a new ECSScene object
	 *
	 * @param master_lua_script The master lua script
	 */
	ECSScene(const std::string& master_lua_script);

	/**
	 * @brief Initializes the scene.
	 */
	void init() override;

	/**
	 * @brief	Adds a game object
	 * @param	lua_script	- a lua script to add
	 *
	 * @pre		Nothing
	 * @post	Object added
	 */
	void add_game_object(const std::string& lua_script) override;

	/**
	 * @brief The function to specify controls for the mouse.
	 *
	 * @param xpos	- X position of mouse on screen
	 * @param ypos	- Y position of mouse on screen
	 */
	void mouse_controls(double xpos, double ypos) override;

	/**
	 * @brief The update loop of the scene.
	 *
	 * @param delta_time	- The time between frames
	 */
	void update(double delta_time) override;

	/**
	 * @brief The fixed update loop of the scene.
	 *
	 * @param delta_time
	 */
	void fixed_update(double delta_time) override;

	/**
	 * @brief Add draw calls to the renderer.
	 */
	void add_draw_call() override;

	/**
	 * @brief	Saves game objects
	 *
	 * @pre		Game objects exists
	 * @post	Game objects saved
	 */
	void save() override;

	/**
	 * @brief	loads game objects
	 *
	 * @pre		Game objects exists in files
	 * @post	Game objects added to scene
	 */
	void load() override;

	/**
	 * @brief	Deleted game objects which are considered finished
	 *
	 * @pre		Game objects exists
	 * @post	Removed bad game objects
	 */
	void garbage_collection() override;

	/**
	 * @brief Get the master lua script object
	 *
	 * @return const std::string& The master lua script object
	 */
	const std::string& get_master_lua_script() const override;

private:
	ECS ecs_;
	ECSGui ecs_gui_;
};
