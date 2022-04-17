#pragma once

#include <vector>
#include <unordered_map>

#include <glm/glm.hpp>

#include "Scene.hpp"
#include "View/Renderer/OpenGL/Objects/Texture.hpp"
#include "View/Renderer/OpenGL/Objects/Material.hpp"
#include "Model/GameObject/GameObject.hpp"
#include "View/Renderer/OpenGL/Objects/DirectionalLight.hpp"
#include "View/Renderer/OpenGL/Objects/SpotLight.hpp"
#include "guiManager.hpp"
#include "GameAssetFactory.hpp"
#include "Controller/MaterialLuaController.hpp"
#include "Controller/ResourceManager/ResourceManager.hpp"
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
	 * @brief The update loop.
	 *
	 * @param delta_time
	 */
	void update(float delta_time) override;

	/**
	 * @brief Add draw calls to the renderer.
	 */
	void add_draw_call() override;

private:
	/// A directional light.
	DirectionalLight directional_light_ = {};

	/// Flashlight.
	SpotLight flashlight_ = {};
};
