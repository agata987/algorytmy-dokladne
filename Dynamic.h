#pragma once
#include "Algorithm.h"

class Dynamic :
	public Algorithm
{
private:
	int rekurencja(const vector<vector<int>>& cities, int pos, int visited, vector<vector<int>>& state);
	int koszt;
public:
	Dynamic(Graph* graph) : Algorithm(graph) {
		algorytmName = "Dynamic";
	};
	~Dynamic() = default;

	void run() override;
	void printPath() override;
};

