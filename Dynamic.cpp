#include "Dynamic.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void Dynamic::run()
{

	vector<vector<int>> cities;

	vector<int> row;

	for (int i = 0; i < graph->getnumberOfCities(); i++)
	{
		row.clear();
		for (int j = 0; j < graph->getnumberOfCities(); j++)
		{
			row.push_back(graph->getWeight(i, j));
			
		}

		cities.push_back(row);
	}
	
	// tu beda sie tworzyc dlugosci sciezek od wierzcholka nr 0, przechowujemy tyle roznych dlugosci sciezek ile jest miast -> n*2^n
	vector<vector<int>> state(cities.size());
	for (auto& neighbors : state)
		neighbors = vector<int>((1 << cities.size()) - 1, INT_MAX);  
	// "tablice" - wektor wektorow wypelniamy INT_MAX, co oznacza ze nie odwiedzilismy
	// oprocz wierzcholka nr 0 - dlatego jest -1 , czyli mamy max max max ... 0

	// wierzcholek startowy na 0 i odwiedzone miasto to miasto pierwsze
	koszt = rekurencja(cities, 0, 1, state);
}

void Dynamic::printPath()
{
	cout << "koszt drogi: " << koszt << endl;;
}

// visited - wektor z przesunieciem bitowym
int Dynamic::rekurencja(const vector<vector<int>>& cities, int pos, int visited, vector<vector<int>>& state)
{
	// jezeli odwiedzone wszystkie miasta czyli bit ostatniego miasa to 1
	if (visited == ((1 << cities.size()) - 1))
	{
		return cities[pos][0]; // wracamy do miasta poczatkowego
	}
	

	// jezeli mamy juz dlugosc sciezki do tego miasta to ja zwracamy
	if (state[pos][visited] != INT_MAX)
		return state[pos][visited];

		for (int i = 0; i < cities.size(); ++i)
		{
			// nie mozemy odwiedzic samych siebie & pomijamy jezeli juz odwiedzilismy miasto (jezeli wychodzi nam 1 to true)
			// visited jest "przesuwane" w ponownym wywolaniu rekurencji - visited sa bitowo miasta odwiedzone, | <- OR
			if (i == pos || (visited & (1 << i)))
				continue;

			// wywolujemy rekurencje dla nast miast, modyfikujemy odpowiednio wektor visited
			int distance_all = cities[pos][i] + rekurencja(cities, i, visited | (1 << i), state);
			// jezeli dystans do danego miasta jest mniejszy to podmieniamy
			if (distance_all < state[pos][visited]) // <- bo to dwojkowo jest zpaisany node
			{

				state[pos][visited] = distance_all;
			}
		}
		return state[pos][visited];
}