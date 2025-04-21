#include "ButtonProt.h"

void ButtonProt::check() { std::cout << "checkProt\n"; }
void ButtonProt::render() { std::cout << "renderProt\n"; }
void ButtonProt::initSprite(sf::IntRect texture_rect1) { std::cout << "initSpriteProt\n"; }

ButtonProt::ButtonProt(sf::RenderWindow* iw1, std::string title1, sf::Rect<float> rect1, sf::Font* ifont1, int size_text1, sf::Color col_text1, bool paint1) :
	iw{ iw1 },
	rect{ rect1 },
	paint{ paint1 },
	text{ Text(iw1, title1, ifont1, size_text1, col_text1, {0, 0}) }
{
	text.setonbutton(rect, "CENTER");
}

ButtonProt::ButtonProt(sf::RenderWindow* iw1, std::string title1, sf::Rect<float> rect1, Text example1, bool paint1) :
	iw{ iw1 },
	rect{ rect1 },
	paint{ paint1 },
	text{example1}
{
	text.orig_str = title1;
	text.setString(title1);
	text.setonbutton(rect, "CENTER");

}

int ButtonProt::getStatus()
{	
	sf::Vector2f mouse_pos = get_mouse_pos(iw);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && rect.contains(mouse_pos))
		return 2;
	else if (rect.contains(mouse_pos))
		return 1;
	else
		return 0;
}
