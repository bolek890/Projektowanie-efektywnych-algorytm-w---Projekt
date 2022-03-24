#include "Tsp_BB.h"

Tsp_BB::Tsp_BB()
{}

Tsp_BB::~Tsp_BB()
{}

Tsp_BB::Tsp_BB(vector<vector<int>> matrix) : matrix(matrix)
{}

vector<int> Tsp_BB::rowReduction(vector<vector<int>>& matrix)
{
	vector<int> minRow(matrix.size(), INT_MAX);
	// row[j] zawiera minimaln� waro�� w wierszu j
	for (unsigned i = 0; i < minRow.size(); i++) {
		for (unsigned j = 0; j < minRow.size(); j++) {
			if (matrix[j][i] != -1 && matrix[j][i] < minRow[j])
				minRow[j] = matrix[j][i];
		}
	}

	// Odejmij minimaln� warto�� z ka�dego elementu w wierszu, tak aby by�a chocia� jedna warto�� 0
	for (unsigned i = 0; i < minRow.size(); i++) {
		for (unsigned j = 0; j < minRow.size(); j++) {
			if (matrix[j][i] != -1)
				matrix[j][i] -= minRow[j];
		}
	}
	// Aby algorytm dzia�a� porpawnie potrzebne jest zabezpieczenie inaczej �cie�ka nie b�dzie optymalna
	replace(minRow.begin(), minRow.end(), INT_MAX, 0);

	return minRow;
}

vector<int> Tsp_BB::colReduction(vector<vector<int>>& matrix)
{
	vector<int> minCol(matrix.size(), INT_MAX);

	// col[j] zawiera minimaln� waro�� w wierszu i
	for (unsigned j = 0; j < minCol.size(); j++) {
		for (unsigned i = 0; i < minCol.size(); i++) {
			if (matrix[i][j] != -1 && matrix[i][j] < minCol[j])
				minCol[j] = matrix[i][j];
		}
	}

	// Odejmij minimaln� warto�� z ka�dego elementu w kolumnie, tak aby by�a chocia� jedna warto�� 0
	for (unsigned i = 0; i < minCol.size(); i++) {
		for (unsigned j = 0; j < minCol.size(); j++) {
			if (matrix[j][i] != -1)
				matrix[j][i] -= minCol[i];
		}
	}
	// Aby algorytm dzia�a� porpawnie potrzebne jest zabezpieczenie inaczej �cie�ka nie b�dzie optymalna
	replace(minCol.begin(), minCol.end(), INT_MAX, 0);

	return minCol;
}

int Tsp_BB::calculateCost(vector<vector<int>>& matrix)
{
	// Redukcja wierszy
	vector<int> minRow = rowReduction(matrix);
	// Redukcja kolumn
	vector<int> minCol = colReduction(matrix);
	// ca�kowity oczekiwany koszt to suma wszystkich redukcji w tabeli macierzy
	return accumulate(minRow.begin(), minRow.end(), 0) + accumulate(minCol.begin(), minCol.end(), 0);
}

finalPath Tsp_BB::solveTSPBnB()
{
	// Obiekt por�wnania, kt�ry ma by� u�yty do tworzenia kopca, w naszym przypadku waga
	auto comp = [](const Branch& nl, const Branch& nr) {
		if (nl.wage < nr.wage) return false;
		if (nl.wage > nr.wage) return true;
		return true; };

	// Kolejka priorytetowa kt�ra przechowuje aktywne w�z�y wyszukiwania
	priority_queue<Branch, vector<Branch>, decltype(comp)> pq(comp);

	//�cie�ka przej�� w drzewie
	vector<int> v;

	//Wstawienie miasta pocz�tkowego
	v.push_back(0);

	//Ustawienie sumy zredukowanych wierszy i kolumny
	int sum = calculateCost(matrix);

	// Stworzenie korzenia drzewa i oblicznenie jego drogi
	// Rozpocz�cie algorytmu TSP od 0 w�z�a
	Branch root = Branch::rootNode(matrix, v, 0);

	//Ustawienie warto�ci zredukowanych wierszy i kolumny
	root.wage = sum;

	// dodaj korze� do kolejki aktywnych w�z��w wyszukiwania
	pq.push(root);


	//Znajduje potomka z najmniejszym kosztem
	//Dodaje jego dzieci do kolejki a nast�pnie usuwa go z pami�ci
	while (!pq.empty())
	{
		// pobierz weze� o najmniejszym koszcie
		Branch min = pq.top();
		// Znaleziony w�ze� jest usuwany z listy aktywnych w�z��w
		pq.pop();
		// i przechowuje aktualnie odiedzany w�ze�
		int i = min.curr_node;
		// JE�ELI wszystkie wierzcho�ki(miasta) zosta�y odwiedzone
		if (min.node == matrix.size() - 1)
		{
			finalPath finalPath;
			// Powr�t do miasta startowego
			min.connection.push_back(0);

			// Wy�wietlanie wierzcho�k�w odwiedzonych
			finalPath.solution_path = min.connection;
			finalPath.cost = min.wage;
			return finalPath;
		}

		for (int j = 0; j < matrix.size(); j++)
		{
			// Dla potomka o minimalnej wadze tworzy kraw�d� w drzewie
			if (min.adj_Matrix[i][j] != -1)
			{
				//Tworzymy nowy obiekt kt�ry jest potomkiem
				Branch next = Branch::newPath(min.adj_Matrix, min.connection, min.node + 1, i, j);

				// utw�rz potomkai oblicz koszt jego drogi
				next.wage = min.wage + calculateCost(next.adj_Matrix) + min.adj_Matrix[i][j];

				// Dodaj potomka do listy aktywnych w�z��w
				pq.push(next);

				//Usuwamy z pami�ci nowy obiekt
				next.~Branch();

			}
		}
		//Usuwamy z pami�ci stary obiekt
		min.~Branch();
	}
}