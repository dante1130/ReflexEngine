#pragma once

#include "Model/LightData.hpp"
#include "Model/GameObject/GameObject.hpp"

/**
 * @class PointLightObject
 * @brief A point light game object.
 */
class PointLightObject : public GameObject {
public:
	/**
	 * @brief Construct a new Directional Light Object object
	 *
	 * @param light_data
	 */
	PointLightObject(const PointLightData& light_data);

	/**
	 * @brief Initializes the directional light object.
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
	/// The point light data.
	PointLightData light_data_;
};
