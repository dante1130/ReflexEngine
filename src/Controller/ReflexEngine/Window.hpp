#pragma once

#include <iostream>

#include <GLFW/glfw3.h>

/**
 * @class Window
 * @brief A window class using GLFW.
 */
class Window {
public:
	/**
	 * @brief Construct a new Window object
	 */
	Window();

	/**
	 * @brief Construct a new Window object
	 *
	 * @param windowWidth
	 * @param windowHeight
	 */
	Window(int windowWidth, int windowHeight);

	/**
	 * @brief Initializes the window.
	 *
	 * @return int
	 */
	int Init();

	/**
	 * @brief Get the Buffer Width.
	 *
	 * @return GLint
	 */
	int GetBufferWidth() const;

	/**
	 * @brief Get the Buffer Height.
	 *
	 * @return GLint
	 */
	int GetBufferHeight() const;

	/**
	 * @brief Get the mouse x offset.
	 *
	 * @return GLdouble
	 */
	double GetXOffset();

	/**
	 * @brief Get the mouse y offset.
	 *
	 * @return GLdouble
	 */
	double GetYOffset();

	/**
	 * @brief Set whether the window should close.
	 *
	 * @param should_close
	 */
	void set_should_close(bool should_close);

	/**
	 * @brief Returns a boolean whether the window should close.
	 *
	 * @return true
	 * @return false
	 */
	bool IsShouldClose() const;

	/**
	 * @brief
	 *
	 */
	void SwapBuffers();

	/**
	 * @brief Returns a pointer to the window.
	 *
	 * @return GLFWwindow*
	 */
	GLFWwindow* get_window() { return m_mainWindow; }

	/**
	 * @brief Destroy the Window object
	 */
	~Window();

private:
	/// The GLFW window.
	GLFWwindow* m_mainWindow;

	/// Dimensions of the window.
	int m_width, m_height;

	/// The buffer dimensions.
	int m_bufferWidth, m_bufferHeight;

	/// The previous mouse position.
	double m_xPrev, m_yPrev;

	/// The offset between the previous and the current mouse position.
	double m_xOffset, m_yOffset;

	/// Check whether if this is the first mouse move.
	bool m_isFirstMouse;

	/**
	 * @brief Create callbacks for the keyboard and mouse events.
	 */
	void CreateCallbacks();

	/**
	 * @brief Keyboard callback.
	 *
	 * @param window
	 * @param key
	 * @param code
	 * @param action
	 * @param mode
	 */
	static void HandleKeys(GLFWwindow* window, int key, int code, int action,
	                       int mode);

	/**
	 * @brief Mouse callback.
	 *
	 * @param window
	 * @param xPos
	 * @param yPos
	 */
	static void HandleMouse(GLFWwindow* window, double xPos, double yPos);
};
