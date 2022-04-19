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

void Camera::move(Movement movement, GLfloat delta_time) {
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

	switch (movement) {
		case Movement::forward:
			m_position += front * velocity;
			break;
		case Movement::backward:
			m_position -= front * velocity;
			break;
		case Movement::left:
			m_position -= right * velocity;
			break;
		case Movement::right:
			m_position += right * velocity;
			break;
	}
}

void Camera::calculate_direction(Movement movement) {
	glm::vec3 front;
	glm::vec3 right;

	if (is_noclip_) {
		front = m_front;
		right = m_right;
	} else {
		front = glm::normalize(glm::vec3(m_front.x, 0.0f, m_front.z));
		right = glm::normalize(glm::vec3(m_right.x, 0.0f, m_right.z));
	}

	switch (movement) {
		case Movement::forward:
			direction_ += front;
			break;
		case Movement::backward:
			direction_ -= front;
			break;
		case Movement::left:
			direction_ -= right;
			break;
		case Movement::right:
			direction_ += right;
			break;
		default:
			direction_ = glm::vec3(0.0f, 0.0f, 0.0f);
			break;
	}

	direction_ = glm::normalize(direction_);
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

void Camera::set_position(glm::vec3 position) { m_position = position; }

void Camera::set_move_direction(glm::vec3 direction) { direction_ = direction; }

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

glm::vec3 Camera::get_move_direction() const { return direction_; }

void Camera::toggle_noclip() { is_noclip_ = !is_noclip_; }
