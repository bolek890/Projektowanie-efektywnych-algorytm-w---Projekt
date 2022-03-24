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
	// row[j] zawiera minimaln¹ waroœæ w wierszu j
	for (unsigned i = 0; i < minRow.size(); i++) {
		for (unsigned j = 0; j < minRow.size(); j++) {
			if (matrix[j][i] != -1 && matrix[j][i] < minRow[j])
				minRow[j] = matrix[j][i];
		}
	}

	// Odejmij minimaln¹ wartoœæ z ka¿dego elementu w wierszu, tak aby by³a chocia¿ jedna wartoœæ 0
	for (unsigned i = 0; i < minRow.size(); i++) {
		for (unsigned j = 0; j < minRow.size(); j++) {
			if (matrix[j][i] != -1)
				matrix[j][i] -= minRow[j];
		}
	}
	// Aby algorytm dzia³a³ porpawnie potrzebne jest zabezpieczenie inaczej œcie¿ka nie bêdzie optymalna
	replace(minRow.begin(), minRow.end(), INT_MAX, 0);

	return minRow;
}

vector<int> Tsp_BB::colReduction(vector<vector<int>>& matrix)
{
	vector<int> minCol(matrix.size(), INT_MAX);

	// col[j] zawiera minimaln¹ waroœæ w wierszu i
	for (unsigned j = 0; j < minCol.size(); j++) {
		for (unsigned i = 0; i < minCol.size(); i++) {
			if (matrix[i][j] != -1 && matrix[i][j] < minCol[j])
				minCol[j] = matrix[i][j];
		}
	}

	// Odejmij minimaln¹ wartoœæ z ka¿dego elementu w kolumnie, tak aby by³a chocia¿ jedna wartoœæ 0
	for (unsigned i = 0; i < minCol.size(); i++) {
		for (unsigned j = 0; j < minCol.size(); j++) {
			if (matrix[j][i] != -1)
				matrix[j][i] -= minCol[i];
		}
	}
	// Aby algorytm dzia³a³ porpawnie potrzebne jest zabezpieczenie inaczej œcie¿ka nie bêdzie optymalna
	replace(minCol.begin(), minCol.end(), INT_MAX, 0);

	return minCol;
}

int Tsp_BB::calculateCost(vector<vector<int>>& matrix)
{
	// Redukcja wierszy
	vector<int> minRow = rowReduction(matrix);
	// Redukcja kolumn
	vector<int> minCol = colReduction(matrix);
	// ca³kowity oczekiwany koszt to suma wszystkich redukcji w tabeli macierzy
	return accumulate(minRow.begin(), minRow.end(), 0) + accumulate(minCol.begin(), minCol.end(), 0);
}

finalPath Tsp_BB::solveTSPBnB()
{
	// Obiekt porównania, który ma byæ u¿yty do tworzenia kopca, w naszym przypadku waga
	auto comp = [](const Branch& nl, const Branch& nr) {
		if (nl.wage < nr.wage) return false;
		if (nl.wage > nr.wage) return true;
		return true; };

	// Kolejka priorytetowa która przechowuje aktywne wêz³y wyszukiwania
	priority_queue<Branch, vector<Branch>, decltype(comp)> pq(comp);

	//Œcie¿ka przejœæ w drzewie
	vector<int> v;

	//Wstawienie miasta pocz¹tkowego
	v.push_back(0);

	//Ustawienie sumy zredukowanych wierszy i kolumny
	int sum = calculateCost(matrix);

	// Stworzenie korzenia drzewa i oblicznenie jego drogi
	// Rozpoczêcie algorytmu TSP od 0 wêz³a
	Branch root = Branch::rootNode(matrix, v, 0);

	//Ustawienie wartoœci zredukowanych wierszy i kolumny
	root.wage = sum;

	// dodaj korzeñ do kolejki aktywnych wêz³ów wyszukiwania
	pq.push(root);


	//Znajduje potomka z najmniejszym kosztem
	//Dodaje jego dzieci do kolejki a nastêpnie usuwa go z pamiêci
	while (!pq.empty())
	{
		// pobierz weze³ o najmniejszym koszcie
		Branch min = pq.top();
		// Znaleziony wêze³ jest usuwany z listy aktywnych wêz³ów
		pq.pop();
		// i przechowuje aktualnie odiedzany wêze³
		int i = min.curr_node;
		// JE¯ELI wszystkie wierzcho³ki(miasta) zosta³y odwiedzone
		if (min.node == matrix.size() - 1)
		{
			finalPath finalPath;
			// Powrót do miasta startowego
			min.connection.push_back(0);

			// Wyœwietlanie wierzcho³ków odwiedzonych
			finalPath.solution_path = min.connection;
			finalPath.cost = min.wage;
			return finalPath;
		}

		for (int j = 0; j < matrix.size(); j++)
		{
			// Dla potomka o minimalnej wadze tworzy krawêdŸ w drzewie
			if (min.adj_Matrix[i][j] != -1)
			{
				//Tworzymy nowy obiekt który jest potomkiem
				Branch next = Branch::newPath(min.adj_Matrix, min.connection, min.node + 1, i, j);

				// utwórz potomkai oblicz koszt jego drogi
				next.wage = min.wage + calculateCost(next.adj_Matrix) + min.adj_Matrix[i][j];

				// Dodaj potomka do listy aktywnych wêz³ów
				pq.push(next);

				//Usuwamy z pamiêci nowy obiekt
				next.~Branch();

			}
		}
		//Usuwamy z pamiêci stary obiekt
		min.~Branch();
	}
}