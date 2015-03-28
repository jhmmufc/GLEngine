#ifndef GAME_ENGINE_TIMING_HPP
#define GAME_ENGINE_TIMING_HPP

namespace GameEngine
{
	namespace Time
	{
		class FPSLimiter
		{
		public:
			FPSLimiter() = default;
			void Initialise(float maxFPS);
			void SetMaxFPS(float maxFPS);

			void Begin();
			float End();
		private:
			void CalculateFPS();

			float m_fps;
			float m_maxFPS;
			float m_frameTime;
			unsigned int m_startTicks;
		};
	}
}

#endif