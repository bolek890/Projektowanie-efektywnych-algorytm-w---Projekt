#pragma once
#include <vector>

using namespace std;

// Klasa przechowuj�ca �cie�ke i wage dla wyniku dzia�ania algorytmu
class finalPath
{
public:
	int cost = 0;
	vector<int> solution_path{ 0 };
};