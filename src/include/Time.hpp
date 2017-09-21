#ifndef GAME_ENGINE_TIME_HPP
#define GAME_ENGINE_TIME_HPP

#include <stdint.h>

namespace GameEngine
{
	namespace Timing
	{
		class Time
		{
		public:
			Time() = default;

			float AsSeconds() const;
			int32_t AsMilliseconds() const;
			int64_t AsMicroseconds() const;

			static const Time Zero;
		private:
			friend Time Seconds(float);
			friend Time Milliseconds(int32_t);
			friend Time Microseconds(int64_t);

			explicit Time(int64_t microseconds);

			int64_t m_microseconds = 0;
		};

		Time Seconds(float amount);
		Time Milliseconds(int32_t amount);
		Time Microseconds(int64_t amount);
		bool operator ==(Time left, Time right);
		bool operator !=(Time left, Time right);
		bool operator <(Time left, Time right);
		bool operator >(Time left, Time right);
		bool operator <=(Time left, Time right);
		bool operator >=(Time left, Time right);
		Time operator -(Time right);
		Time operator +(Time left, Time right);
		Time& operator +=(Time& left, Time right);
		Time operator -(Time left, Time right);
		Time& operator -=(Time& left, Time right);
		Time operator *(Time left, float right);
		Time operator *(Time left, int64_t right);
		Time operator *(float left, Time right);
		Time operator *(int64_t left, Time right);
		Time& operator *=(Time& left, float right);
		Time& operator *=(Time& left, int64_t right);
		Time operator /(Time left, float right);
		Time operator /(Time left, int64_t right);
		Time& operator /=(Time& left, float right);
		Time& operator /=(Time& left, int64_t right);
		float operator /(Time left, Time right);
		Time operator %(Time left, Time right);
		Time& operator %=(Time& left, Time right);
	}
}

#endif
