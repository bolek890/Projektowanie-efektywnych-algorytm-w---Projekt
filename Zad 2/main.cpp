#include <iostream>
#include "finalPath.h"
#include "SA_algorithm.h"
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

void printResult(finalPath& result)
{
	std::cout << "Najtansza sciezka: ";
	for (int i = 0; i < result.solution_path.size(); i++) {
		std::cout << result.solution_path[i];
		if (i != result.solution_path.size() - 1)
			std::cout << " - ";
	}
	std::cout << endl;
	std::cout << "Koszt sciezki: " << result.cost;
	std::cin.ignore();
	std::cin.get();
}


int main() {
	int switcher = NULL;
	int SIZE = 0, temp, cost = NULL;
	fstream file;
	string fileName;
	vector<vector<int>> loadMatrix;
	SA_algorithm sa_algorithm;
	long long int frequency, start, elapsed;
	finalPath result;
	float initTemp = 10000;
	float coolingTemp = 0.99;
	float minTemp = 0.0001;
	int iterations = 20;
	double time_max = 10;
	// MENU z opcjami do obs³ugi programu
	do {
		std::cout << "3.0v Parametry: "<< endl << "--------------------------------------" << endl << "Temperatura poczatkowa : "<< initTemp << endl << "Wspolczynnik chlodzenia : "<< coolingTemp << endl << "Temperatura minimalna : "<< minTemp << endl << "Maksymalny czas operacji: " << time_max << endl << "Dlugosc epoki: " << iterations << endl;
		std::cout << "--------------------------------------" << endl;
		std::cout << "1. Wczytaj dane z pliku." << endl;
		std::cout << "2. Zmien parametry dla TSP(SA)" << endl;
		std::cout << "3. Obliczcykl Hamiltona -> TSP (metoda Simulated Annealing)." << endl;
		std::cout << "4. WYJDZ." << endl << "Wybrana opcja: ";
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
			// Zmiana parametrów
			std::cout << "Podaj wartosci:" << endl;
			std::cout << "Temp poczatkowa: ";
			std::cin >> initTemp;
			std::cout << "Wspolczynnik chlodzenia: ";
			std::cin >> coolingTemp;
			std::cout << "Temp minimalna: ";
			std::cin >> minTemp;
			std::cout << "Czas operacji: ";
			std::cin >> time_max;
			std::cout << "Iteracje: ";
			std::cin >> iterations;
			break;
		case 3:
			std::cout << endl;
			sa_algorithm = SA_algorithm(loadMatrix, initTemp, coolingTemp, minTemp, time_max, iterations);


			// pomiary czasu
			/*QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
			start = read_QPC();*/

			result = sa_algorithm.simulatedAnnealing();
			

			/*elapsed = read_QPC() - start;
			std::cout << "Time [s] = " << fixed << setprecision(3) << (float)elapsed /
				frequency << endl;
			std::cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) /
				frequency << endl;
			std::cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) /
				frequency << endl;*/

			printResult(result);
			break;
		case 4:
			return 0;
			break;
		default:
			std::cout << "Nie ma takiej operacji!" << endl;
			break;
		
		}
	} while (true);




	return 0;
}

