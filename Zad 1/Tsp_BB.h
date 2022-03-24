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
	//Macierz przej�� do miast
	vector<vector<int>> matrix;
	// Funkcja redukuj�ca wiersze w macierzy s�siedztwa tak aby w ka�dym wierszu by�a warto�� = 0
	vector<int> rowReduction(vector<vector<int>>& matrix);
	// Funkcja redukuj�ca kolumny w macierzy s�siedztwa tak aby w ka�dej kolumnie by�a warto�� = 0
	vector<int> colReduction(vector<vector<int>>& matrix);
	// Funkcja wyznaczaj�ca doln� granic� na �cie�ce zaczynaj�cej si� od bie��cego w�z�a o minimalnej �cie�ce
	int calculateCost(vector<vector<int>>& matrix);

public:

	// Konstruktor z macierz�
	Tsp_BB(vector<vector<int>> matrix);

	// G��wny algorytm BnB
	finalPath solveTSPBnB();

	// Konstruktory, destruktory
	Tsp_BB();
	~Tsp_BB();
};