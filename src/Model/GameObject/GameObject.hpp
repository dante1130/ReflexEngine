#pragma once

#include <glm/glm.hpp>
#include "View/Renderer/OpenGL/Objects/Shader.hpp"

/**
 * @class GameObject
 * @brief An abstract class to represent a game object.
 */
class GameObject {
public:
	struct {
		/// The position of the game object.
		glm::vec3 position = {0.0f, 0.0f, 0.0f};
		/// The rotation of the game object.
		glm::vec3 rotation = {0.0f, 1.0f, 0.0f};
		/// The scale of the game object.
		glm::vec3 scale = {1.0f, 1.0f, 1.0f};
		float angle = 0.01;
	};

	/**
	 * @brief Initializes the game object.
	 */
	virtual void init() = 0;

	/**
	 * @brief Updates the game object with delta time.
	 *
	 * @param delta_time
	 */
	virtual void update(float delta_time) = 0;

	/**
	 * @brief Adds a draw call to the renderer.
	 */
	virtual void add_draw_call() = 0;

	/**
	 * @brief The draw call.
	 *
	 * @param shader
	 */
	virtual void draw(std::shared_ptr<Shader> shader) = 0;

	/**
	 * @brief	Saves the object to lau file
	 * @param	No param
	 * @return	Void
	 *
	 * @pre		Object exists
	 * @post	Object saved
	 */
	virtual void saveObject() = 0;

	/**
	 * @brief Virtual destructor.
	 */
	virtual ~GameObject() = default;
};
