#include "Genetic.h"

using namespace std;

// Kosntruktor klasy
Genetic::Genetic(int number_of_vertices, int** matrix, int population_size)
{
	fitness.reserve(population_size);
	best_member.reserve(number_of_vertices);


	population.reserve(SIZE);
	best_members.reserve(SIZE);
	new_generation.reserve(2 * SIZE);

	this->population_size = population_size;
	SIZE = number_of_vertices;

	// Kopiowanie macierzy sąsiedztwa
	adj_matrix = new int* [SIZE];
	for (int i = 0; i < SIZE; i++)
		adj_matrix[i] = new int[SIZE];

	// Zastąpienie -1 na przekątnej zerami
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
		{
			adj_matrix[i][j] = matrix[i][j];
			if (i == j)	adj_matrix[i][j] = 0;
		}

	// Najlpeszy dystans jako największa liczba
	shortest_path = INT_MAX;
}

// Destruktor
Genetic::~Genetic()
{
	//Zwolnienie pamiêci
	for (int i = 0; i < SIZE; i++)
		delete[] adj_matrix[i];

	if (adj_matrix != nullptr) delete[] adj_matrix;
}

// Metoda licząca fitness czyli potencjał rozwiązania. Powinna ona rosnąć jeżeli ścieżka jest coraz krótsza
// dlatego wynik to odwrotność kosztu ścieżki 1/x
float Genetic::calculate_fitness(vector<int> population_member)
{
	return (1.0f / (CalculateCost(population_member) + 1));
}

// Metoda generująca pierwszą losową populacje dla zadanego ciagu wierzchołków
void Genetic::makeFirstPopulation()
{
	vector<int> population_member(SIZE);

	// Tworzymy pierwszą populację jaką jest ciąg kolejnych wierzchołków
	for (int i = 0; i < SIZE; ++i)
		population_member[i] = i;

	// Następuje losowe mieszanie wierzchołków w ciągu co tworzy kolejne permutacje rozwiązania
	for (int i = 0; i < population_size; ++i) {
		swapVertice(population_member, 20);
		population.push_back(population_member);
	}
}

// Funkcja zamineiająca kolejnośc wierzchołków dla pierwszej populacji
void Genetic::swapVertice(vector<int>& population_member, int how_much_times)
{
	//Pętla wykonująca o zadaną ilość razy zamianę wierzchołków w ciągu
	for (int i = 0; i < how_much_times; i++)
	{
		// Dwie inne niż 0
		int first_vertice = rand() % (SIZE - 1) + 1;
		int second_vertice = rand() % (SIZE - 1) + 1;

		// Jeśli wylosujemy to samo miasto następuje kolejne losowanie
		while (first_vertice == second_vertice)
			second_vertice = rand() % (SIZE - 1) + 1;

		// Zamiana kolejności wierzchołków
		swap(population_member[first_vertice], population_member[second_vertice]);
	}
}

// Metoda wprowadzająca mutację w zależności od wyboru
void Genetic::tryMutation(vector<int>& population_member)
{
	if ((float)rand() / (float)RAND_MAX <= mutation_probability)
	{
		// W zależności od wybory użytkownika
		if (mutation_choice == 0)
			transpositionMutation(population_member);
		else 
			inversionMutation(population_member);
	}

}

// Mutacja - metoda wzajemnej wymiany
void Genetic::transpositionMutation(vector<int>& permutation)
{
	// losujemy dwa indeksy wierzchołków
	int idxOne = 1 + rand() % (SIZE - 1);
	int idxTwo = 1 + rand() % (SIZE - 1);

	// losujemy dopóki będą różne
	while (idxOne == idxTwo) {
		idxTwo = 1 + rand() % (SIZE - 1);
	}

	// zamień kolejność
	swap(permutation[idxOne], permutation[idxTwo]);
}

// Mutacja - metoda inwersji
void Genetic::inversionMutation(vector<int>& permutation)
{
	// losujemy dwa indeksy
	int idxOne, idxTwo;
	idxOne = 1 + rand() % (SIZE - 1);
	idxTwo = 1 + rand() % (SIZE - 1);

	// Jeżeli indeksy są takie same musi nastąpić ich ponowna randomizacja
	while (idxOne == idxTwo)
		idxTwo = 1 + rand() % (SIZE - 1);

	// Jeżeli indeks pierwszy jest większy musimy go zamienić aby była zachowana poprawność mustacji
	if (idxOne > idxTwo)
		swap(idxOne, idxTwo);

	// Musimy zaokrąglić ilość iteracji dla pętli w przypadku nieparzystych indeksów
	int iterator = ceil((idxTwo - idxOne) / 2.0f);

	//Zamiana pierwzszego z ostatnim , drugiego z przedostatnim...
	for (int i = idxOne, j = idxTwo; i < idxOne + iterator; i++, j--)
	{
		swap(permutation[i], permutation[j]);
	}
}

// Krzyżowanie - metoda z zachowaniem porządku polega na skopiowaniu losowych sekwencji genów ustalonych na podstawie dwóch punktów krzyżowań
void Genetic::orderCrossover()
{
	int idxOne, idxTwo;

	// losowanie dwóch indeksów
	idxOne = (rand() % population_size);
	idxTwo = (rand() % population_size);

	// Losuje dopóki dwa indeksy będą różne
	while (idxOne == idxTwo)
		idxTwo = rand() % population_size;
	// utworzenie jednego rodzica
	vector<int> mother = population.at(idxOne);
	// utworzenie drugiego rodzica
	vector<int> father = population.at(idxTwo);

	// Prawdopodobieństwo krzyżowania jeżeli wylosowana wartość będzie większa nastąpi dodanie rodziców
	if ((float)rand() / (float)RAND_MAX > crossover_probability)
	{
		new_generation.push_back(mother);
		new_generation.push_back(father);
		return;
	}

	// utworzenie wektorów dzieci jeżeli ma dojść do krzyżowania
	vector<int> oneChild(SIZE);
	vector<int> secondChild(SIZE);

	// Wybór punktów krzyżowania
	int oneIdxCrossing = 1 + rand() % (SIZE - 1);
	int twoIdxCrossing = 1 + rand() % (SIZE - 1);

	while (oneIdxCrossing == twoIdxCrossing)
	{
		oneIdxCrossing = 1 + rand() % (SIZE - 1);
		twoIdxCrossing = 1 + rand() % (SIZE - 1);
	}

	// Zamieniamy miejscami punkty jeżeli pierwszy ma wiekszą wartość od drugiego
	if (oneIdxCrossing > twoIdxCrossing)
	{
		int temp = twoIdxCrossing;
		twoIdxCrossing = oneIdxCrossing;
		oneIdxCrossing = temp;
	}

	// Pętla krzyżowania
	oneChild.at(0) = 0;

	// Kopiujemy dane, które znajdują sie pomiędzy punktami krzyżowania
	for (int i = oneIdxCrossing; i <= twoIdxCrossing; ++i)
	{
		oneChild[i] = mother[i];
		secondChild[i] = father[i];
	}

	// Operacje dla pierwszego potomka w znajdowaniu wartości za pomocą funkcji find(początek, koniec, wyrażenie porównywane)
	for (int i = 1; i < oneIdxCrossing; i++)
	{
		for (int j = 1; j < SIZE; j++)
		{
			// Porównujemy z wartościami drugiego rodzica, jeżeli są różne kontynuujemy
			if (find(oneChild.begin(), oneChild.end(), father.at(j)) != oneChild.end()) 
				continue;
			else 
				// Jeżeli nie, zmieniamy wartość
				oneChild.at(i) = father.at(j);
		}
	}

	// Podobne operacje wykonujemy dla drugiego punktu krzyżowania
	for (int i = twoIdxCrossing + 1; i < SIZE; i++)
	{
		for (int j = 1; j < SIZE; j++)
		{
			// Porównujemy z wartościami drugiego rodzica, jeżeli są różne kontynuujemy
			if (find(oneChild.begin(), oneChild.end(), father.at(j)) != oneChild.end()) 
				continue;
			else
				// Jeżeli nie, zmieniamy wartość
				oneChild.at(i) = father.at(j);
		}
	}

	// Wywołanie mutacji z prawdopodobieństwem dla pierwszego potomka
	tryMutation(oneChild);

	// Włączenie do nowego pokolenia pierwszego potomka
	new_generation.push_back(oneChild);


	// Analogiczne operacje dla drugiego potomka
	for (int i = 1; i < oneIdxCrossing; i++)
	{
		for (int j = 1; j < SIZE; j++)
		{
			// Porównujemy z wartościami drugiego rodzica, jeżeli są różne kontynuujemy
			if (find(secondChild.begin(), secondChild.end(), mother.at(j)) != secondChild.end()) 
				continue;
			else 
				// Jeżeli nie, zmieniamy wartość
				secondChild.at(i) = mother.at(j);
		}
	}

	for (int i = twoIdxCrossing + 1; i < SIZE; i++)
	{
		for (int j = 1; j < SIZE; j++)
		{
			// Porównujemy z wartościami drugiego rodzica, jeżeli są różne kontynuujemy
			if (find(secondChild.begin(), secondChild.end(), mother.at(j)) != secondChild.end()) 
				continue;
			else 
				// Jeżeli nie, zmieniamy wartość
				secondChild.at(i) = mother.at(j);
		}
	}

	// Wywołanie mutacji dla drugiego dziecka
	tryMutation(secondChild);

	//Dodanie pierwszego dziecka powstałego z pary rodziców
	new_generation.push_back(secondChild);
}

// Tworzenie kolejnego pokolenia rozwiązań
void Genetic::makeNextGeneration()
{
	// Wyczyszczenie wektora z poprzedniego pokolenia
	new_generation.clear();
	best_members.clear();

	// Pętla krzyżowania rodziców i tworzenia potomków
	for (int i = 0; i < population_size; i++)
		orderCrossover();

	// Srotowanie osobników populacji po współczynniku potencjału optymalnego rozwiązania
	sort(new_generation.begin(), new_generation.end(), [this](auto i, auto j)->bool {return calculate_fitness(i) > calculate_fitness(j); });

	// Wielkość nowej populacji pozostaje niezmieniona
	int new_population_size = new_generation.size();

	// wybranie najlepszych osobników
	for (int i = 0; i < population_size; i++)
		best_members.push_back(new_generation.at(i));

	// Pupilacja to najlepsze osobniki
	population = best_members;

}

// Pokazywanie ścieżki końcowej
void Genetic::showFinalPath()
{
	cout << "Najmniejsza sciezka : " << shortest_path << endl;
	cout << "Droga : ";
	for (int j = 0; j < SIZE; j++) 
		cout << best_member.at(j) << " ";
	cout << "0" << endl;
}



// Aktualizacja parametrów algorymtu
void Genetic::setParams(int iterations, float mutation_probability, int mutation_manner, float crossover_probability, double max_time)
{
	this->iterations = iterations;
	this->mutation_probability = mutation_probability;
	this->mutation_choice = mutation_manner;
	this->crossover_probability = crossover_probability;
	this->max_time = max_time;
}

// Główna metoda algorytmu
void Genetic::geneticAlghoritm()
{
	// Start zegara
	start = clock();

	//Wygenerowanie początkowej permutacji - losowo
	makeFirstPopulation();

	for (int i = 0; i < iterations; ++i)
	{
		// ograniczenie czasowe
		if ((clock() - start) / CLOCKS_PER_SEC > max_time)
			break;

		// W metodzie występuje krzyżowania oraz mutacja
		makeNextGeneration();

		// Aktualizacja najlepszej ścieżki
		int best_member_cost = CalculateCost(population.front());
		if (best_member_cost < shortest_path)
		{
			shortest_path = best_member_cost;
			best_member = population.front();
		}
		
	}
}

int Genetic::CalculateCost(vector<int>& permutation)
{
	// Inicjalizacja początkowego kosztu cyklu
	int cost = 0;

	for (int i = 0; i < SIZE - 1; i++)
		cost += adj_matrix[permutation.at(i)][permutation.at(i + 1)];

	// dodanie ostatniego odcina powrotnego do drogi
	cost += adj_matrix[permutation.at(SIZE - 1)][0];
	return cost;
}

