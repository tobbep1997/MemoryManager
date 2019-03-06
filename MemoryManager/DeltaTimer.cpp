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
	preTime = high_resolution_clock::now();
	currentTime = high_resolution_clock::now();
}

double DeltaTimer::GetDeltaTimeInSeconds()
{
	using namespace std::chrono;

	currentTime = high_resolution_clock::now();
	const double dt = duration_cast<nanoseconds>(currentTime - preTime).count();
	preTime = currentTime;

	return dt;
}