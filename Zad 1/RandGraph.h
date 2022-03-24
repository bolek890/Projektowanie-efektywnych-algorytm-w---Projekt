#pragma once
#include <iostream>
#include <vector>

using namespace std;

class RandGraph {
public:
	// Macierz s�siedztwa losowanego grafu
	vector<vector<int>>costMatrix;

	RandGraph(int SIZE);
	// Funkcja wprowadzaj�ca losowedane do grafu
	void startRand(int SIZE);
	// Funkcja wy�wietlaj�ca macierz
	void showAdjMt(int SIZE);
	// Funkcja zapisuj�ca dane do pliku
	void saveToFile(int SIZE, string file_name);
};


