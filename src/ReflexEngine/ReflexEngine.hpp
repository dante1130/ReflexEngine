#pragma once

#include <stack>

#include "Game/Scene.hpp"
#include "Renderer/OpenGL/OpenGL.hpp"
#include "Window.hpp"

class ReflexEngine {
public:
	Window window_ = {};

	OpenGL renderer_ = {};

	std::stack<std::shared_ptr<Scene>> scenes_ = {};

	static void run();

	static ReflexEngine& get_instance();

	ReflexEngine(ReflexEngine& other) = delete;
	ReflexEngine(const ReflexEngine& other) = delete;
	void operator=(ReflexEngine&&) = delete;
	void operator=(const ReflexEngine&) = delete;

private:
	ReflexEngine();
};
