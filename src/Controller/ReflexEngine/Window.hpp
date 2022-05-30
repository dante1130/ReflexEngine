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
	Window() = default;

	/**
	 * @brief Construct a new Window object
	 *
	 * @param window_width The width of the window.
	 * @param window_height The height of the window.
	 */
	Window(int window_width, int window_height);

	/**
	 * @brief Initializes the window.
	 *
	 * @return int
	 */
	bool init();

	/**
	 * @brief Returns a pointer to the window.
	 *
	 * @return GLFWwindow*
	 */
	GLFWwindow* get_window() const;

	/**
	 * @brief Get the aspect ratio of the window.
	 *
	 * @return float
	 */
	float get_ratio() const;

	/**
	 * @brief Get the Buffer Width.
	 *
	 * @return int
	 */
	int get_buffer_width() const;

	/**
	 * @brief Get the Buffer Height.
	 *
	 * @return int
	 */
	int get_buffer_height() const;

	/**
	 * @brief Get the mouse x offset.
	 *
	 * @return double
	 */
	double get_x_offset();

	/**
	 * @brief Get the mouse y offset.
	 *
	 * @return double
	 */
	double get_y_offset();

	/**
	 * @brief Set whether the window should close.
	 *
	 * @param should_close Whether the window should close.
	 */
	void set_should_close(bool should_close);

	/**
	 * @brief Returns a boolean whether the window should close.
	 *
	 * @return bool
	 */
	bool is_should_close() const;

	/**
	 * @brief Updates the window buffer sizes.
	 */
	void update_window_buffer_size();

	/**
	 * @brief Swap the window buffers.
	 */
	void swap_buffers();

	/**
	 * @brief Destroy the Window object
	 */
	~Window();

private:
	/// The GLFW window.
	GLFWwindow* main_window_ = nullptr;

	/// Dimensions of the window.
	int width_ = 0, height_ = 0;

	/// The buffer dimensions.
	int buffer_width_ = 0, buffer_height_ = 0;

	/// The previous mouse position.
	double prev_x_ = 0.0, prev_y_ = 0.0;

	/// The offset between the previous and the current mouse position.
	double offset_x_ = 0.0, offset_y_ = 0.0;

	/// Check whether if this is the first mouse move.
	bool is_first_mouse_ = true;

	/**
	 * @brief Create callbacks for the keyboard and mouse events.
	 */
	void create_callbacks();

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
