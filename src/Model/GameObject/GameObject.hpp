#pragma once

#include <glm/glm.hpp>
#include "Shader.hpp"

/**
 * @class GameObject
 * @brief An abstract class to represent a game object.
 */
class GameObject {
public:
	struct {
		/// The position of the game object.
		glm::vec3 position = {0, 0, 0};
		/// The rotation of the game object.
		glm::vec3 rotation = {0, 1, 0};
		/// The scale of the game object.
		glm::vec3 scale = {1, 1, 1};
		float angle = 0;
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
	 * @brief Virtual destructor.
	 */
	virtual ~GameObject() = default;
};
