#pragma once
#include <vector>

using namespace std;

// Klasa przechowuj¹ca œcie¿ke i wage dla wyniku dzia³ania algorytmu
class finalPath
{
public:
	int cost = 0;
	vector<int> solution_path{ 0 };
};