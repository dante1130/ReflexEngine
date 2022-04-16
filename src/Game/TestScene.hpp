#pragma once

#include <vector>
#include <unordered_map>

#include <glm/glm.hpp>

#include "Scene.hpp"
#include "Texture.hpp"
#include "Material.hpp"
#include "Model/GameObject/Item.hpp"
#include "Model/GameObject/Water.hpp"
#include "DirectionalLight.hpp"

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
};
