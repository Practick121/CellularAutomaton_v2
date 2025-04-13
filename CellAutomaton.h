#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <atomic>
#include "TypeAutomaton.h"
#include "defenition.h"
class CellAutomaton {
public:
	static int SIZET;
	std::vector <std::vector<int>> M;
	std::vector<std::pair<sf::Vector2f, int>> update;
	CellAutomaton();
	static int getsizet();
	int getrandom(int a, int b), getcntnbrs(int i, int j);
	void nextgeneration(TypeAutomaton mode), printmatrix(), clean(), setrandom(), setcustom();
};
