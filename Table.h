#pragma once
#include "Camera.h"
#include "TypeAutomaton.h"
#include "Global.h"
#include "functions.h"
#include "Config.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Table {
public:
	Table() = default;
	Table(sf::RenderWindow* iw, Camera* camera1, sf::Rect<float> rect1);
	sf::Rect<float> rect;
	int brush = Gl::CNT_GENER;
	void setcustom();
	void setrandom();
	void printmatrix();
	void render();
	void clean();
	void check();
	void nextgeneration();
	void setmatrix(std::vector<std::vector<int>>* M);
	std::vector<std::vector<int>> getmatrix();
private:
	
	sf::Rect<float> cellrect;
	bool pressed = false;
	sf::RenderWindow* iw = nullptr;
	Camera* camera = nullptr;

	std::vector<sf::Vertex> vertexarray;
	std::vector <std::vector<int>> M;
	std::vector<std::pair<sf::Vector2f, int>> update;
	std::vector<sf::Color> Color_for_Gener;

	bool ispressed();
	void updateVertexArray();

	void setColor(int i, int j, sf::Color col);
	void addQuad(int i, int j);
	int getcntnbrs(int i, int j);
	bool isalive(int i, int j);

	template <typename Func>
	void cellForEach(Func func1);
};

template<typename Func>
void Table::cellForEach(Func func1)
{
	for (int i = 0; i < Config::SIZET; i++) {
		for (int j = 0; j < Config::SIZET; j++) {
			func1(i, j);
		}
	}
}
