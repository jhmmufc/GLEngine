#include "InputManager.hpp"

namespace GameEngine
{
	namespace Input
	{
		void InputManager::Reset()
		{
			for (auto& k : m_keyReleased)
			{
				k.second = false;
			}
		}

		void InputManager::Update(const std::vector<SDL_Event>& events)
		{
			Reset();

			for (const auto& ev : events)
			{
				if (ev.type == SDL_KEYDOWN)
				{
					m_keyPressed[ev.key.keysym.sym] = true;
				}

				if (ev.type == SDL_MOUSEBUTTONDOWN)
				{
					m_keyPressed[ev.button.button] = true;
				}

				if (ev.type == SDL_KEYUP)
				{
					m_keyPressed[ev.key.keysym.sym] = false;
					m_keyReleased[ev.key.keysym.sym] = true;
				}

				if (ev.type == SDL_MOUSEBUTTONUP)
				{
					m_keyPressed[ev.button.button] = false;
					m_keyReleased[ev.button.button] = true;
				}

				if (ev.type == SDL_MOUSEMOTION)
				{
					m_mouseCoords = glm::vec2(static_cast<float>(ev.motion.x), static_cast<float>(ev.motion.y));
				}
			}
		}
	}
}