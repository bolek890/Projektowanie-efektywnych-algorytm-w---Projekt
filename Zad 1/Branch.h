#pragma once

#include <vector>

using namespace std;

class Branch
{
public:
	//Zapisuje macierz s¹siedztwa
	vector<vector<int>> adj_Matrix;

	//Zapisuje przebyt¹ droge
	vector<int> connection;

	//Zapisuje najmniejsz¹ wartoœæ przejœæ 
	int wage;

	//Zapisuje numer miasta
	int curr_node;

	//Zapisuje iloœæ miast przebyt¹ do teraz
	int node;
	// Funkcja dodaj¹ca now¹ œcie¿kê do grafu
	static Branch newPath(vector<vector<int>> parentMatrix, vector<int> const& connection, int node, int i, int j);
	//Tworzy korzeñ drzewa
	static Branch rootNode(vector<vector<int>> parentMatrix, const vector<int>& connection, int i);

	Branch();
	~Branch();
};