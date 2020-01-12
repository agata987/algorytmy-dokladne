#include "Menu.h"
#include <iostream>

using namespace std;

void Menu::print()
{
	g = new Graph(5);
	char opcja;

	cout << "\n   -----MENU-----" << endl;
	cout << "1. Wczytaj z pliku \t" << "5. Wyswietl graf\t" << "\t9. Test" << endl;
	cout << "2. Wygeneruj losowo \t" << "6. Brute Force\t" << "\t\t0. Wyjscie" << endl;
	cout << "3. Podaj sciezke \t" << "7. Branch and Bound\t" << "\tm - Menu" << endl;
	cout << "4. Funkcja celu \t" << "8. Dynamic -sym" << endl;

	do {
		cin.clear();
		cout << "\n>> ";
		cin >> opcja;
		cout << endl;

		switch (opcja)
		{
		case 'm':

			cout << "\n   -----MENU-----" << endl;
			cout << "1. Wczytaj z pliku \t" << "5. Wyswietl graf\t" << "\t9. Test" << endl;
			cout << "2. Wygeneruj losowo \t" << "6. Brute Force\t" << "\t\t0. Wyjscie" << endl;
			cout << "3. Podaj sciezke \t" << "7. Branch and Bound" << endl;
			cout << "4. Funkcja celu \t" << "8. Dynamic -sym" << endl;
			break;

		case '1':
			g = new Graph(5);
			g->readFromFile();
			break;

		case '2':

			int rozmiar;
			cout << " Podaj rozmiar macierzy: ";
			cin.clear();
			cin >> rozmiar;
			g = new Graph(rozmiar);
			g->reGenerate(rozmiar);
			g->generateRandom();
			g->randomPath();
			break;

		case '3':

			if (g->graf_ == true)
				g->setPath();
			else cout << "Najpierw utworz graf." << endl;

			break;
		case '4':

			if (g->graf_ == false)
				cout << "brak grafu" << endl;
			else if (g->sciezka_ == false)
				cout << "brak sciezki" << endl;
			else
			cout << g->funkcjaCelu() << endl;

			break;

		case '5':

			if (g->graf_ == true)
				g->display();
			else
				cout << "brak grafu" << endl;

			if (g->sciezka_ == true)
				g->printPath();
			else
				cout << "\nbrak sciezki" << endl;

			break;

		case '6':

			if (g->graf_ == false)
				cout << "brak grafu" << endl;
			else {
				if (g->sciezka_ == false)
					g->randomPath();

				bf = new BruteForce(g);
				bf->run();
				bf->printPath();
			}
			

			break;

		case '7':

			if (g->graf_ == false)
				cout << "brak grafu" << endl;
			else {
				if (g->sciezka_ == false)
					g->randomPath();

				bnb = new BranchAndBound(g);
				bnb->run();
				bnb->printPath();
			}

			break;

		case '8':
			if (g->graf_ == false)
				cout << "brak grafu" << endl;
			else {
				d = new Dynamic(g);
				d->run();
				d->printPath();
			}
			break;

		case '9':
			if (g->graf_ == false)
				cout << "brak grafu" << endl;
			else {
				if (g->sciezka_ == false)
					g->randomPath();
				cout << "-->";
				d = new Dynamic(g);
				d->test();
				cout << endl;
				cout << "-->";
				bnb = new BranchAndBound(g);
				bnb->test();
				cout << endl;
				cout << "-->";
				bf = new BruteForce(g);
				bf->test();
			}

			break;
		}

	} while (opcja != '0');
}

