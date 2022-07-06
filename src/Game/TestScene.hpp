#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "Scene.hpp"
#include "Model/GameObject/GameObject.hpp"
#include "View/Renderer/OpenGL/Objects/DirectionalLight.hpp"
#include "View/Renderer/OpenGL/Objects/SpotLight.hpp"
#include "Controller/GameAssetFactory.hpp"
#include "Controller/NetworkAccess.h"
#include "Controller/LuaManager.hpp"

/**
 * @class TestScene
 * @brief A test scene for testing purposes.
 */
class TestScene : public Scene {
public:
	/**
	 * @brief Default constructor
	 */
	TestScene() = default;

	/**
	 * @brief Initializes the scene.
	 */
	void init() override;

	/**
	 * @brief	Adds a game object
	 * @param	luaScript	- a lua script to add
	 *
	 * @pre		Nothing
	 * @post	Object added
	 */
	void addGameObject(const std::string& luaScript) override;

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
	void saveGameObjects() override;

	/**
	 * @brief	loads game objects
	 *
	 * @pre		Game objects exists in files
	 * @post	Game objects added to scene
	 */
	void loadSavedGameObjects() override;

	/**
	 * @brief	Deleted game objects which are considered finished
	 *
	 * @pre		Game objects exists
	 * @post	Removed bad game objects
	 */
	void garbage_collection();
};
