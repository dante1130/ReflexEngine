#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	Camera();
	Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch,
	       GLfloat moveSpeed, GLfloat turnSpeed);

	void KeyControl(const bool* keys, GLfloat deltaTime);
	void MouseControl(GLfloat xOffset, GLfloat yOffset);

	glm::mat4 CalculateViewMatrix();

	glm::vec3 GetCamPosition() const;
	glm::vec3 GetCamDirection() const;

private:
	glm::vec3 m_position;
	glm::vec3 m_front;
	glm::vec3 m_up;
	glm::vec3 m_right;
	glm::vec3 m_upWorld;

	GLfloat m_yaw;
	GLfloat m_pitch;

	GLfloat m_moveSpeed;
	GLfloat m_turnSpeed;

	void Update();
};
