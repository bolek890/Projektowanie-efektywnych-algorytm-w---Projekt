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

	// przechowuje rodzica krawêdzi drzewa przestrzeni stanów
	branch.connection = connection;
	//Dodaje przejœcie 
	branch.connection.push_back(j);
	//Zapisz przekazan¹ macierz przejœæ poprzedniego wêz³a
	branch.adj_Matrix = parentMatrix;

	// Zmieñ kolumnê[i] i wiersz[j] na  -1 
	for (int k = 0; k < parentMatrix.size(); k++)
	{
		// ustaw krawêdŸ wychodz¹c¹ z "miasta" na -1
		branch.adj_Matrix[i][k] = -1;

		// ustaw krawêdŸ wychodz¹c¹ do "miasta" na na -1
		branch.adj_Matrix[k][j] = -1;
	}

	// Ustaw j->0 na -1
	branch.adj_Matrix[j][connection[0]] = -1;

	// Liczba miast odwiedzonych
	branch.node = node;

	// Przypisz aktualny numer wêz³a
	branch.curr_node = j;

	// zwróæ wêze³
	return branch;
}

Branch Branch::rootNode(vector<vector<int>> parentMatrix, const vector<int>& connection, int i)
{
	Branch node;
	//Zapisz poprzedni¹ œcie¿kê 
	node.connection = connection;
	//Zapisz przekazan¹ macierz przejœæ poprzedniego wêz³a
	node.adj_Matrix = parentMatrix;
	//Ustaw iloœci miast odwiedzonych
	node.node = 0;
	//Zapisz aktualny numer miasta
	node.curr_node = i;

	return node;
}