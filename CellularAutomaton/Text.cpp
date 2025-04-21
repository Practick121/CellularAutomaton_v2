#include "Text.h"

std::vector<Text*> Text::List;

Text::Text(){}

Text::Text(const Text& text) :
	Text(text.iw, text.str, text.font, text.charsize, text.color, text.rect.getPosition(), true)
{
}

Text::Text(sf::RenderWindow* iw1, std::string str1, sf::Font* font1, int charsize1, sf::Color color1, sf::Vector2f coord1, bool renderiable1) :
	orig_str{ str1 }
{
	if (renderiable)
		Text::List.push_back(this);
	iw = iw1;
	str = str1;
	charsize = charsize1;
	color = color1;
	font = font1;
	renderiable = renderiable1;
	text.setString(str1);
	text.setFont(*font1);
	text.setFillColor(color);
	text.setCharacterSize(charsize);
	text.setStyle(sf::Text::Regular);
	rect = text.getLocalBounds();
	setCoord(coord1);
	text.setPosition(rect.getPosition());
}

void Text::setCoord(sf::Vector2f coord1) {
	rect = sf::Rect<float>{ coord1, rect.getSize() };
	text.setPosition(rect.getPosition());
}

void Text::setonbutton(sf::Rect<float> but_rect, std::string pos) {
	rect = text.getLocalBounds();
	if (pos == "CENTER") {
		rect.left = but_rect.left + (but_rect.width - rect.width) / 2;
		rect.top = but_rect.top + (but_rect.height - rect.height) / 2;
		text.setPosition(rect.getPosition());
	}
	else if (pos == "LEFTTOP") {
		rect.left = but_rect.left + (but_rect.width - rect.width) / 4;
		rect.top = but_rect.top + (but_rect.height - rect.height) / 4;
		text.setPosition({ rect.left, rect.top });
	}
}

void Text::setString(std::string newstr) {
	str = newstr;
	text.setString(str);
}

const sf::Font* Text::getFont()
{
	return font;
}

void Text::init()
{

}

void Text::render() {
	iw->draw(text);
}

void Text::move(sf::Vector2f move1)
{
	rect = sf::Rect<float>{ rect.getPosition() + move1, rect.getSize()};
	text.setPosition(rect.getPosition());
}

void Text::printInfo()
{
	std::cout << "charsize: " << charsize << ' ' << text.getCharacterSize() << '\n';
	std::cout << "str_orig: " << orig_str << ' ' << "str: " << str  << '\n';
	std::cout << "rect: " << rect.left << ' ' << rect.top << ' ' << rect.width << ' ' << rect.height << '\n';
	std::cout << "font: " << text.getFont() << '\n';
}
