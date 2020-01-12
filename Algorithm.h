#pragma once

#include "Graph.h"
#include "Timer.h"
#include <vector>

class Algorithm
{
protected:
	Graph* graph;
	string algorytmName;
public:
	Algorithm(Graph* graph) : graph(graph) {};
	~Algorithm() = default;

	virtual void run() = 0;
	virtual void printPath() = 0;
	void test();
};

