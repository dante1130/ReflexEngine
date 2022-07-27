#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "Scene.hpp"
#include "Model/GameObject/GameObject.hpp"
#include "View/Renderer/OpenGL/Objects/DirectionalLight.hpp"
#include "View/Renderer/OpenGL/Objects/SpotLight.hpp"
#include "Controller/GameAssetFactory.hpp"
#include "Controller/Networking/NetworkAccess.h"
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
	void add_game_object(const std::string& luaScript) override;

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
	void save_game_objects() override;

	/**
	 * @brief	loads game objects
	 *
	 * @pre		Game objects exists in files
	 * @post	Game objects added to scene
	 */
	void load_saved_game_objects() override;

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
	/// A vector of game objects in the scene.
	std::vector<std::unique_ptr<GameObject>> game_objects_;
};
