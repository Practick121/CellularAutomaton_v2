#pragma once
#include <SFML/Graphics.hpp>
#include "CellAutomaton.h"
#include "TypeAutomaton.h"
#include "defenition.h"
#include "functions.h"

class Table {
public:
	float zoom = 1;
	bool pressed = false;
	int brush = 1;
	TypeAutomaton mode;
	sf::Vector2f mouselastpos;
	sf::Rect<float> tablerect, cellrect;
	sf::RectangleShape cellshape, tableshape, deathshape;
	sf::RenderWindow* w1;
	Table();
	Table(sf::RenderWindow* w1, int width, int height);
	void setmatrix(std::vector<std::vector<int>>* M), render(), nextgeneration(), setrandom(),\
		clean(), check(), setcustom(), exit();
	bool ispressed(), myintersects(sf::Rect <float> a, sf::Rect<float> b );
	std::vector<std::vector<int>> getmatrix();
private:
	CellAutomaton automaton;
};
