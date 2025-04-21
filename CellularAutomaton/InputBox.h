#pragma once
#include "Text.h"
#include "functions.h"
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class InputBox {
public:
	static std::vector<InputBox*> List;
	InputBox();
	void init(sf::RenderWindow* iw1, std::string title1, sf::Rect<float> rect1, sf::Font* ifont1, int sizetext1=-1, int sizetext2=-1);
	void render();
	void check(sf::Event* ev);
	void deactive();
	void setCoord(sf::Vector2f crd);
	std::string content;
private:
	std::string title;
	bool active = false;
	Text input_text, title_text;
	sf::RenderWindow* iw;
	sf::RectangleShape shape;
	sf::Rect<float> rect;
};