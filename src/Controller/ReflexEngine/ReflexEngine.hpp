#pragma once

#include <stack>

#include "Game/Scene.hpp"
#include "View/Renderer/OpenGL/OpenGL.hpp"
#include "Camera.hpp"
#include "Window.hpp"
#include "EngineTime.hpp"

/**
 * @class ReflexEngine
 * @brief The game engine.
 */
class ReflexEngine {
public:
	/// Window class.
	Window window_ = {};

	/// The camera.
	Camera camera_ = {};

	/// The renderer of the engine.
	OpenGL renderer_ = {};

	/// A stack of the current Scene, used to switch between Scenes.
	std::stack<std::shared_ptr<Scene>> scenes_ = {};

	/**
	 * @brief Runs the engine.
	 */
	static void run();

	/**
	 * @brief Get an instance of the engine.
	 *
	 * @return ReflexEngine&
	 */
	static ReflexEngine& get_instance();

	// These are deleted as a singleton pattern is used.
	ReflexEngine(ReflexEngine& other) = delete;
	ReflexEngine(const ReflexEngine& other) = delete;
	void operator=(ReflexEngine&&) = delete;
	void operator=(const ReflexEngine&) = delete;

private:
	/**
	 * @brief The default constructor is private as a singleton pattern is
	 * used, preventing multiple instances.
	 */
	ReflexEngine() = default;
};
