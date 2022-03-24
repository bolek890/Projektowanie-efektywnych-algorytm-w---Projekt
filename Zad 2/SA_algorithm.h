#pragma once
#include <vector>
#include <math.h>
#include <time.h>
#include <random>
#include "finalPath.h"
#include <fstream>
#include <windows.h>
#include <ctime>
#include <iomanip>
#include <string>
#include <random>

// Stała Eulera e
const float M_E = 2.71828182845904523536;

using namespace std;

class SA_algorithm
{
	//-------------------------------------------------------------------------
	long long int read_QPC()
	{
		LARGE_INTEGER count;
		QueryPerformanceCounter(&count);
		return((long long int)count.QuadPart);
	}
	//-------------------------------------------------------------------------
public:
	// Macierz sąsiedztwa do algorytmu
	vector<vector<int>> adj_matrix;

	// Zmienne należące do algorytmu symulowanego wyżarzania
	float starting_temp; // temperatura początkowa
	float min_temp; // temperatura minimalna (końcowa)
	float curr_temp; // aktualna temperatura podczas działania algorytmu

	float cooling_rate; // współczynnik chłodzenia
	
	int iterations; // ilość iteracji jaką ma wykonywać się algorytm
	clock_t start; // liczenie czasu
	double max_time; // ograniczenie czasu

	//Wyniki
	finalPath prev_result;
	finalPath curr_result;
	finalPath next_result;
	finalPath best_result;

	// konstruktor parametryczny
	SA_algorithm(vector<vector<int>> adj_matrix, float starting_temp, float cooling_rate, float min_temp, double max_time, int iterations);
	// konstruktor
	SA_algorithm();

	// Główna metoda algorytmu
	finalPath simulatedAnnealing();
	// obliczanie prawdopodobieństwa
	double makeProbability();
	// obliczanie kosztów cyklu Hamiltona
	int calculatePath(vector<int> & path);
	// Metoda zamiany sąsiedztwa swap() 
	void swap();

	// destruktor
	~SA_algorithm();
};