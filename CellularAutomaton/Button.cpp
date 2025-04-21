#include "Button.h"
std::vector<Button*> Button::List, Button::Active;

Button::Button(sf::RenderWindow* iw1, std::string title1, sf::Rect<float> rect1, sf::IntRect texture_rect1, sf::Font* ifont1, int sizetext1, sf::Color col_text1, void (*func1)(), std::pair<int, bool> num_set1, bool paint1) :
    ButtonProt(iw1, title1, rect1, ifont1, sizetext1, col_text1, paint1),
    func{ func1 },
    num_set{ num_set1 }
{
    init(texture_rect1, title1);
}


Button::Button(sf::RenderWindow* iw1, std::string title1, sf::Rect<float> rect1, sf::IntRect texture_rect1, Text example1, void(*func1)(), std::pair<int, bool> num_set1, bool paint1) :
    func{ func1 },
    ButtonProt(iw1, title1, rect1, example1, paint1),
    num_set{ num_set1 }
{
    init(texture_rect1, title1);
}

void Button::init(sf::IntRect texture_rect1, std::string title1)
{
    List.push_back(this);
    initSprite(texture_rect1);
    while ((int)Button::Active.size() - 1 < num_set.first) {
        Active.push_back(nullptr);
    }

}

void Button::initSprite(sf::IntRect texture_rect1) {
    texture.loadFromImage(Gl::buttons, texture_rect1);
    for (int i = 0; i < 4; i++) {
        sprite[i].setTexture(texture);
        sprite[i].setPosition({ rect.left, rect.top });
        sprite[i].setScale(rect.width / sprite[i].getLocalBounds().width, rect.height / sprite[i].getLocalBounds().height);
    }
    sprite[1].setColor(sf::Color(210, 210, 210));
    sprite[2].setColor(Gl::darkGrey);
    sprite[3].setColor(sf::Color(176, 0, 0));
}

void Button::render() {
    if (text.orig_str == "NEIGHBOURS:")
        text.setString(text.orig_str + Gl::mode.getTypenbrs());
    if (!paint)
        iw->draw(sprite[0]);
	else if (Active[num_set.first] == this && num_set.second)
		iw->draw(sprite[3]);
	else
		iw->draw(sprite[status]);
	text.render();  
}

void Button::check() {
    int new_status = getStatus();
	if (status == 1 && new_status == 2) {
        Active[num_set.first] = this;
		callfunc();
	}
	status = new_status;
}

void Button::setCoord(sf::Vector2f crd1)
{
    rect = { crd1, rect.getSize() };
    for (int i = 0; i < 4; i++)
        sprite[i].setPosition(rect.getPosition());
    text.setonbutton(rect);
}


void Button::callfunc() {
    func();
}
