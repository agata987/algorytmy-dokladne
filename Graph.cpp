#include "Graph.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <algorithm>
#include <queue>

using namespace std;

void Graph::addEdge(int city1, int city2, int distance)
{
	matrix[city1][city2] = distance;
}

int Graph::getWeight(int city1, int city2)
{
	return matrix[city1][city2];
}

void Graph::display()
{
	std::cout <<" "<< "\t";
	for (int i = 0; i < numberOfCities; i++)
	{
		std::cout << i << "\t";
	}
	cout << endl;
	for (int i = 0; i < numberOfCities; i++)
	{
		std::cout << i << "\t";
		for (int j = 0; j < numberOfCities; j++)
			std::cout << matrix[i][j] << "\t";

		std::cout << std::endl;
	}
}

int Graph::getnumberOfCities()
{
	return numberOfCities;
}

void Graph::generateRandom()
{
	srand(time(NULL));

	for(int i=0;i<numberOfCities;i++)
		for (int j = 0; j < numberOfCities; j++)
		{
			if (i != j)
				addEdge(i, j, rand() % 101 + 1);
			else
				addEdge(i, j, -1);
		}
	graf_ = true;
}

void Graph::reGenerate(int newSize)
{
	for (int i = 0; i < numberOfCities; i++)
		delete[] matrix[i];

	delete[] matrix;

	this->numberOfCities = newSize;
	matrix = new int* [numberOfCities];

	for (int i = 0; i < numberOfCities; i++)
		matrix[i] = new int[numberOfCities];
}

void Graph::readFromFile()
{
	string sciezka;
	cout << "Podaj sciezke do pliku: ";
	cin >> sciezka;

	fstream plik;
	plik.open(sciezka, ios::in);

	if (plik.good() == false)
	{
		cout << "Blad otwarcia pliku." << endl;
	}
	else 
	{

		int newSize;

		plik >> name;
		plik >> newSize;

		reGenerate(newSize);

		// tworzenie grafu
		int  value;
		for (int i = 0; i < numberOfCities; i++)
		{
			for (int j = 0; j < numberOfCities; j++)
			{
				plik >> value;
				addEdge(i, j, value);
			}
		}

		graf_ = true;
		sciezka_ = false;
	}
	plik.close();
}

int Graph::funkcjaCelu()
{
		int sum = 0;
		for (vector<int>::iterator it = path.begin(); it != prev(path.end()); it++)
		{
			sum += getWeight(*it, *(next(it,1)));
		}
		return sum;
}

void Graph::setPath()
{
	cout << "Podaj kolejnosc wierzcholkow (0 - " << numberOfCities - 1 << "): ";

	path.clear();

	int vertex, added=0;
	cin.clear();

	do {
		cin >> vertex;
		while (find(path.begin(), path.end(), vertex) != path.end())
		{
			cout << "\nTa wartosc jest juz w sciezce." << endl;
			cin >> vertex;
		}
		while (vertex > numberOfCities - 1)
		{
			cout << "\nNie ma takiego wierzcholka." << endl;
			cin >> vertex;
		}
		path.push_back(vertex);
		added++;
	} while (added < numberOfCities);

	path.push_back(path.front());

	sciezka_ = true;
}

void Graph::randomPath()
{
	srand(time(NULL));

	if (path.empty())
		for (int i = 0; i < numberOfCities; i++)
			path.push_back(i);

	random_shuffle(path.begin(),path.end());
	path.push_back(path.front());

	while (czyIstniejeSciezkaDlaAsymetrycznych()==false)
	{
		path.pop_back();
		random_shuffle(path.begin(), path.end());
		path.push_back(path.front());
	}

	sciezka_ = true;
}

void Graph::printPath()
{
	cout << endl;
	cout << "sciezka: ";
	for (vector<int>::iterator it = path.begin(); it != path.end(); it++)
		cout << *it << " ";
	cout << endl;
}

int Graph::getMinimumDistanceTo(int city)
{
	int min(INT_MAX);

	for (int i = 0; i < numberOfCities; i++)
	{
		if (matrix[i][city]<min && matrix[i][city]>-1)
			min = matrix[i][city];
	}

	return min;
}

int Graph::getMinimumDistanceFrom(int city)
{
	int min(INT_MAX);

	for (int i = 0; i < numberOfCities; i++)
	{
		if (matrix[city][i]<min && matrix[city][i]>-1)
			min = matrix[city][i];
	}

	return min;
}

bool Graph::czyIstniejeSciezkaDlaAsymetrycznych()
{

	vector<int>::iterator it, it2;

	bool istnieje = true;

	for (it = path.begin(); it != path.end() - 1; it++)
	{
		it2 = it;
		it2++;

		if (getWeight(*it, *it2) < 1)
		{
			istnieje = false;
			break;
		}
	}
	return istnieje;
}
