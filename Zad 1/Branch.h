#pragma once

#include <vector>

using namespace std;

class Branch
{
public:
	//Zapisuje macierz s�siedztwa
	vector<vector<int>> adj_Matrix;

	//Zapisuje przebyt� droge
	vector<int> connection;

	//Zapisuje najmniejsz� warto�� przej�� 
	int wage;

	//Zapisuje numer miasta
	int curr_node;

	//Zapisuje ilo�� miast przebyt� do teraz
	int node;
	// Funkcja dodaj�ca now� �cie�k� do grafu
	static Branch newPath(vector<vector<int>> parentMatrix, vector<int> const& connection, int node, int i, int j);
	//Tworzy korze� drzewa
	static Branch rootNode(vector<vector<int>> parentMatrix, const vector<int>& connection, int i);

	Branch();
	~Branch();
};