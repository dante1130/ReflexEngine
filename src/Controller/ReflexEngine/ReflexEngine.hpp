#pragma once

#include "View/Renderer/OpenGL/OpenGL.hpp"

#include "SceneManager.hpp"
#include "Camera.hpp"
#include "EngineTime.hpp"
#include "Window.hpp"

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
	/// The scene manager.
	SceneManager scene_manager_ = {};

	/**
	 * @brief Exposes all the engine components to lua.
	 */
	void lua_access();

	/**
	 * @brief Loads default resources for the ResourceManager.
	 */
	static void load_default_resources();

	/**
	 * @brief The default constructor is private as a singleton pattern is
	 * used, preventing multiple instances.
	 */
	ReflexEngine() = default;
};
