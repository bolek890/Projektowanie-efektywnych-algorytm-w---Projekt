#pragma once
#include <iostream>
#include <vector>

using namespace std;

class RandGraph {
public:
	// Macierz s¹siedztwa losowanego grafu
	vector<vector<int>>costMatrix;

	RandGraph(int SIZE);
	// Funkcja wprowadzaj¹ca losowedane do grafu
	void startRand(int SIZE);
	// Funkcja wyœwietlaj¹ca macierz
	void showAdjMt(int SIZE);
	// Funkcja zapisuj¹ca dane do pliku
	void saveToFile(int SIZE, string file_name);
};


