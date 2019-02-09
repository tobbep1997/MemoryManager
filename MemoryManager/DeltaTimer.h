#pragma once
#include <chrono>
class DeltaTimer
{
private:
	std::chrono::time_point <std::chrono::steady_clock> preTime;
	std::chrono::time_point <std::chrono::steady_clock> currentTime;
public:
	DeltaTimer();
	~DeltaTimer();
	void Init();
	double GetDeltaTimeInSeconds();
};