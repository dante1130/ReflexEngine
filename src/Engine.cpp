#include "Engine.hpp"

SDL_Window* ReflexEngine::Engine::m_window;
bool ReflexEngine::Engine::m_isRunning;

ReflexEngine::Engine::Engine()
{
    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

    // Create an application window with the following settings:
    m_window = SDL_CreateWindow(
        "An SDL2 window",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        1280,                               // width, in pixels
        720,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags
    );

    SDL_GL_CreateContext(m_window);

    gladLoadGLLoader(SDL_GL_GetProcAddress);

    glViewport(0, 0, 1280, 720);

    m_isRunning = true;
}

void ReflexEngine::Engine::Run()
{
    SDL_Event event;

    while (m_isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                m_isRunning = false;
                break;

            case SDL_KEYDOWN:
                std::cout << "key pressed" << std::endl;
                break;

            case SDL_MOUSEMOTION:
                std::cout << "mouse moved" << std::endl;
                break;
            }
        }

        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(m_window);
    }
}

void ReflexEngine::Engine::Stop()
{
    m_isRunning = false;
}

ReflexEngine::Engine::~Engine()
{
    // Close and destroy the window
    SDL_DestroyWindow(m_window);

    // Clean up
    SDL_Quit();
}