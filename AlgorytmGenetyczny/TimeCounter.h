#pragma once

#include <chrono>
class TimeCounter
{
public:
	std::chrono::high_resolution_clock::time_point start;
	std::chrono::high_resolution_clock::time_point end;
	TimeCounter();
	~TimeCounter();
	void startTimer();
	void stopTimer();
	long timePassed();
};

