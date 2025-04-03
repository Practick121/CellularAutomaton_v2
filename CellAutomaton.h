#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "TypeAutomaton.h"
#include "defenition.h"
class CellAutomaton {
public:
	static const int SIZET = 200;
	std::vector <std::vector<int>> M;
	CellAutomaton();
	static int getsizet();
	int getrandom(int a, int b), getcntnbrs(int i, int j);
	void nextgeneration(TypeAutomaton mode), printmatrix(), clean(), setrandom();
};