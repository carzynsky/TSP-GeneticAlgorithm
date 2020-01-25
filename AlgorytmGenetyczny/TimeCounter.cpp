#include "TimeCounter.h"

TimeCounter::TimeCounter()
{
}


TimeCounter::~TimeCounter()
{
}

void TimeCounter::startTimer()
{
	start = std::chrono::steady_clock::now();
}

void TimeCounter::stopTimer()
{
	end = std::chrono::steady_clock::now();
}

long TimeCounter::timePassed()
{
	return  std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

