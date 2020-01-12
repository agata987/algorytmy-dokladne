#include "Timer.h"
#include <iostream>

using namespace std;

Timer::Timer()
{
	this->PCFreq = 0.0;
	this->CounterStart = 0.0;
}


Timer::~Timer()
{
}

double Timer::getCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}

void Timer::startCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		cout << "Licznik jest popsuty.";

	PCFreq = double(li.QuadPart) / 1000000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}