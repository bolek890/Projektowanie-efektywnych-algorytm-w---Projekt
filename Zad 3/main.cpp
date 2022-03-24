#include <iostream>
#include <fstream>
#include <windows.h>
#include <ctime>
#include <iomanip>
#include <string>
#include <random>
#include "Genetic.h"

using namespace std;

//-------------------------------------------------------------------------
long long int read_QPC()
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}
//-------------------------------------------------------------------------



// Dane pocz¹tkowe
int iterations = 200;
int population_size = 100;
float mutation_probability = 0.1f;
float crossover_probability = 0.9f;
int mutation_choice = 0;
int max_time = 100;



int main() {
	int switcher = NULL;
	int mutation_option = NULL;
	int SIZE = 0, temp, cost = NULL;
	fstream file;
	string fileName;
	Genetic* TSP;
	int** loadMatrix = nullptr;

	
	long long int frequency, start, elapsed;

	// MENU z opcjami do obs³ugi programu
	do {
		std::cout << "Parametry: " << endl << "--------------------------------------" << endl << "Iteracje : " << iterations << endl << "Populacja : " << population_size << endl << "Prawd. mutacji : " << mutation_probability << endl << "Prawd. krzyzowania : " << crossover_probability << endl << "Mutacja (0 - metoda wzajemnej wymiany, 1 - metoda inversji: " << mutation_choice << endl << "Maksymalny czas:"<< max_time << endl;
		std::cout << "--------------------------------------" << endl;
		std::cout << "1. Wczytaj dane z pliku." << endl;
		std::cout << "2. Zmien parametry dla alg. genetycznego" << endl;
		std::cout << "3. Oblicz cykl Hamiltona -> TSP genetyczny" << endl;
		std::cout << "4. WYJDZ." << endl << "Wybrana opcja: ";
		std::cin >> switcher;
		switch (switcher)
		{
		case 1:
			std::cout << "Podaj nazwe pliku:";
			std::cin >> fileName;
			/*loadMatrix.resize(0);
			loadMatrix.shrink_to_fit();*/
			file.open(fileName.c_str(), ios::in);

			if (file.is_open())
			{
				file >> SIZE;
				loadMatrix = new int* [SIZE];
				for (int i = 0; i < SIZE; i++)
				{
					loadMatrix[i] = new int[SIZE];
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
								loadMatrix[i][j] = temp;
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
			std::cout << "Iteracje: ";
			std::cin >> iterations;
			std::cout << "Wielkosc populacji: ";
			std::cin >> population_size;
			std::cout << "Prawdopodobienstwo mutacji: ";
			std::cin >> mutation_probability;
			std::cout << "Rodzaj mutacji(0 - metoda wzajemnej wymiany, 1 - metoda inwersji): ";
			std::cin >> mutation_choice;

			std::cout << "Prawdopodobienstwo krzyzowania osobnikow: ";
			std::cin >> crossover_probability;
			std::cout << "Maksymalny czas: ";
			std::cin >> max_time;
			break;
		case 3:
			 TSP = new Genetic(SIZE, loadMatrix, population_size);
			 TSP->setParams(iterations, mutation_probability, mutation_choice, crossover_probability, max_time);
			 TSP->geneticAlghoritm();
			 TSP->showFinalPath();
			 TSP->~Genetic();
			std::cout << endl;
			


			// pomiary czasu
			/*QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
			start = read_QPC();*/



			/*elapsed = read_QPC() - start;
			std::cout << "Time [s] = " << fixed << setprecision(3) << (float)elapsed /
				frequency << endl;
			std::cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) /
				frequency << endl;
			std::cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) /
				frequency << endl;*/

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

