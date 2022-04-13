#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
	Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch,
	       GLfloat moveSpeed, GLfloat turnSpeed);

	/**
	 * @brief The callback for the keyboard input.
	 * @todo Refactor this to not handle keys.
	 * @param keys
	 * @param deltaTime
	 */
	void KeyControl(const bool* keys, GLfloat deltaTime);

	/**
	 * @brief The callback for mouse input.
	 *
	 * @param xOffset
	 * @param yOffset
	 */
	void MouseControl(GLfloat xOffset, GLfloat yOffset);

	/**
	 * @brief Returns the view matrix.
	 *
	 * @return glm::mat4
	 */
	glm::mat4 CalculateViewMatrix();

	/**
	 * @brief Gets a Vector3 of the camera's position.
	 *
	 * @return glm::vec3
	 */
	glm::vec3 GetCamPosition() const;

	/**
	 * @brief Gets a Vector3 of the camera's position.
	 *
	 * @return glm::vec3
	 */
	glm::vec3 GetCamDirection() const;

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
	GLfloat m_yaw;
	/// The camera's pitch.
	GLfloat m_pitch;

	/// The camera's movement speed.
	GLfloat m_moveSpeed;
	/// The camera's turn speed. (sensitivity)
	GLfloat m_turnSpeed;

	/**
	 * @brief Updates the camera.
	 */
	void Update();
};
