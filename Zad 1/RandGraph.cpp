#include "RandGraph.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <fstream>


using namespace std;

// Konstruktor Macierzy s�siedztwa
RandGraph::RandGraph(int SIZE)
{
	costMatrix.resize(SIZE, vector<int>(SIZE));
}

// Funkcja losuj�ca wagi kraw�dzi w macierzy s�siedztwa
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

// Funkcja wy�wietlaj�ca wylosowan� macierz s�siedztwa
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

// Funkcja wypisuj�ca wylosowan� macierz do pliku txt
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
