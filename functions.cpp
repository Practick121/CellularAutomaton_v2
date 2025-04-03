#include "functions.h"

sf::Vector2f get_mouse_pos(sf::RenderWindow* w1) {
	return { (float)sf::Mouse::getPosition(*w1).x, (float)sf::Mouse::getPosition(*w1).y };
}
