#pragma once

#include <GLFW/glfw3.h>

#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class CameraMovement { forward, backward, left, right };

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
	void move(CameraMovement direction, float delta_time);

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

	/// The camera's yaw.
	float m_yaw;
	/// The camera's pitch.
	float m_pitch;

	/// The camera's movement speed.
	float m_moveSpeed;
	/// The camera's turn speed. (sensitivity)
	float m_turnSpeed;

	bool is_noclip_ = false;

	/**
	 * @brief Updates the camera.
	 */
	void Update();
};
