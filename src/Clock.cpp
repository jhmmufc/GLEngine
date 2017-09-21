#include "Clock.hpp"
#include "Utility.hpp"

namespace GameEngine
{
	namespace Timing
	{
		Time Clock::GetElapsedTime() const
		{
			auto now = GetCurrentTime();

			auto elapsed = Microseconds(std::chrono::duration_cast<std::chrono::microseconds>(now - m_startTime).count());

			return elapsed;
		}

		Time Clock::Restart()
		{
			auto now = GetCurrentTime();

			auto elapsed = Microseconds(std::chrono::duration_cast<std::chrono::microseconds>(now - m_startTime).count());

			m_startTime = now;

			return elapsed;
		}

		std::chrono::system_clock::time_point Clock::GetCurrentTime() const
		{
			return std::chrono::system_clock::now();
		}
	}
}