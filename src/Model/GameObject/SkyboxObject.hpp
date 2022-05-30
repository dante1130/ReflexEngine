#pragma once

#include <vector>
#include <string>

#include "GameObject.hpp"

enum class SkyboxFaces { RIGHT, LEFT, TOP, BOTTOM, BACK, FRONT };

class SkyboxObject : public GameObject {
public:
	/**
	 * @brief Construct a new Skybox Object
	 */
	SkyboxObject();

	/**
	 * @brief Initializes the skybox object.
	 */
	void init() override;

	/**
	 * @brief Updates the object with delta time.
	 *
	 * @param delta_time The time since the last frame.
	 */
	void update(double delta_time) override {}

	/**
	 * @brief Updates the object with fixed delta time.
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
	void draw(std::shared_ptr<Shader> shader) override {}

	/**
	 * @brief	Saves the object to lua file
	 *
	 * @pre		Object exists
	 * @post	Object saved
	 */
	void save_object() override;

	/**
	 * @brief Set the face of the skybox with a texture path
	 *
	 * @param face
	 * @param texture_path
	 */
	void set_face(SkyboxFaces face, const std::string& texture_path);

private:
	/// The faces of the skybox
	std::vector<std::string> faces_;
};
