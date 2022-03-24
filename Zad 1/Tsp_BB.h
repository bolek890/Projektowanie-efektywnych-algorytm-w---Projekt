#pragma once

#include "Branch.h"
#include "finalPath.h"
#include <numeric>
#include <queue>
#include <iostream>

using namespace std;

class Tsp_BB
{
private:
	//Macierz przejœæ do miast
	vector<vector<int>> matrix;
	// Funkcja redukuj¹ca wiersze w macierzy s¹siedztwa tak aby w ka¿dym wierszu by³a wartoœæ = 0
	vector<int> rowReduction(vector<vector<int>>& matrix);
	// Funkcja redukuj¹ca kolumny w macierzy s¹siedztwa tak aby w ka¿dej kolumnie by³a wartoœæ = 0
	vector<int> colReduction(vector<vector<int>>& matrix);
	// Funkcja wyznaczaj¹ca doln¹ granicê na œcie¿ce zaczynaj¹cej siê od bie¿¹cego wêz³a o minimalnej œcie¿ce
	int calculateCost(vector<vector<int>>& matrix);

public:

	// Konstruktor z macierz¹
	Tsp_BB(vector<vector<int>> matrix);

	// G³ówny algorytm BnB
	finalPath solveTSPBnB();

	// Konstruktory, destruktory
	Tsp_BB();
	~Tsp_BB();
};