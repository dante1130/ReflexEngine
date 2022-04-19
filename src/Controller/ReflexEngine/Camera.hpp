#pragma once

#include <GLFW/glfw3.h>

#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class Movement { forward, backward, left, right };

/**
 * @class Camera
 * @brief A Euler camera.
 */
class Camera {
public:
	/**
	 * @brief Default constructor.
	 */
	Camera();

	/**
	 * @brief Parameterized constructor.
	 *
	 * @param position
	 * @param up
	 * @param yaw
	 * @param pitch
	 * @param moveSpeed
	 * @param turnSpeed
	 */
	Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch,
	       float moveSpeed, float turnSpeed);

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
	 * @param direction
	 */
	void calculate_direction(Movement direction);

	/**
	 * @brief Moves the perspective by the offset in mouse position.
	 *
	 * @param xOffset
	 * @param yOffset
	 */
	void mouse_move(float xOffset, float yOffset);

	/**
	 * @brief Returns the view matrix.
	 *
	 * @return glm::mat4
	 */
	glm::mat4 calc_view_matrix();

	/**
	 * @brief Set the position.
	 * @param position
	 */
	void set_position(glm::vec3 position);

	/**
	 * @brief Set the move direction.
	 *
	 * @param direction
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
	 * @brief Toggles noclip on and off.
	 */
	void toggle_noclip();

private:
	/// The camera's position.
	glm::vec3 m_position;
	/// The camera's front vector.
	glm::vec3 m_front;
	/// The camera's up vector.
	glm::vec3 m_up;
	/// The camera's right vector.
	glm::vec3 m_right;
	/// The camera's upworld vector.
	glm::vec3 m_upWorld;
	/// The camera's move direction.
	glm::vec3 direction_;

	/// The camera's yaw.
	float m_yaw;
	/// The camera's pitch.
	float m_pitch;

	/// The camera's movement speed.
	float m_moveSpeed;
	/// The camera's turn speed. (sensitivity)
	float m_turnSpeed;

	/// The camera's noclip state.
	bool is_noclip_ = false;

	/**
	 * @brief Updates the camera.
	 */
	void Update();
};
