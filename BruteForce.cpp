#include "BruteForce.h"
#include <iostream>
#include <iterator> 

using namespace std;

void BruteForce::run()
{
	najlepszaTrasa = oryginalnaTrasa;
	
	calkowitaOdlegloscNajlepszejTrasy = graph->funkcjaCelu();

	graph->path.pop_back(); // powrot do pierwszego miasta nie potrzebny w permutacjach

	permutacje(0);

	graph->path = oryginalnaTrasa;
}

void BruteForce::printPath()
{
	vector<int>::iterator it;

	for (it = najlepszaTrasa.begin(); it != najlepszaTrasa.end(); it++)
		cout << *it << " ";

	cout << "	koszt drogi: " << calkowitaOdlegloscNajlepszejTrasy << endl;
}

void BruteForce::permutacje(int n)
{
	if (n < graph->getnumberOfCities()-1)
	{
		for (int i = n; i < graph->getnumberOfCities(); i++)
		{
			swap(graph->path[n], graph->path[i]); // zamienia dwa elementy miejscami
			permutacje(n + 1);
			swap(graph->path[n], graph->path[i]); // przywracamy
		}
	}
	else 
	{

		graph->path.push_back(graph->path[0]); // dodanie powrotu do miasta

		if (graph->czyIstniejeSciezkaDlaAsymetrycznych()==true) {

			wynikFunkcjiCelu = graph->funkcjaCelu();

			if (wynikFunkcjiCelu < calkowitaOdlegloscNajlepszejTrasy)
			{
				calkowitaOdlegloscNajlepszejTrasy = wynikFunkcjiCelu;
				najlepszaTrasa = graph->path;
			}
		}
		graph->path.pop_back();		// zabieramy powrot do pierwszego miasta
	}
}