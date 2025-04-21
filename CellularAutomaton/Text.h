#pragma once 
#include "Global.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>

class Text {
public:
	static std::vector<Text*> List;
	sf::Text text;
	std::string str, orig_str;
	sf::Rect <float> rect;
	Text();
	Text(const Text& text);
	Text(sf::RenderWindow* iw1, std::string str1, sf::Font* font1 ,int charsize1, sf::Color color1, sf::Vector2f coord1, bool renderiable=true);
	void render();
	void move(sf::Vector2f move1);
	void printInfo();
	void setCoord(sf::Vector2f coord1);
	void setonbutton(sf::Rect<float> but_rect, std::string pos="CENTER");
	void setString(std::string newstr);
	const sf::Font* getFont();
private:
	sf::Font* font;
	bool renderiable;
	void init();
	sf::RenderWindow* iw;
	sf::Color color;
	int charsize;
};
