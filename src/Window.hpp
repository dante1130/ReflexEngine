#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);

	int Init();

	GLint GetBufferWidth() const;
	GLint GetBufferHeight() const;

	GLdouble GetXOffset();
	GLdouble GetYOffset();

	bool* GetKeys();

	bool IsShouldClose() const;
	
	void SwapBuffers();

	GLFWwindow* getWindow() { return m_mainWindow; }

	~Window();

private:
	GLFWwindow* m_mainWindow;

	GLint m_width, m_height;
	GLint m_bufferWidth, m_bufferHeight;

	GLdouble m_xPrev, m_yPrev;
	GLdouble m_xOffset, m_yOffset;

	bool m_isFirstMouse;

	bool m_keys[1024];

	void CreateCallbacks();
	static void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void HandleMouse(GLFWwindow* window, double xPos, double yPos);
};
