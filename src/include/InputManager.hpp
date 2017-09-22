#ifndef GAME_ENGINE_INPUT_MANAGER_HPP
#define GAME_ENGINE_INPUT_MANAGER_HPP

#include <unordered_map>
#include <vector>

#include <glm/glm.hpp>

#include <SDL.h>

namespace GameEngine
{
	namespace Input
	{
		class InputManager
		{
		public:
			void Update(const std::vector<SDL_Event>& events);

			inline const glm::vec2& GetMouseCoords() const
			{
				return m_mouseCoords;
			}

			inline bool IsKeyReleased(unsigned int key) const
			{
				auto it = m_keyReleased.find(key);

				if (it != m_keyReleased.end())
				{
					return it->second;
				}

				return false;
			}

			inline bool IsKeyPressed(unsigned int key) const
			{
				auto it = m_keyPressed.find(key);

				if (it != m_keyPressed.end())
				{
					return it->second;
				}

				return false;
			}

		private:
			void Reset();

			glm::vec2 m_mouseCoords = glm::vec2(0);

			std::unordered_map<unsigned int, bool> m_keyPressed;
			std::unordered_map<unsigned int, bool> m_keyReleased;
		};
	}
}

#endif
