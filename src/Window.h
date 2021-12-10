#pragma once

#include <iostream>

#include <glad/glad.h>
#include <glfw/glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);

	int Init();

	GLint GetBufferWidth() const;
	GLint GetBufferHeight() const;

	bool IsShouldClose() const;

	void SwapBuffers();

	~Window();

private:
	GLFWwindow* m_mainWindow;

	GLint m_width, m_height;
	GLint m_bufferWidth, m_bufferHeight;
};