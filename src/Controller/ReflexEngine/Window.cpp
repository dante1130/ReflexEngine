#include "Window.hpp"

Window::Window()
    : m_mainWindow(nullptr),
      m_width(0),
      m_height(0),
      m_bufferWidth(0),
      m_bufferHeight(0),
      m_xPrev(0),
      m_yPrev(0),
      m_xOffset(0),
      m_yOffset(0),
      m_isFirstMouse(false)

{
	std::fill(m_keys, m_keys + 1024, false);
}

Window::Window(int windowWidth, int windowHeight)
    : m_mainWindow(nullptr),
      m_width(windowWidth),
      m_height(windowHeight),
      m_bufferWidth(0),
      m_bufferHeight(0),
      m_xPrev(0),
      m_yPrev(0),
      m_xOffset(0),
      m_yOffset(0),
      m_isFirstMouse(false) {
	std::fill(m_keys, m_keys + 1024, false);
}

int Window::Init() {
	if (!glfwInit()) {
		std::cout << "GLFW init failed!" << std::endl;
		glfwTerminate();
		return 1;
	}

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();

	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	if (m_width == 0 || m_height == 0) {
		m_width = mode->width;
		m_height = mode->height;
	}

	m_mainWindow =
	    glfwCreateWindow(m_width, m_height, "ReflexBullet", nullptr, nullptr);

	if (!m_mainWindow) {
		std::cout << "GLFW window creation failed!" << std::endl;
		glfwDestroyWindow(m_mainWindow);
		glfwTerminate();
		return 1;
	}

	glfwGetFramebufferSize(m_mainWindow, &m_bufferWidth, &m_bufferHeight);

	glfwMakeContextCurrent(m_mainWindow);

	glfwSwapInterval(0);

	CreateCallbacks();
	glfwSetInputMode(m_mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetWindowUserPointer(m_mainWindow, this);

	return 0;
}

void Window::CreateCallbacks() {
	glfwSetKeyCallback(m_mainWindow, Window::HandleKeys);
	glfwSetCursorPosCallback(m_mainWindow, Window::HandleMouse);
}

void Window::HandleKeys(GLFWwindow* window, int key, int code, int action,
                        int mode) {
	Window* currWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key <= 0 && key >= 1024) return;

	if (action == GLFW_PRESS)
		currWindow->m_keys[key] = true;
	else if (action == GLFW_RELEASE)
		currWindow->m_keys[key] = false;
}

void Window::HandleMouse(GLFWwindow* window, double xPos, double yPos) {
	Window* currWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (currWindow->m_isFirstMouse) {
		currWindow->m_xPrev = xPos;
		currWindow->m_yPrev = yPos;
		currWindow->m_isFirstMouse = false;
	}

	currWindow->m_xOffset = xPos - currWindow->m_xPrev;
	currWindow->m_yOffset = currWindow->m_yPrev - yPos;

	currWindow->m_xPrev = xPos;
	currWindow->m_yPrev = yPos;
}

int Window::GetBufferWidth() const { return m_bufferWidth; }

int Window::GetBufferHeight() const { return m_bufferHeight; }

double Window::GetXOffset() {
	GLdouble offset = m_xOffset;
	m_xOffset = 0.0;

	return offset;
}

double Window::GetYOffset() {
	GLdouble offset = m_yOffset;
	m_yOffset = 0.0;

	return offset;
}

const bool* Window::GetKeys() const { return m_keys; }

bool Window::IsShouldClose() const {
	return glfwWindowShouldClose(m_mainWindow);
}

void Window::SwapBuffers() { glfwSwapBuffers(m_mainWindow); }

Window::~Window() {
	glfwDestroyWindow(m_mainWindow);
	glfwTerminate();
}
