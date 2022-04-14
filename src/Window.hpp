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
	Window(GLint windowWidth, GLint windowHeight);

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
	GLint GetBufferWidth() const;

	/**
	 * @brief Get the Buffer Height.
	 *
	 * @return GLint
	 */
	GLint GetBufferHeight() const;

	/**
	 * @brief Get the mouse x offset.
	 *
	 * @return GLdouble
	 */
	GLdouble GetXOffset();

	/**
	 * @brief Get the mouse y offset.
	 *
	 * @return GLdouble
	 */
	GLdouble GetYOffset();

	/**
	 * @brief Get the current keys pressed.
	 *
	 * @return const bool* - boolean array
	 */
	const bool* GetKeys() const;

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
	 * @brief Returns a pointer to the window. (wtf?)
	 *
	 * @return GLFWwindow*
	 */
	GLFWwindow* getWindow() { return m_mainWindow; }

	/**
	 * @brief Destroy the Window object
	 */
	~Window();

private:
	/// The GLFW window.
	GLFWwindow* m_mainWindow;

	/// Dimensions of the window.
	GLint m_width, m_height;

	/// The buffer dimensions.
	GLint m_bufferWidth, m_bufferHeight;

	/// The previous mouse position.
	GLdouble m_xPrev, m_yPrev;

	/// The offset between the previous and the current mouse position.
	GLdouble m_xOffset, m_yOffset;

	/// Check whether if this is the first mouse move.
	bool m_isFirstMouse;

	/// Boolean array of keys pressed.
	bool m_keys[1024];

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
