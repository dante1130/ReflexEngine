#include "Camera.hpp"

Camera::Camera()
    : m_position(0.0f),
      m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
      m_up(0.0f),
      m_right(0.0f),
      m_upWorld(glm::vec3(0.0f, 1.0f, 0.0f)),
      m_yaw(0),
      m_pitch(0),
      m_moveSpeed(5.0f),
      m_turnSpeed(1.0f) {
	Update();
}

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch,
               GLfloat moveSpeed, GLfloat turnSpeed)
    : m_position(position),
      m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
      m_up(0.0f),
      m_right(0.0f),
      m_upWorld(up),
      m_yaw(yaw),
      m_pitch(pitch),
      m_moveSpeed(moveSpeed),
      m_turnSpeed(turnSpeed)

{
	Update();
}

void Camera::move(CameraMovement direction, GLfloat delta_time) {
	GLfloat velocity = m_moveSpeed * delta_time;

	glm::vec3 front;
	glm::vec3 right;

	if (is_noclip_) {
		front = m_front;
		right = m_right;
	} else {
		front = glm::normalize(glm::vec3(m_front.x, 0.0f, m_front.z));
		right = glm::normalize(glm::vec3(m_right.x, 0.0f, m_right.z));
	}

	switch (direction) {
		case CameraMovement::forward:
			m_position += front * velocity;
			break;
		case CameraMovement::backward:
			m_position -= front * velocity;
			break;
		case CameraMovement::left:
			m_position -= right * velocity;
			break;
		case CameraMovement::right:
			m_position += right * velocity;
			break;
	}
}

void Camera::mouse_move(GLfloat xOffset, GLfloat yOffset) {
	xOffset *= m_turnSpeed;
	yOffset *= m_turnSpeed;

	m_yaw += xOffset;
	m_pitch += yOffset;

	m_pitch = glm::clamp(m_pitch, -89.0f, 89.0f);

	Update();
}

glm::mat4 Camera::calc_view_matrix() {
	return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::Update() {
	m_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front.y = sin(glm::radians(m_pitch));
	m_front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

	m_front = glm::normalize(m_front);

	m_right = glm::normalize(glm::cross(m_front, m_upWorld));
	m_up = glm::normalize(glm::cross(m_right, m_front));
}

glm::vec3 Camera::get_position() const { return m_position; }

glm::vec3 Camera::get_direction() const { return glm::normalize(m_front); }

void Camera::toggle_noclip() { is_noclip_ = !is_noclip_; }
