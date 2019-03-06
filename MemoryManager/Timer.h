#pragma once
#include <Windows.h>
#include <stdio.h>
typedef float real32;
typedef double real64;

class Timer
{
public:
	enum TIME_UNIT
	{
		SECONDS = 1,
		MILLISECONDS = 1000,
		MICROSECONDS = 1000000
	};
private:
	LARGE_INTEGER m_StartingTime;
	LARGE_INTEGER m_EndingTime;
	LARGE_INTEGER m_Frequency;
public:

	inline void Init()
	{
		QueryPerformanceFrequency(&m_Frequency);
		QueryPerformanceCounter(&m_StartingTime);
	}
	inline double GetDeltaTimeInSeconds(const TIME_UNIT & timeUnit = MICROSECONDS)
	{
		QueryPerformanceCounter(&m_EndingTime);
		LARGE_INTEGER elapsedMicroseconds;
		elapsedMicroseconds.QuadPart = m_EndingTime.QuadPart - m_StartingTime.QuadPart;
		const double msPerFrame = static_cast<real64>(elapsedMicroseconds.QuadPart);// / static_cast<real64>(m_Frequency.QuadPart);
		m_StartingTime = m_EndingTime;
		return msPerFrame * timeUnit;
	}
};