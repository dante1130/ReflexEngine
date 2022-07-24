#include "Window.hpp"

#include "Controller/Input/InputManager.hpp"
#include "Controller/LuaManager.hpp"

Window::Window(int window_width, int window_height)
    : main_window_(nullptr), width_(window_width), height_(window_height) {}

void Window::lua_access() {
	auto& lua = LuaManager::get_instance().get_state();

	auto window_table = lua.create_named_table("Window");

	window_table.set_function("is_fullscreen", &Window::is_fullscreen, this);
	window_table.set_function("is_cursor_visible", &Window::is_cursor_visible,
	                          this);
	window_table.set_function("get_width", &Window::get_buffer_width, this);
	window_table.set_function("get_height", &Window::get_buffer_height, this);
	window_table.set_function("get_ratio", &Window::get_ratio, this);
	window_table.set_function("set_fullscreen", &Window::set_fullscreen, this);
	window_table.set_function("set_cursor_visible", &Window::set_cursor_visible,
	                          this);
	window_table.set_function("set_window_size", &Window::set_window_size,
	                          this);
}

bool Window::init() {
	if (!glfwInit()) {
		std::cout << "GLFW init failed!" << std::endl;
		glfwTerminate();
		return false;
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
	glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);

	if (width_ == 0 || height_ == 0) {
		width_ = mode->width;
		height_ = mode->height;
	}

	main_window_ =
	    glfwCreateWindow(width_, height_, "ReflexBullet", nullptr, nullptr);

	if (!main_window_) {
		std::cout << "GLFW window creation failed!" << std::endl;
		glfwDestroyWindow(main_window_);
		glfwTerminate();
		return false;
	}

	glfwGetFramebufferSize(main_window_, &buffer_width_, &buffer_height_);

	glfwMakeContextCurrent(main_window_);

	glfwSwapInterval(0);

	create_callbacks();
	glfwSetInputMode(main_window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetWindowUserPointer(main_window_, this);

	return true;
}

GLFWwindow* Window::get_window() const { return main_window_; }

void Window::create_callbacks() {
	glfwSetCursorPosCallback(main_window_, Window::HandleMouse);
}

void Window::HandleMouse(GLFWwindow* window, double xPos, double yPos) {
	Window* currWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (currWindow->is_first_mouse_) {
		currWindow->prev_x_ = xPos;
		currWindow->prev_y_ = yPos;
		currWindow->is_first_mouse_ = false;
	}

	currWindow->offset_x_ = xPos - currWindow->prev_x_;
	currWindow->offset_y_ = currWindow->prev_y_ - yPos;

	currWindow->prev_x_ = xPos;
	currWindow->prev_y_ = yPos;
}

float Window::get_ratio() const {
	return static_cast<float>(buffer_width_) /
	       static_cast<float>(buffer_height_);
}

int Window::get_buffer_width() const { return buffer_width_; }

int Window::get_buffer_height() const { return buffer_height_; }

double Window::get_x_offset() {
	GLdouble offset = offset_x_;
	offset_x_ = 0.0;

	return offset;
}

double Window::get_y_offset() {
	GLdouble offset = offset_y_;
	offset_y_ = 0.0;

	return offset;
}

void Window::set_fullscreen(bool fullscreen) {
	is_fullscreen_ = fullscreen;

	if (is_fullscreen_) {
		glfwSetWindowMonitor(main_window_, glfwGetPrimaryMonitor(), 0, 0,
		                     width_, height_, 0);
	} else {
		glfwSetWindowMonitor(main_window_, nullptr, 0, 0, width_, height_, 0);
	}
}

void Window::set_window_size(int width, int height) {
	width_ = width;
	height_ = height;
	glfwSetWindowSize(main_window_, width, height);
	update_window_buffer_size();
}

void Window::set_cursor_visible(bool visible) {
	is_cursor_visible_ = visible;

	if (is_cursor_visible_) {
		glfwSetInputMode(main_window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	} else {
		glfwSetInputMode(main_window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}

void Window::set_should_close(bool should_close) {
	glfwSetWindowShouldClose(main_window_, should_close);
}

bool Window::is_cursor_visible() const { return is_cursor_visible_; }

bool Window::is_should_close() const {
	return glfwWindowShouldClose(main_window_);
}

bool Window::is_fullscreen() const { return is_fullscreen_; }

void Window::update_window_buffer_size() {
	glfwGetFramebufferSize(main_window_, &buffer_width_, &buffer_height_);
}

void Window::swap_buffers() { glfwSwapBuffers(main_window_); }

Window::~Window() {
	glfwDestroyWindow(main_window_);
	glfwTerminate();
}
