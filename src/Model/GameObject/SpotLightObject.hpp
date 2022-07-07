#pragma once

#include "Model/LightData.hpp"
#include "Model/GameObject/GameObject.hpp"

/**
 * @class SpotLightObject
 * @brief A spot light game object.
 */
class SpotLightObject : public GameObject {
public:
	/**
	 * @brief Construct a new Directional Light Object object
	 *
	 * @param light_data The light data.
	 */
	SpotLightObject(const SpotLightData& light_data);

	/**
	 * @brief Initializes the game object.
	 */
	void init() override;

	/**
	 * @brief Updates the game object with delta time.
	 *
	 * @param delta_time The time since the last frame.
	 */
	void update(double delta_time) override;

	/**
	 * @brief Updates the game object with fixed delta time.
	 *
	 * @param delta_time The time since the last fixed tick.
	 */
	void fixed_update(double delta_time) override {}

	/**
	 * @brief Adds a draw call to the renderer.
	 */
	void add_draw_call() override {}

	/**
	 * @brief The draw call.
	 *
	 * @param shader The shader to use.
	 */
	void draw(const Shader& shader) override {}

	/**
	 * @brief	Saves the object to lua file
	 *
	 * @pre		Object exists
	 * @post	Object saved
	 */
	void save_object() override;

private:
	/// The spot light data.
	SpotLightData light_data_;

	/// The light id in the light manager.
	size_t light_id_ = 0;
};