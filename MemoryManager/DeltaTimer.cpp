#include "DeltaTimer.h"

DeltaTimer::DeltaTimer()
{
}


DeltaTimer::~DeltaTimer()
{
}

void DeltaTimer::Init()
{
	using namespace std::chrono;
	preTime = steady_clock::now();
	currentTime = steady_clock::now();
}

double DeltaTimer::GetDeltaTimeInSeconds()
{
	using namespace std::chrono;

	currentTime = steady_clock::now();
	const double dt = duration_cast<nanoseconds>(currentTime - preTime).count() / 1000000000.0f;
	preTime = currentTime;

	return dt;
}