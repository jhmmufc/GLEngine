#include "Window.hpp"
#include "Private/Utility.hpp"

#include <iostream>

namespace GameEngine
{
	namespace Rendering
	{
		Window::~Window()
		{
			// Destroy our window handle when game closes
			SDL_DestroyWindow(m_window);
		}

		int Window::CreateWindow(const std::string& windowTitle, int screenWidth, int screenHeight, WindowFlags flags, bool enabledVSync)
		{
			uint32_t useFlags = SDL_WINDOW_OPENGL;

			bool checkFlags = !(flags & NONE);

			if (checkFlags)
			{
				if (flags & HIDE)
				{
					useFlags |= SDL_WINDOW_HIDDEN;
				}
				else if (flags & FULLSCREEN)
				{
					useFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
				}
				else if (flags & BORDERLESS)
				{
					useFlags |= SDL_WINDOW_BORDERLESS;
				}
			}

			// Create our SDL window
			m_window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, useFlags);

			// Ensure that the window has been created
			if (!m_window)
			{
				//Private::Error::FatalError("SDL window could not be created!");
			}

			// Retrieve a openGL context
			auto context = SDL_GL_CreateContext(m_window);

			// Ensure we have a GL context
			if (!context)
			{
				//Private::Error::FatalError("SDL GL Context could not be created!");
			}

			// Initialse GLEW
			glewExperimental = true;
			auto success = glewInit();

			// ensure glew has been initialsed correctly
			if (success != GLEW_OK)
			{
				//Private::Error::FatalError("Could not initialse GLEW");
			}

			// Get the openGL version
			std::cout << "*** " << glGetString(GL_VERSION) << " ***" << std::endl;

			// The colour we wish to clear the screen to
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

			// Turns v sync on to prevent screen tear
			if (enabledVSync)
			{
				SDL_GL_SetSwapInterval(1);
			}
			else
			{
				SDL_GL_SetSwapInterval(0);
			}

			// Enable alpha blending
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			return 0;
		}

		void Window::SwapBuffer()
		{
			SDL_GL_SwapWindow(m_window);
		}
	}
}
