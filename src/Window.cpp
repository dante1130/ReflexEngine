#include "Window.h"

Window::Window()
	: m_mainWindow(nullptr), m_width(800), m_height(600), m_bufferWidth(0), m_bufferHeight(0)
{}

Window::Window(GLint windowWidth, GLint windowHeight)
	: m_mainWindow(nullptr), m_width(windowWidth), m_height(windowHeight), m_bufferWidth(0), m_bufferHeight(0)
{}

int Window::Init()
{
	if (!glfwInit())
	{
		std::cout << "GLFW init failed!" << std::endl;
		glfwTerminate();
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	m_mainWindow = glfwCreateWindow(m_width, m_height, "ReflexBullet", NULL, NULL);

	if (!m_mainWindow)
	{
		std::cout << "GLFW window creation failed!" << std::endl;
		glfwDestroyWindow(m_mainWindow);
		glfwTerminate();
		return 1;
	}

	glfwGetFramebufferSize(m_mainWindow, &m_bufferWidth, &m_bufferHeight);

	glfwMakeContextCurrent(m_mainWindow);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, m_bufferWidth, m_bufferHeight);

	return 0;
}

GLint Window::GetBufferWidth() const
{
	return m_bufferWidth;
}

GLint Window::GetBufferHeight() const
{
	return m_bufferHeight;
}

bool Window::IsShouldClose() const
{
	return glfwWindowShouldClose(m_mainWindow);
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(m_mainWindow);
}

Window::~Window()
{
	glfwDestroyWindow(m_mainWindow);
	glfwTerminate();
}