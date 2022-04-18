#pragma once

#include <vector>
#include <unordered_map>

#include <glm/glm.hpp>

#include "Scene.hpp"
#include "Model/GameObject/GameObject.hpp"
#include "View/Renderer/OpenGL/Objects/DirectionalLight.hpp"
#include "View/Renderer/OpenGL/Objects/SpotLight.hpp"
#include "guiManager.hpp"
#include "GameAssetFactory.hpp"
#include "Controller/GuiLuaAccess.hpp"
#include "guiManager.hpp"
#include "Controller/GenericFunctions.h"

/**
 * @class TestScene
 * @brief A test scene for testing purposes.
 */
class TestScene : public Scene {
public:
	/**
	 * @brief Default constructor
	 */
	TestScene();

	/**
	 * @brief Initializes the scene.
	 */
	void init() override;

	/**
	 * @brief	Adds a game object
	 * @param	No param
	 * @return	Void
	 *
	 * @pre	Nothing
	 * @post	Object adde
	 */
	void addGameObject(std::string luaScript) override;

	/**
	 * @brief The function to specify controls for the keyboard.
	 *
	 * @param keys
	 */
	void key_controls(float delta_time) override;

	/**
	 * @brief The function to specify controls for the mouse.
	 *
	 * @param xpos
	 * @param ypos
	 */
	void mouse_controls(float xpos, float ypos) override;

	/**
	 * @brief The update loop.
	 *
	 * @param delta_time
	 */
	void update(float delta_time) override;

	/**
	 * @brief Add draw calls to the renderer.
	 */
	void add_draw_call() override;

	/**
	 * @brief	Saves game objects
	 * @param	No param
	 * @return	Void
	 *
	 * @pre		Game objects exists
	 * @post	Game objects saved
	 */
	void saveGameObjects() override;

	/**
	 * @brief	loads game objects
	 * @param	No param
	 * @return	Void
	 *
	 * @pre		Game objects exists in files
	 * @post	Game objects added to scene
	 */
	void loadSavedGameObjects() override;

	/**
	 * @brief	Adds new game objects during run time
	 * @param	No param
	 * @return	Void
	 *
	 * @pre		Added game objects stored in list
	 * @post	Game objects loaded and stored
	 */
	void add_new_game_objects();

	/**
	 * @brief	Deleted game objects which are considered finished
	 * @param	No param
	 * @return	Void
	 *
	 * @pre		Game objects exists
	 * @post	Removed bad game objects
	 */
	void garbage_collection();

private:
	/// A directional light.
	DirectionalLight directional_light_ = {};

	/// Flashlight.
	SpotLight flashlight_ = {};
};
