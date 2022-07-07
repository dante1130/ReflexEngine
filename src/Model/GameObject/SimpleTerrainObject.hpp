#pragma once

#include "GameObject.hpp"
#include "Controller/Terrain/TexturedTerrain.hpp"

class SimpleTerrainObject : public GameObject {
public:
	/**
	 * @brief Initializes the game object.
	 */
	void init() override;

	/**
	 * @brief Updates the game object with delta time.
	 *
	 * @param delta_time The time since the last frame.
	 */
	void update(double delta_time) override {}

	/**
	 * @brief Updates the game object with fixed delta time.
	 *
	 * @param delta_time The time since the last fixed tick.
	 */
	void fixed_update(double delta_time) override {}

	/**
	 * @brief Adds a draw call to the renderer.
	 */
	void add_draw_call() override;

	/**
	 * @brief The draw call.
	 *
	 * @param shader The shader to use.
	 */
	void draw(const Shader& shader) override;

	/**
	 * @brief	Saves the object to lua file
	 *
	 * @pre		Object exists
	 * @post	Object saved
	 */
	void save_object() override;

private:
	TexturedTerrain terrain_;
	std::string texture_name_;
	std::string detailmap_name_;
};