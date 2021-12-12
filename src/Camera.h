#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glfw/glfw3.h>

class Camera
{
public:
	Camera();
	Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch, GLfloat moveSpeed, GLfloat turnSpeed);

	void KeyControl(bool* keys, GLfloat deltaTime);
	void MouseControl(GLfloat xOffset, GLfloat yOffset);

	glm::mat4 CalculateViewMatrix();

	~Camera();

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