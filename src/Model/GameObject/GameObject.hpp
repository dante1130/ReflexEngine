#pragma once

#include <glm/glm.hpp>
#include "View/Renderer/OpenGL/Objects/Shader.hpp"

/**
 * @class GameObject
 * @brief An abstract class to represent a game object.
 */
class GameObject {
public:
	/// The position of the game object.
	glm::vec3 position = {0.0f, 0.0f, 0.0f};
	/// The rotation of the game object.
	glm::vec3 rotation = {0.0f, 1.0f, 0.0f};
	/// The scale of the game object.
	glm::vec3 scale = {1.0f, 1.0f, 1.0f};

	/// The angle of rotation.
	float angle = 0.01f;

	/// Whether the game object should be removed.
	bool remove = false;

	/**
	 * @brief Initializes the game object.
	 */
	virtual void init() = 0;

	/**
	 * @brief Updates the game object with delta time.
	 *
	 * @param delta_time The time since the last frame.
	 */
	virtual void update(double delta_time) = 0;

	/**
	 * @brief Updates the game object with fixed delta time.
	 *
	 * @param delta_time The time since the last fixed tick.
	 */
	virtual void fixed_update(double delta_time) = 0;

	/**
	 * @brief Adds a draw call to the renderer.
	 */
	virtual void add_draw_call() = 0;

	/**
	 * @brief The draw call.
	 *
	 * @param shader The shader to use.
	 */
	virtual void draw(std::shared_ptr<Shader> shader) = 0;

	/**
	 * @brief	Saves the object to lua file
	 *
	 * @pre		Object exists
	 * @post	Object saved
	 */
	virtual void save_object() = 0;

	/**
	 * @brief Virtual destructor.
	 */
	virtual ~GameObject() = default;
};
