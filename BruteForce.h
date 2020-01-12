#pragma once
#include "Algorithm.h"
class BruteForce :
	public Algorithm
{
private:
	vector<int> oryginalnaTrasa;
	vector<int> najlepszaTrasa;
	int calkowitaOdlegloscNajlepszejTrasy;
	int wynikFunkcjiCelu;
	void permutacje(int n);
public:
	BruteForce(Graph* grapf) : Algorithm(grapf) { 
		oryginalnaTrasa = grapf->path; 
		algorytmName = "Brute Force";
	};
	~BruteForce() = default;

	void run() override;
	void printPath() override;
};

