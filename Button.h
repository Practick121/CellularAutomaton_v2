#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "functions.h"
class Button {
public: 
    static std::vector <Button*> List;
    Button(sf::RenderWindow* w, std::string str1, sf::Vector2f coord1, sf::Vector2f size1, int sizetext, sf::Color col1, sf::Color col_text1, void (*func)());
    void render(), check();
    bool ispressed();
private:
    sf::Rect <float> rect;
    sf::RectangleShape rectshape[4];
    sf::Vector2f coord, size;
    sf::Color colbut, coltext;
    sf::Text text;
    sf::Font font;
    std::string title;
    sf::RenderWindow* w1;
    bool pressed;
    void (*func)();
};