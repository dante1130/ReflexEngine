#pragma once

#include <string>

#include "GameObject.hpp"
#include "View/Renderer/OpenGL/Objects/Model.hpp"
#include "View/Renderer/OpenGL/Objects/Texture.hpp"
#include "View/Renderer/OpenGL/Objects/Material.hpp"

/**
 * @class Item
 * @brief An item in the scene. (JUST FOR TESTING NOW)
 */
class Item : public GameObject {
public:
	/**
	 * @brief Construct a new Item object with a model_path, shininess, and
	 * specular intensity.
	 *
	 * @param model_path
	 * @param shininess
	 * @param spec_intensity
	 */
	Item(const std::string& model_path, GLfloat shininess,
	     GLfloat spec_intensity);

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
	 * @brief Adds the draw call to the renderer.
	 */
	void add_draw_call() override;

	/**
	 * @brief The draw call for the item.
	 *
	 * @param shader
	 */
	void draw(std::shared_ptr<Shader> shader) override;

private:
	/// The model of the item.
	Model model_ = {};
	/// The material of the item.
	Reflex::Material material_ = {};
};
