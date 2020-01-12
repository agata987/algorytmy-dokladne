#pragma once
#include <string>
#include <vector>

using namespace std;

class Graph
{
private:
	int** matrix;
	int numberOfCities;
	string name = "brak";
public:
	bool graf_ = false;
	bool sciezka_ = false;

	vector<int> path;
	Graph(int numberOfCities)
	{
		this->numberOfCities = numberOfCities;
		matrix = new int* [numberOfCities];

		for (int i = 0; i < numberOfCities; i++)
			matrix[i] = new int[numberOfCities];
	};
	~Graph() = default;
	void readFromFile();
	void addEdge(int city1, int city2, int distance);
	void reGenerate(int newSize);
	void generateRandom();
	void randomPath();
	int funkcjaCelu();
	bool czyIstniejeSciezkaDlaAsymetrycznych();
	// get
	int getWeight(int city1, int city2);
	int getnumberOfCities();
	// minimalna doleglosc pomiedzy dwoma miastami
	int getMinimumDistanceTo(int city);
	int getMinimumDistanceFrom(int city);
	// set
	void setPath();
	// print
	void printPath();
	void display();
};

