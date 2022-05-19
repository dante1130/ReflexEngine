#pragma once

#include "GameObject.hpp"
#include "Model/LightData.hpp"

/**
 * @class DirectionalLightObject
 * @brief A directional light game object.
 */
class DirectionalLightObject : public GameObject {
public:
	/**
	 * @brief Construct a new Directional Light Object object
	 *
	 * @param light_data
	 */
	DirectionalLightObject(const DirectionalLightData& light_data);

	/**
	 * @brief Initializes the game object.
	 */
	void init() override {}

	/**
	 * @brief Updates the game object with delta time.
	 *
	 * @param delta_time
	 */
	void update(float delta_time) override {}

	/**
	 * @brief Updates the game object with fixed delta time.
	 *
	 * @param delta_time
	 */
	void fixed_update(float delta_time) override {}

	/**
	 * @brief Adds a draw call to the renderer.
	 */
	void add_draw_call() override;

	/**
	 * @brief The draw call.
	 *
	 * @param shader
	 */
	void draw(std::shared_ptr<Shader> shader) override {}

	/**
	 * @brief	Saves the object to lua file
	 *
	 * @pre		Object exists
	 * @post	Object saved
	 */
	void save_object() override;

private:
	/// The directional light data.
	DirectionalLightData light_data_;
};
