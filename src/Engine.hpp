#pragma once

#include <SDL.h>
#include <iostream>
#include <glad/glad.h>

// TODO: Singleton pattern, GLSL for shaders
namespace ReflexEngine
{
	class Engine
	{
	public:
		Engine();

		static void Run();

		static void Stop();

		~Engine();

	private:
		

		static SDL_Window* m_window;
		static bool m_isRunning;
	};
}