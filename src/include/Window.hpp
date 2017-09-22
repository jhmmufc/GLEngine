#ifndef GAME_ENGINE_WINDOW_HPP
#define GAME_ENGINE_WINDOW_HPP

#include <SDL.h>

#include <GL/glew.h>

#include <string>

namespace GameEngine
{
	namespace Rendering
	{
		enum WindowFlags
		{
			NONE = 0x1,
			HIDE = 0x2,
			FULLSCREEN = 0x4,
			BORDERLESS = 0x8
		};

		class Window
		{
		public:
			Window() = default;
			~Window();

			int CreateWindow(const std::string& windowTitle, int screenWidth, int screenHeight, WindowFlags flags, bool enabledVSync = false);

			void SwapBuffer();

			int GetScreenWidth() const
			{
				return m_width;
			}

			int GetScreenHeight() const
			{
				return m_height;
			}

		private:
			int m_width = 0;
			int m_height = 0;

			SDL_Window* m_window = nullptr;
		};
	}
}

#endif
