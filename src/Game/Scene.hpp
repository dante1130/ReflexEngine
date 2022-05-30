#pragma once

#include <memory>
#include <vector>

#include "Model/GameObject/GameObject.hpp"

/**
 * @class Scene
 * @brief A scene in the game.
 */
class Scene {
public:
	/**
	 * @brief Initializes the scene.
	 */
	virtual void init() = 0;

	/**
	 * @brief	Adds a game object
	 * @param	luaScript	- The lua script of the object you want to add
	 *
	 * @pre	Nothing
	 * @post	Object adde
	 */
	virtual void addGameObject(const std::string& luaScript) = 0;

	/**
	 * @brief The function to specify controls for the keyboard.
	 *
	 * @param delta_time	- The time between frames
	 */
	virtual void key_controls(double delta_time) = 0;

	/**
	 * @brief The function to specify controls for the mouse.
	 *
	 * @param xpos	- the x position of mouse on screen
	 * @param ypos	- the y position of mouse on screen
	 */
	virtual void mouse_controls(double xpos, double ypos) = 0;

	/**
	 * @brief The update loop of the scene.
	 *
	 * @param delta_time	- the time between frames
	 */
	virtual void update(double delta_time) = 0;

	/**
	 * @brief The fixed update loop of the scene.
	 *
	 * @param delta_time
	 */
	virtual void fixed_update(double delta_time) = 0;

	/**
	 * @brief Adds any draw calls to the renderer.
	 */
	virtual void add_draw_call() = 0;

	/**
	 * @brief	Saves game objects
	 *
	 * @pre		Game objects exists
	 * @post	Game objects saved
	 */
	virtual void saveGameObjects() = 0;

	/**
	 * @brief	loads game objects
	 *
	 * @pre		Game objects exists in files
	 * @post	Game objects added
	 */
	virtual void loadSavedGameObjects() = 0;

	/**
	 * @brief Virtual destructor.
	 */
	virtual ~Scene() = default;

protected:
	/// A vector of game objects in the scene.
	std::vector<std::unique_ptr<GameObject>> game_objects_;
};
