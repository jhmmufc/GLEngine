#ifndef GAME_ENGINE_CLOCK_HPP
#define GAME_ENGINE_CLOCK_HPP

#include <chrono>

#include "Time.hpp"

namespace GameEngine
{
	namespace Timing
	{
		class Clock
		{
		public:
			Clock::Clock() = default;

			Time GetElapsedTime() const;

			Time Restart();

		private:
			std::chrono::system_clock::time_point m_startTime = GetCurrentTime();

			std::chrono::system_clock::time_point GetCurrentTime() const;
		};
	}
}

#endif