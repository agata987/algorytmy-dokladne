#include "Algorithm.h"
#include <iostream>
#include "Timer.h"
#include <iomanip>

using namespace std;

void Algorithm::test()
{
	cout << algorytmName << endl;
	int ile;
	float wynik;
	cout << "\n   Ile testow: ";
	cin.clear();
	cin >> ile;

	Timer t;

	t.startCounter();
	for (int i = 0; i < ile; i++)
	{
		run();
	}
	wynik = t.getCounter() / float(ile);

	cout << endl;
	cout <<"   "<<setprecision(10) << wynik <<"	milisekund"<<endl;
}