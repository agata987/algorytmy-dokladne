#pragma once
#include <Windows.h>

class Timer
{
private:
	double PCFreq;
	__int64 CounterStart;
public:
	Timer();
	~Timer();
	void startCounter();        // zlicza liczbe cykli zegara (przechowuje je w polu CounterStart)
	double getCounter();        // zwraca liczbe milisekund od czasu ostatniego wywolania funkcji startCounter()
};

