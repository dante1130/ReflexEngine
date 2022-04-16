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
	 * @param	No param
	 * @return	Void
	 *
	 * @pre	Nothing
	 * @post	Object adde
	 */
	virtual void addGameObject(std::string luaScript) = 0;

	/**
	 * @brief The update loop of the scene.
	 *
	 * @param delta_time
	 */
	virtual void update(float delta_time) = 0;

	/**
	 * @brief Adds any draw calls to the renderer.
	 */
	virtual void add_draw_call() = 0;

	/**
	 * @brief Virtual destructor.
	 */
	virtual ~Scene() = default;

protected:
	/// A vector of game objects in the scene.
	std::vector<std::shared_ptr<GameObject>> game_objects_;
};
