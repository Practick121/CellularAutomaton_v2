#pragma once
#include "Text.h"
#include "functions.h"
#include "Global.h"
#include "ButtonProt.h"
#include "Config.h"
#include "Table.h"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class Button: ButtonProt {
public: 
    static std::vector <Button*> Active; // ������ ������� - �������� ������ �� ������� ���������, ������ ������� - ..
    static std::vector <Button*> List;
    void render();
    void check();
    void setCoord(sf::Vector2f crd1);
    Button(sf::RenderWindow* iw1, std::string title1, sf::Rect<float> rect1, sf::IntRect texture_rect1, sf::Font* ifont1, int sizetext, sf::Color col_text1, void (*func1)(), std::pair<int, bool> num_set1 = { 0, false }, bool paint = true);
    Button(sf::RenderWindow* iw1, std::string title1, sf::Rect<float> rect1, sf::IntRect texture_rect1, Text example1, void (*func1)(), std::pair<int, bool> num_set1 = { 0, false }, bool paint = true);

private:
    std::pair<int, bool> num_set; // � ������ ��������� �������� ������ ��������� ������ ������/ ������������ �� ��� ��������
    void init(sf::IntRect textue_rect1, std::string title1);
    void initSprite(sf::IntRect texture_rect1) override;
    void callfunc();
    sf::Sprite sprite[4];
    sf::Texture texture;
    void (*func)();
};


