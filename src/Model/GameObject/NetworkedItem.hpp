#pragma once

#include <string>

#include "GameObject.hpp"
#include "Controller/ResourceManager/ResourceManager.hpp"
#include "View/Renderer/OpenGL/Objects/Model.hpp"
#include "View/Renderer/OpenGL/Objects/Texture.hpp"
#include "View/Renderer/OpenGL/Objects/Material.hpp"
#include "Controller/ResourceManager/ObjectSaving.hpp"
#include <NetworkManager.hpp>

/**
 * @class Item
 * @brief An item in the scene that has networking functionality
 */
class NetworkedItem : public GameObject {
public:
	/**
	 * @brief Construct a new Item object with a model name and a texture name.
	 *
	 * @param model_name
	 * @param texture_name
	 */
	NetworkedItem(const std::string& model_name, const std::string& texture_name);

	/**
	 * @brief Initializes the item with a model, a texture, and a material.
	 */
	void init() override {}

	/**
	 * @brief Updates the item with delta time.
	 *
	 * @param delta_time
	 */
	void update(float delta_time) override {}

	/**
	 * @brief Updates the body object with fixed delta time.
	 *
	 * @param delta_time
	 */
	void fixed_update(float delta_time) override {}

	/**
	 * @brief Adds the draw call to the renderer.
	 */
	void add_draw_call() override;

	void initNetworkManager();

	/**
	 * @brief The draw call for the item.
	 *
	 * @param shader
	 */
	void draw(std::shared_ptr<Shader> shader) override;

	/**
	 * @brief	Saves the object to lau file
	 * @param	No param
	 * @return	Void
	 *
	 * @pre		Object exists
	 * @post	Object saved
	 */
	void save_object() override;

private:
	/// The model of the item.
	std::string model_name_;
	/// The material of the item.
	std::string material_name_;
	/// The paired networkManager of the other connected client
	networkManager client;
};
