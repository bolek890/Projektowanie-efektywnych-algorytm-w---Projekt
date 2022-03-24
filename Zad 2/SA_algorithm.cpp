#include "SA_algorithm.h"
#include <iostream>

// konstruktor parametryczny
SA_algorithm::SA_algorithm(vector<vector<int>> adj_matrix, float starting_temp, float cooling_rate, float min_temp, double max_time, int iterations)
	: adj_matrix(adj_matrix), starting_temp(starting_temp), cooling_rate(cooling_rate), min_temp(min_temp), max_time(max_time), curr_temp(starting_temp), iterations(iterations)
{

}

// konstruktor
SA_algorithm::SA_algorithm()
{
}

// G³ówna metoda algorytmu
finalPath SA_algorithm::simulatedAnnealing()
{
	srand(time(NULL));
	start = clock();

	// Tworzenie dorgi pocz¹tkowej
	for (int i = 1; i < adj_matrix.size(); i++) 
	{
		curr_result.solution_path.push_back(i);
	}

	// dodanie powrotu do miasta pocz¹tkowego
	curr_result.solution_path.push_back(0);

	// obliczanie kosztów aktualnego rozwi¹zania
	curr_result.cost = calculatePath(curr_result.solution_path);

	// Jak  na razie jest to najlepsze rozwi¹zanie
	best_result.solution_path = curr_result.solution_path;
	best_result.cost = curr_result.cost;

	// losowanie liczby rzeczywistej z przedzia³u 0 .. 1
	uniform_real_distribution<double> distribution(0.0, 1.0);
	default_random_engine generator;

	
		// g³ówna pêtla algorytmu
		while (curr_temp > min_temp)
		{
			// Ograniczenie czasowe
			if ((clock() - start) / CLOCKS_PER_SEC > max_time)
				break;

			for (int i = 0; i < iterations; i++)
			{
				// zamiana dwóch miast w next_result
				swap();

				// obliczanie wagi nowej œcie¿ki w next_result
				next_result.cost = calculatePath(next_result.solution_path);

				// Je¿eli aktualna œicie¿ka jest krótsza
				if (curr_result.cost > next_result.cost)
				{
					// nowe rozwi¹zanie staje siê aktualnym rozwi¹zaniem
					curr_result = next_result;

					// Je¿eli aktualne rozwi¹zanie jest mniejsze od najlepszego to zapisz
					if (best_result.cost > curr_result.cost) {
						best_result = curr_result;
					}
						
				}
				// Je¿eli aktualna œcie¿ka jest d³u¿sza to dodajemy rozwi¹zanie z prawdopodobieñstwem
				else if (makeProbability() > distribution(generator))
				{
					curr_result = next_result;
				}

			}

			// Geometryczne obliczanie temperatury
			curr_temp *= cooling_rate;
		
	}
	return best_result;
}

// obliczanie prawdopodobieñstwa
double SA_algorithm::makeProbability()
{
	// 
	double temp = -((curr_result.cost - next_result.cost) / curr_temp);

	return pow(M_E, temp);
}

// obliczanie kosztów cyklu Hamiltona
int SA_algorithm::calculatePath(vector<int> & path)
{
	int temp = 0;

	for (int i = 0; i < path.size() - 1; i++)
		temp += adj_matrix[path[i]][path[i + 1]];

	return temp;
}

// Metoda zamiany s¹siedztwa swap()
void SA_algorithm::swap()
{
	// losowanie miast o indeksach <1, n-1>
	int cityCount = curr_result.solution_path.size();
	int a = rand() % (cityCount - 2) + 1;
	int b = rand() % (cityCount - 2) + 1;
	while (a == b)
		b = rand() % (cityCount - 2) + 1;

	// zamiana dwóch miast
	next_result = curr_result;
	int tmp = next_result.solution_path[a];
	next_result.solution_path[a] = next_result.solution_path[b];
	next_result.solution_path[b] = tmp;
}


SA_algorithm::~SA_algorithm()
{
}
