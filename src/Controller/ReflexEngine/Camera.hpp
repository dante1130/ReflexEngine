#pragma once

#include <GLFW/glfw3.h>

#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/**
 * @enum Movement
 * @brief Enum for the different directions.
 */
enum class Movement { forward, backward, left, right };

/**
 * @class Camera
 * @brief A Euler camera.
 */
class Camera {
public:
	/**
	 * @brief	Provides lua access to basic camera variables
	 */
	void lua_access();

	/**
	 * @brief Default constructor.
	 */
	Camera();

	/**
	 * @brief Parameterized constructor.
	 *
	 * @param position The position of the camera.
	 * @param up The up vector of the camera.
	 * @param yaw The yaw of the camera.
	 * @param pitch The pitch of the camera.
	 * @param move_speed The movement speed of the camera.
	 * @param turn_speed The turn speed of the camera.
	 */
	Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch,
	       float move_speed, float turn_speed);

	/**
	 * @brief Moves the camera position in the specified direction.
	 *
	 * @param direction
	 * @param delta_time
	 */
	void move(Movement direction, float delta_time);

	/**
	 * @brief Calculates the direction of where the camera is moving.
	 *
	 * @param direction The direction of movement.
	 */
	void calculate_direction(Movement direction);

	/**
	 * @brief Moves the perspective by the offset in mouse position.
	 *
	 * @param x_offset The x offset.
	 * @param y_offset The y offset.
	 */
	void mouse_move(float x_offset, float y_offset);

	/**
	 * @brief Returns the view matrix.
	 *
	 * @return glm::mat4
	 */
	glm::mat4 calc_view_matrix();

	/**
	 * @brief Set the position.
	 * @param position The position to set the camera.
	 */
	void set_position(glm::vec3 position);

	/**
	 * @brief Set the move direction.
	 *
	 * @param direction The move direction vector.
	 */
	void set_move_direction(glm::vec3 direction);

	/**
	 * @brief Gets a Vector3 of the camera's position.
	 *
	 * @return glm::vec3
	 */
	glm::vec3 get_position() const;

	/**
	 * @brief Gets a Vector3 of the camera's position.
	 *
	 * @return glm::vec3
	 */
	glm::vec3 get_direction() const;

	/**
	 * @brief Get the move direction
	 *
	 * @return glm::vec3
	 */
	glm::vec3 get_move_direction() const;

	/**
	 * @brief Get the up vector in the world.
	 *
	 * @return glm::vec3
	 */
	glm::vec3 get_up_world() const;

	/**
	 * @brief Toggles noclip on and off.
	 */
	void toggle_noclip();

private:
	/// The camera's position.
	glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f);
	/// The camera's front vector.
	glm::vec3 front_ = glm::vec3(0.0f, 0.0f, -1.0f);
	/// The camera's up vector.
	glm::vec3 up_ = glm::vec3(0.0f, 1.0f, 0.0f);
	/// The camera's right vector.
	glm::vec3 right_ = glm::vec3(1.0f, 0.0f, 0.0f);
	/// The camera's upworld vector.
	glm::vec3 up_world_ = glm::vec3(0.0f, 1.0f, 0.0f);
	/// The camera's move direction.
	glm::vec3 direction_ = glm::vec3(0.0f, 0.0f, -1.0f);

	/// The camera's yaw.
	float yaw_ = 0.0f;
	/// The camera's pitch.
	float pitch_ = 0.0f;

	/// The camera's movement speed.
	float move_speed_ = 5.0f;
	/// The camera's turn speed. (sensitivity)
	float turn_speed_ = 1.0f;

	/// The camera's noclip state.
	bool is_noclip_ = false;

	/**
	 * @brief Updates the camera.
	 */
	void Update();
};
