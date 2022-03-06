#include "Camera.hpp"

Camera::Camera()
	: m_position(0.0f), m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
	m_up(0.0f), m_right(0.0f), m_upWorld(glm::vec3(0.0f, 1.0f, 0.0f)), 
	m_yaw(0), m_pitch(0), m_moveSpeed(5.0f), m_turnSpeed(1.0f)
{
	Update();
}

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch, GLfloat moveSpeed, GLfloat turnSpeed)
	: m_position(position), m_front(glm::vec3(0.0f, 0.0f, -1.0f)), 
	m_up(0.0f), m_right(0.0f), m_upWorld(up), m_yaw(yaw), 
	m_pitch(pitch), m_moveSpeed(moveSpeed), m_turnSpeed(turnSpeed)

{
	Update();
}

void Camera::KeyControl(bool* keys, GLfloat deltaTime)
{
	GLfloat velocity = m_moveSpeed * deltaTime;

	// To not move in the y direction, simply don't modify the y in the vectors.
	if (keys[GLFW_KEY_W])
	{
		m_position += m_front * velocity;
	}

	if (keys[GLFW_KEY_S])
	{
		m_position -= m_front * velocity;
	}

	if (keys[GLFW_KEY_A])
	{
		m_position -= m_right * velocity;
	}

	if (keys[GLFW_KEY_D])
	{
		m_position += m_right * velocity;
	}
}

void Camera::MouseControl(GLfloat xOffset, GLfloat yOffset)
{
	xOffset *= m_turnSpeed;
	yOffset *= m_turnSpeed;

	m_yaw += xOffset;
	m_pitch += yOffset;

	m_pitch = glm::clamp(m_pitch, -89.0f, 89.0f);

	Update();
}

glm::mat4 Camera::CalculateViewMatrix()
{
	return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::Update()
{
	m_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front.y = sin(glm::radians(m_pitch));
	m_front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

	m_front = glm::normalize(m_front);

	m_right = glm::normalize(glm::cross(m_front, m_upWorld));
	m_up = glm::normalize(glm::cross(m_right, m_front));
}

glm::vec3 Camera::GetCamPosition() const
{
	return m_position;
}

glm::vec3 Camera::GetCamDirection() const
{
	return glm::normalize(m_front);
}

Camera::~Camera()
{

}
