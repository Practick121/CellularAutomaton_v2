#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <map>
#include "functions.h"
#include "defenition.h"

class Button {
public: 
    static std::vector <Button*> List;
    Button(sf::RenderWindow* w, std::string str1, sf::Vector2f coord1, sf::Vector2f size1, int sizetext, sf::Color col1, sf::Color col_text1, void (*func)(), bool texture_on=true);
    void render(), check(), draw(int num=-1);
    bool ispressed();
    virtual void callfunc();
    std::vector <std::string> active = { "RUN", "STOP", "LIVE", "CARPET", "MAZE", "CAVES", "DAYNIGHT", "DIAMOEBA" };
    std::map <std::string, TypeAutomaton> mapactive = { {"LIVE", Def::liveA}, {"CARPET", Def::carpetA}, {"DIAMOEBA", Def::diamobaA},\
        {"DAYNIGHT", Def::daynightA}, { "MAZE", Def::mazeA }, { "CAVES", Def::cavesA } };
    sf::RenderWindow* w1;
private:
    sf::Sprite sprites[4];
    sf::Texture texture;
    sf::Rect <float> rect;
    sf::RectangleShape rectshape[4];
    sf::Vector2f coord, size;
    sf::Color colbut, coltext;
    sf::Text text;
    sf::Font font;
    std::string title;
    bool pressed, texture_on;
    void (*func)();
};

class Button1: public Button {
public:
    Button1(sf::RenderWindow* w, std::string str1, sf::Vector2f coord1, sf::Vector2f size1, int sizetext, sf::Color col1, sf::Color col_text1, void (*func)(sf::RenderWindow* w));
    void callfunc() override;

private:
    void (*func)(sf::RenderWindow* w1);
};
