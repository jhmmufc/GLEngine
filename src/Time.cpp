#include "Time.hpp"

namespace GameEngine
{
	namespace Timing
	{
		const Time Time::Zero;

		float Time::AsSeconds() const
		{
			return m_microseconds / 1000000.f;
		}

		int32_t Time::AsMilliseconds() const
		{
			return static_cast<int32_t>(m_microseconds / 1000);
		}

		int64_t Time::AsMicroseconds() const
		{
			return m_microseconds;
		}

		Time::Time(int64_t microseconds) :
			m_microseconds(microseconds)
		{
		}

		Time Seconds(float amount)
		{
			return Time(static_cast<int64_t>(amount * 1000000));
		}

		Time Milliseconds(int32_t amount)
		{
			return Time(static_cast<int64_t>(amount)* 1000);
		}

		Time Microseconds(int64_t amount)
		{
			return Time(amount);
		}

		bool operator ==(Time left, Time right)
		{
			return left.AsMicroseconds() == right.AsMicroseconds();
		}

		bool operator !=(Time left, Time right)
		{
			return left.AsMicroseconds() != right.AsMicroseconds();
		}

		bool operator <(Time left, Time right)
		{
			return left.AsMicroseconds() < right.AsMicroseconds();
		}

		bool operator >(Time left, Time right)
		{
			return left.AsMicroseconds() > right.AsMicroseconds();
		}

		bool operator <=(Time left, Time right)
		{
			return left.AsMicroseconds() <= right.AsMicroseconds();
		}

		bool operator >=(Time left, Time right)
		{
			return left.AsMicroseconds() >= right.AsMicroseconds();
		}

		Time operator -(Time right)
		{
			return Microseconds(-right.AsMicroseconds());
		}

		Time operator +(Time left, Time right)
		{
			return Microseconds(left.AsMicroseconds() + right.AsMicroseconds());
		}

		Time& operator +=(Time& left, Time right)
		{
			return left = left + right;
		}

		Time operator -(Time left, Time right)
		{
			return Microseconds(left.AsMicroseconds() - right.AsMicroseconds());
		}

		Time& operator -=(Time& left, Time right)
		{
			return left = left - right;
		}

		Time operator *(Time left, float right)
		{
			return Seconds(left.AsSeconds() * right);
		}

		Time operator *(Time left, int64_t right)
		{
			return Microseconds(left.AsMicroseconds() * right);
		}

		Time operator *(float left, Time right)
		{
			return right * left;
		}

		Time operator *(int64_t left, Time right)
		{
			return right * left;
		}

		Time& operator *=(Time& left, float right)
		{
			return left = left * right;
		}

		Time& operator *=(Time& left, int64_t right)
		{
			return left = left * right;
		}

		Time operator /(Time left, float right)
		{
			return Seconds(left.AsSeconds() / right);
		}

		Time operator /(Time left, int64_t right)
		{
			return Microseconds(left.AsMicroseconds() / right);
		}

		Time& operator /=(Time& left, float right)
		{
			return left = left / right;
		}

		Time& operator /=(Time& left, int64_t right)
		{
			return left = left / right;
		}

		float operator /(Time left, Time right)
		{
			return left.AsSeconds() / right.AsSeconds();
		}

		Time operator %(Time left, Time right)
		{
			return Microseconds(left.AsMicroseconds() % right.AsMicroseconds());
		}

		Time& operator %=(Time& left, Time right)
		{
			return left = left % right;
		}
	}
}
