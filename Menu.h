#pragma once
#include "Graph.h"
#include "BranchAndBound.h"
#include "BruteForce.h"
#include "Dynamic.h"

class Menu
{
	Graph* g;
	BranchAndBound* bnb;
	BruteForce* bf;
	Dynamic* d;
public:
	Menu() = default;
	~Menu() = default;

	void print();
};

