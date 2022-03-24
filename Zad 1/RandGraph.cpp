#include "RandGraph.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <fstream>


using namespace std;

// Konstruktor Macierzy s¹siedztwa
RandGraph::RandGraph(int SIZE)
{
	costMatrix.resize(SIZE, vector<int>(SIZE));
}

// Funkcja losuj¹ca wagi krawêdzi w macierzy s¹siedztwa
void RandGraph::startRand(int SIZE)
{
	for (size_t i = 0; i < SIZE; i++) 
	{
		for (size_t j = 0; j < SIZE; j++) 
		{
			costMatrix[i][j]  =(rand() % 998) + 1;
			if (i == j)
				costMatrix[i][j] = -1;
		}
	}
}

// Funkcja wyœwietlaj¹ca wylosowan¹ macierz s¹siedztwa
void RandGraph::showAdjMt(int SIZE)
{
	for (size_t i = 0; i < SIZE; i++)
	{
		cout << endl;

		for (size_t j = 0; j < SIZE; j++)
		{
			cout << costMatrix[i][j] << " ";
		}
	}
}

// Funkcja wypisuj¹ca wylosowan¹ macierz do pliku txt
void RandGraph::saveToFile(int SIZE, string fileName)
{
	fstream file;
	file.open(fileName.c_str(), ios::out);
	file << SIZE;
	for (size_t i = 0; i < SIZE; i++)
	{
		file << endl;

		for (size_t j = 0; j < SIZE; j++)
		{
			file << costMatrix[i][j] << " ";
		}
	}


	file.close();
}
