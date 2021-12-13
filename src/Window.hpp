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

	GLfloat GetXOffset();
	GLfloat GetYOffset();

	bool* GetKeys();

	bool IsShouldClose() const;
	
	void SwapBuffers();

	~Window();

private:
	GLFWwindow* m_mainWindow;

	GLint m_width, m_height;
	GLint m_bufferWidth, m_bufferHeight;

	GLfloat m_xPrev, m_yPrev;
	GLfloat m_xOffset, m_yOffset;

	bool m_isFirstMouse;

	bool m_keys[1024];

	void CreateCallbacks();
	static void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void HandleMouse(GLFWwindow* window, double xPos, double yPos);
};