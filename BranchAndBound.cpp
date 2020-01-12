#include "BranchAndBound.h"
#include <iostream>

int BranchAndBound::pierwszaNajkrotszaDroga(int miasto)
{
	return graph->getMinimumDistanceFrom(miasto);
}

int BranchAndBound::drugaNajkrotszaDroga(int miasto)
{
	int droga1 = INT_MAX;
	int droga2 = INT_MAX;

	for (int i = 0; i < graph->getnumberOfCities(); i++)
	{
		if (miasto == i)
			continue;

		if (graph->getWeight(miasto, i) <= droga1)
		{
			droga2 = droga1;
			droga1 = graph->getWeight(miasto, i);
		}
		else if (graph->getWeight(miasto, i) <= droga2 && graph->getWeight(miasto, i) != droga1)
			droga2 = graph->getWeight(miasto, i);
	}

	return droga2;
}

void BranchAndBound::rekurencja(int curr_bound, int curr_weight, int level, vector<int> curr_path)
{

	// przypadek w ktorym osiagnelismy poziom rowny licznie miast, czyli odwiedzilismy raz wszystkie miasta
	if (level == graph->getnumberOfCities())
	{
		// sprawdzamy czy istnieje krawedz z ostatniego miasta do pierwszego 
		if (graph->getWeight(curr_path[level - 1], curr_path[0]) > 0)
		{

			// w curr_res mamy calkowia dlugosc sciezki (dlugosc aktualnego rozwiazania) 
			int curr_res = curr_weight + graph->getWeight(curr_path[level - 1], curr_path[0]);
			curr_path[level] = curr_path[0];

			// jezeli jest lepsze od obecnego bestResulat to podmieniamy
			if (curr_res < bestResult)
			{
				najlepszaTrasa = curr_path;	//najlepsza trasa
				bestResult = curr_res;		// dlugosc tej najlepszej trasy
			}

			return;
		}
	}

	// dla innych poziomow drzewa dla wszystkich miast budujemy drzewo rekurencyjnie
	for (int i = 0; i < graph->getnumberOfCities(); i++)
	{
		// rozwazamy nastepne miasto jezeli go jeszczenie nie odwiedzilismy i jezeli istnieje dorga do niego
		if (graph->getWeight(curr_path[level - 1], i) >0 && odwiedzoneMiasta[i] == false)
		{
			int temp = curr_bound;
			curr_weight += graph->getWeight(curr_path[level - 1], i);

			// odejmujemy od naszego zalozenia to co sobie wczesniej policzylismy
			// i potem dodajemy to co faktycznie przebylismy czyli obliczony curr_weight
			
			// inne niz dla innych poziomow obliczanie curr_bound dla poziomu 2
			if (level == 1)
				// najkrotsza droga do 0 i do innego miasta do ktorego idziemy /2
				curr_bound -= (pierwszaNajkrotszaDroga(curr_path[level - 1]) + pierwszaNajkrotszaDroga(i)) / 2;
			else
				// druga najkrotsza droga do miasta w ktorym jestesmy i do ktorego idziemy /2
				// pierwsza najrotsza droga do miasta w ktorym jestesmy zostala odjeta poziom wyzej
				curr_bound -= (drugaNajkrotszaDroga(curr_path[level - 1]) + pierwszaNajkrotszaDroga(i)) / 2;


			// curr_bound + curr_weight to aktualne dolne ograniczenie dla wezla drzewa w ktorym sie znajdujemy
			// jezeli aktualne dolne ograniczenie jest mniejsze niz bestResult rozwijamy dalej drzewo od tego wezla
			if (curr_bound + curr_weight < bestResult)
			{
				curr_path[level] = i;
				odwiedzoneMiasta[i] = true;

				// wywolujemy rekurencje dla nast poziomu drzewa
				rekurencja(curr_bound, curr_weight, level + 1, curr_path);
			}

			// jezeli nie rozwijamy dalej musimy przywrocic wartosci dla curr_weight i curr_bound, odcinamy tego node'a
			curr_weight -= graph->getWeight(curr_path[level - 1], i);
			curr_bound = temp;

			// resetujemy tez tablice odwiedzonych miast
			for (int i = 0; i < graph->getnumberOfCities(); i++)
				odwiedzoneMiasta[i] = false;


			for (int j = 0; j <= level - 1; j++)
				odwiedzoneMiasta[curr_path[j]] = true;
		}

	}
}

void BranchAndBound::run()
{
	// tworzymy vector rozmiaru liczba miast +1 i wypelniamy wartosciami -1
	vector<int> curr_path(graph->getnumberOfCities()+1,-1);

	// obliczamy dolne ograniczenie dla korzenia
	// wg wzoru : 1/2 * (pierwsze min + drugie min) dla wszystkich krawedzi
	int curr_bound = 0;

	for (int i = 0; i < graph->getnumberOfCities(); i++)
		odwiedzoneMiasta[i] = false;


	// poczatkowa wartosc dla curr bound (dolnego ograniczenia)
	for (int i = 0; i < graph->getnumberOfCities(); i++)
		curr_bound += (pierwszaNajkrotszaDroga(i) + drugaNajkrotszaDroga(i));

	// dzielimy dolne ograniczenie przez 2 i zaokragloamy dolne ograniczenie curr_bound do liczby calkowtej
	// jezeli jest nieparzyste to dodajmy 1  
	// chcemy byc jak najblizej minimalnej mozliwej wartosci
	curr_bound = curr_bound % 2 == 0 ? curr_bound / 2 : curr_bound / 2 + 1;

	// zaczynamy od miasta nr 0
	odwiedzoneMiasta[0] = true;
	curr_path[0] = 0;

	// wywolujemy rekurencje z wartosciami poczatkowymu curr_weight = 0  i poziomem drzewa = 1
	rekurencja(curr_bound, 0, 1, curr_path);
}

void BranchAndBound::printPath()
{

	for (int i = 0; i < graph->getnumberOfCities()+1; i++)
		std::cout << najlepszaTrasa[i] << " ";

	cout << "	koszt drogi: " << bestResult << endl;

}