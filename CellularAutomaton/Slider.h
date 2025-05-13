#pragma once
#include "Text.h"
#include "ButtonProt.h"
#include "functions.h"
#include "Global.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class Slider: public ButtonProt  {
public:
    static std::vector <Slider*> List;
    Slider(sf::RenderWindow* iw1, std::string title1, sf::Rect<float> rect1, sf::IntRect texture_rect1, sf::Font* font, int sizetext, sf::Color col_text1,\
        void (*func)(int a), int minvalue1, int maxvalue1, int (*getter1)()=nullptr);
    Slider(sf::RenderWindow* iw1, std::string title1, sf::Rect<float> rect1, sf::IntRect texture_rect1, Text example1, void (*func)(int a), int minvalue1,\
        int maxvalue1, int (*getter1)() = nullptr);
    void render();
    void check();
    void setCoord(sf::Vector2f crd);
private:
    void initSprite(sf::IntRect textute_rect1) override;
    void (*func)(int a);
    int (*getter)();
    void callfunc();
    void move(float len);
    int value = 0, max_value, min_value;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Rect<float> sliderrect, sliderlinerect;
    sf::CircleShape slidershape;
    sf::RectangleShape sliderline;
};