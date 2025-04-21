#pragma once
#include "Global.h"
#include "Text.h"
#include "functions.h"
#include <iostream>
#include <SFML//Graphics.hpp>

class ButtonProt {
protected:
	bool paint = true;
	int status = 0;
	Text text;
	sf::Rect<float> rect;
	sf::RenderWindow* iw;
	void virtual initSprite(sf::IntRect texture_rect1);
	virtual void check();
	virtual void render();
	virtual int  getStatus();
public:
	ButtonProt(sf::RenderWindow* iw1, std::string title1, sf::Rect<float> rect1, sf::Font* ifont1, int size_text1, sf::Color col_text1, bool paint=true);
	ButtonProt(sf::RenderWindow* iw1, std::string title1, sf::Rect<float> rect1, Text example1, bool paint1=true);
};