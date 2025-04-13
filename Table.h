#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <atomic>
#include "CellAutomaton.h"
#include "TypeAutomaton.h"
#include "defenition.h"
#include "functions.h"

class Table {
public:
	int zoom = 1;
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
		clean(), check(), setcustom();
	bool ispressed();
	void updateVertexArray();
	void setColor(int i, int j, sf::Color col);
	int getrandom(int a, int b);
	std::vector<std::vector<int>> getmatrix();
	std::vector<sf::Vertex> vertexarray;
private:
	void addQuad(int i, int j);
	CellAutomaton automaton;
};
