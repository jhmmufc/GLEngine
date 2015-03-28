#include "Timing.hpp"

#include <SDL/SDL.h>

namespace GameEngine
{
	namespace Time
	{
		void FPSLimiter::Initialise(float maxFPS)
		{
			SetMaxFPS(maxFPS);
		}

		void FPSLimiter::SetMaxFPS(float maxFPS)
		{
			m_maxFPS = maxFPS;
		}

		void FPSLimiter::Begin()
		{
			m_startTicks = SDL_GetTicks();
		}

		float FPSLimiter::End()
		{
			CalculateFPS();

			float frameTicks = SDL_GetTicks() - m_startTicks;
			//Limit the FPS to the max FPS
			if (1000.0f / m_maxFPS > frameTicks) 
			{
				SDL_Delay((Uint32)(1000.0f / m_maxFPS - frameTicks));
			}

			return m_fps;
		}

		void FPSLimiter::CalculateFPS()
		{
			//The number of frames to average
			static const int NUM_SAMPLES = 10;
			//Stores all the frametimes for each frame that we will average
			static float frameTimes[NUM_SAMPLES];
			//The current frame we are on
			static int currentFrame = 0;
			//the ticks of the previous frame
			static float prevTicks = SDL_GetTicks();

			//Ticks for the current frame
			float currentTicks = SDL_GetTicks();

			//Calculate the number of ticks (ms) for this frame
			m_frameTime = currentTicks - prevTicks;
			frameTimes[currentFrame % NUM_SAMPLES] = m_frameTime;

			//current ticks is now previous ticks
			prevTicks = currentTicks;

			//The number of frames to average
			int count;

			currentFrame++;
			if (currentFrame < NUM_SAMPLES) 
			{
				count = currentFrame;
			}
			else
			{
				count = NUM_SAMPLES;
			}

			//Average all the frame times
			float frameTimeAverage = 0;
			for (int i = 0; i < count; i++)
			{
				frameTimeAverage += frameTimes[i];
			}
			frameTimeAverage /= count;

			//Calculate FPS
			if (frameTimeAverage > 0) 
			{
				m_fps = 1000.0f / frameTimeAverage;
			}
			else 
			{
				m_fps = 60.0f;
			}
		}
	}
}