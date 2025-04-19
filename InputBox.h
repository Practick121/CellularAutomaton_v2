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
	void init(sf::RenderWindow* iw1, std::string title1, sf::Rect<float> rect1, sf::Font* ifont1);
	void render();
	void check(sf::Event* ev);
	void deactive();
	std::string content;
private:
	std::string title;
	bool active = false;
	Text input_text, title_text;
	sf::RenderWindow* iw;
	sf::RectangleShape shape;
	sf::Rect<float> rect;
};
