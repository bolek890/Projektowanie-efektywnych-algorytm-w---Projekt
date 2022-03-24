#include <iostream>
#include "RandGraph.h"
#include "finalPath.h"
#include "Tsp_BB.h"

#include <fstream>
#include <windows.h>
#include <ctime>
#include <iomanip>
#include <string>
#include <random>

using namespace std;

//-------------------------------------------------------------------------
long long int read_QPC()
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}
//-------------------------------------------------------------------------

void printResult(finalPath& finalPath)
{
	std::cout << "Droga: ";
	for (int i = 0; i < finalPath.solution_path.size(); i++) {
		std::cout << finalPath.solution_path[i];
		if (i != finalPath.solution_path.size() - 1)
			std::cout << " - ";
	}
	std::cout << endl;
	std::cout << "Cykl hamiltona o najmniejszej wadze: " << finalPath.cost << endl;
}



int main()
{
	int switcher = NULL;
	int SIZE = 0, temp;
	fstream file;
	string fileName;
	vector<vector<int>> loadMatrix;
	Branch* branch = NULL;
	RandGraph* randomix;
	long long int frequency, start, elapsed;
	Tsp_BB tsp;
	finalPath finalPath;

	// MENU z opcjami do obsługi programu
	do {
		std::cout << "1. Wczytaj dane z pliku." << endl;
		std::cout << "2. Pokaz graf." << endl;
		std::cout << "3. Licz czas i cykl Hamiltona operacji TSP - BnB." << endl;
		std::cout << "4. Losuj graf." << endl;
		std::cout << "5. WYJDZ." << endl;
		std::cout <<  "Wybrana opcja: ";
		std::cin >> switcher;
		switch (switcher)
		{
		case 1:
			std::cout << "Podaj nazwe pliku:";
			std::cin >> fileName;
			loadMatrix.resize(0);
			loadMatrix.shrink_to_fit();
			file.open(fileName.c_str(), ios::in);

			if (file.is_open())
			{
				file >> SIZE;
				for (int i = 0; i < SIZE; i++)
				{
					loadMatrix.push_back(vector<int>());
				}

				if (file.fail())
					std::cout << "File error - READ SIZE" << endl;

				else {
					for (size_t i = 0; i < SIZE; i++) {
						for (size_t j = 0; j < SIZE; j++) {

							file >> temp;
							if (file.fail()) {
								std::cout << "File error - READ DATA" << endl;
								break;
							}
							else {
								loadMatrix[i].push_back(temp);
							}
						}
					}
				}

				file.close();
			}
			else
				std::cout << "File error - OPEN" << endl;
			break;
		case 2:
			// Wyświetlanie grafu
			cout << endl << "Adjency Matrix:" << endl << "     ";
			for (int i = 0; i < loadMatrix.size(); i++)
			{
				cout << " " << i << "  ";
			}
			cout << endl;
			for (int i = 0; i < loadMatrix.size(); i++)
			{
				cout << "_____";
			}
			for (int i = 0; i < loadMatrix.size(); i++)
			{
				cout << endl << i << " | ";
				for (int j = 0; j < loadMatrix.size(); j++)
				{
						cout << setw(3) << loadMatrix[i][j] << " ";
				}
			}
			cout << endl;

			break;
		case 3:
			if (loadMatrix.size() == 0)
				std::cout << "Nie mozna pokazac grafu!" << endl;
			else {
				tsp = Tsp_BB(loadMatrix);
				QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
				start = read_QPC();

				finalPath = tsp.solveTSPBnB();
				printResult(finalPath);

				elapsed = read_QPC() - start;
				std::cout << "Time [s] = " << fixed << setprecision(3) << (float)elapsed /
					frequency << endl;
				std::cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) /
					frequency << endl;
				std::cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) /
					frequency << endl;
				finalPath.solution_path.resize(0);
				finalPath.solution_path.shrink_to_fit();
			}

			break;
		case 4:
			int number_of_SIZE;
			std::cout << "Podaj liczbe miast:";
			std::cin >> number_of_SIZE;
			std::cout << "Podaj nazwe pliku:";
			std::cin >> fileName;

			srand(time(NULL));

			randomix = new RandGraph(number_of_SIZE);
			randomix->startRand(number_of_SIZE);
			randomix->saveToFile(number_of_SIZE, fileName.c_str());
			break;

		default:
			std::cout << "Nie ma takiej operacji!" << endl;
			break;
		}
	} while (switcher != 5);

}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
