#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <map>
#include "Text.h"
#include "functions.h"
#include "defenition.h"

class Button {
public: 
    static std::vector <Button*> List;
    virtual void init(sf::RenderWindow* w, std::string str1, sf::Font* font, sf::Vector2f coord1, sf::Vector2f size1, int sizetext, sf::Color col1, sf::Color col_text1, void (*func)(), bool texture_on=true) final;
    void render(), draw(int num=-1);
    virtual void check();
    int ispressed(); // 0 - мышь не на кнопке, 1 - мышь на кнопке и отжата, 2 - мышь на кнопке и нажата
    virtual void callfunc();
    static std::vector <std::string> active;
    static std::map <std::string, TypeAutomaton> mapactive;
    sf::RenderWindow* w1;
private:
    sf::Sprite sprites[4];
    sf::Texture texture;
    sf::Rect <float> rect;
    sf::RectangleShape rectshape[4];
    sf::Vector2f coord, size;
    sf::Color colbut, coltext;
    Text text;
    sf::Font* font;
    int sizetext;
    std::string title;
    bool texture_on;
    int pressed = 0;
    void (*func)();
};
;
