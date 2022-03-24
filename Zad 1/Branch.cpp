#include "Branch.h"

Branch::Branch()
{
}


Branch::~Branch()
{
}

Branch Branch::newPath(vector<vector<int>> parentMatrix, vector<int> const& connection, int node, int i, int j)
{
	Branch branch;

	// przechowuje rodzica kraw�dzi drzewa przestrzeni stan�w
	branch.connection = connection;
	//Dodaje przej�cie 
	branch.connection.push_back(j);
	//Zapisz przekazan� macierz przej�� poprzedniego w�z�a
	branch.adj_Matrix = parentMatrix;

	// Zmie� kolumn�[i] i wiersz[j] na  -1 
	for (int k = 0; k < parentMatrix.size(); k++)
	{
		// ustaw kraw�d� wychodz�c� z "miasta" na -1
		branch.adj_Matrix[i][k] = -1;

		// ustaw kraw�d� wychodz�c� do "miasta" na na -1
		branch.adj_Matrix[k][j] = -1;
	}

	// Ustaw j->0 na -1
	branch.adj_Matrix[j][connection[0]] = -1;

	// Liczba miast odwiedzonych
	branch.node = node;

	// Przypisz aktualny numer w�z�a
	branch.curr_node = j;

	// zwr�� w�ze�
	return branch;
}

Branch Branch::rootNode(vector<vector<int>> parentMatrix, const vector<int>& connection, int i)
{
	Branch node;
	//Zapisz poprzedni� �cie�k� 
	node.connection = connection;
	//Zapisz przekazan� macierz przej�� poprzedniego w�z�a
	node.adj_Matrix = parentMatrix;
	//Ustaw ilo�ci miast odwiedzonych
	node.node = 0;
	//Zapisz aktualny numer miasta
	node.curr_node = i;

	return node;
}