#pragma once
#include"Algorithm.h"
class BranchAndBound :
	public Algorithm
{
private:
	vector<int> najlepszaTrasa;
	bool* odwiedzoneMiasta;
	int bestResult; // dlugosc najkrotszej trasy
	// 2 najkrotsze drogi z miasta: 
	int pierwszaNajkrotszaDroga(int miasto);
	int drugaNajkrotszaDroga(int miasto);  
	void rekurencja(int curr_bound, int curr_weight, int level, vector<int> curr_path);
	// funkcja bierze jako argumenty: 
	// curr_bound -> dolne ogarniczenie korzenia
	// curr_weight-> dlugosc jak dotad przebytej drogi
	// level-> poziom w drzewie
	// curr_path[] -> obecna sciezka, ktora pozniej bedzie skopiowana do "najlepszaTrasa"
	void copyTo_najlepszaTrasa(int curr_path[]);
public:
		BranchAndBound(Graph* grapf) : Algorithm(grapf) { 
		odwiedzoneMiasta = new bool[grapf->getnumberOfCities()];
		bestResult = INT_MAX;
		algorytmName = "Branch and Bound";
	};
	~BranchAndBound() = default;

	void run() override;
	void printPath() override;
};

