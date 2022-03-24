#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <windows.h>
#include <iomanip>


using namespace std;

class Genetic
{
public:
	int SIZE; //Liczba wierzcho³ków w grafie = matrix size
	int** adj_matrix;

	// Parametry algorytmu genetycznego
	int iterations;
	int population_size;
	float mutation_probability;
	float crossover_probability;
	int mutation_choice;


	clock_t start; 
	int max_time; 
	int shortest_path;

	// Wektory przechowujące osobników
	vector<vector<int>> population;
	vector<vector<int>> best_members;
	vector<vector<int>> new_generation;
	vector<float> fitness;
	vector<int> best_member;

	// Funkcje algorytmu genetycznego
	void makeFirstPopulation();
	void swapVertice(vector<int>& population_member, int num);
	void makeNextGeneration();
	float calculate_fitness(vector<int> population_member);

	// Metody potrzebne do mutacj
	void tryMutation(vector<int>& population_member);
	void transpositionMutation(vector<int>& permutation);
	void inversionMutation(vector<int>& permutation);

	int CalculateCost(vector<int>& permutation);

	void orderCrossover();
	Genetic(int number_of_vertices, int** A, int population_size);
	void setParams(int iterations, float mutation_probability, int mutation_choice, float crossover_probability, double max_time);

	void geneticAlghoritm();
	void showFinalPath();

	~Genetic();
};