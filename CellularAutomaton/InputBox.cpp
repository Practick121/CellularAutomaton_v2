#include "InputBox.h"

std::vector<InputBox*> InputBox::List;

InputBox::InputBox() {}

void InputBox::init(sf::RenderWindow* iw1, std::string title1, sf::Rect<float> rect1, sf::Font* ifont1, int sizetext1, int sizetext2)
{
	iw = iw1;
	rect = rect1;
	title = title1;
	if (sizetext1 == -1) {
		sizetext1 = rect1.getSize().y / 2;
	}
	if (sizetext2 == -1) {
		sizetext2 = rect1.getSize().y / 2;
	}
	
	input_text = Text(iw1, "", ifont1, sizetext1, sf::Color::Black, {rect.left + rect.height / 8, rect.top + rect.height / 4});
	title_text = Text(iw1, title1, ifont1, sizetext2, sf::Color::Black, {rect.left + rect.height / 8, rect.top + rect.height / 4});
	InputBox::List.push_back(this);
	shape.setSize(rect.getSize());
	shape.setPosition(rect.getPosition());
	shape.setFillColor(Gl::Grey);
	input_text.move({title_text.rect.width, 0});
}

void InputBox::render() 
{
	if (iw != nullptr)
		iw->draw(shape);
	input_text.render();
	title_text.render();
}

void InputBox::check(sf::Event* ev)
{
	sf::Vector2f mouse_pos = get_mouse_pos(iw);
	
	if (ev->type == sf::Event::MouseButtonPressed && ev->mouseButton.button == sf::Mouse::Left && rect.contains(mouse_pos))
		active = true;
	if (active && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		active = false;
	if (active && ev->type == sf::Event::TextEntered) {
		char c = static_cast<char>(ev->text.unicode);
		if (c == '\b' && input_text.str.size() != 0) {
			content = content.substr(0, content.size() - 1);
			input_text.setString(content);
		}
		else if (c != '\b' && input_text.text.getLocalBounds().width <= rect.width - input_text.text.getCharacterSize() - title_text.rect.width) {
			content += c;
			input_text.setString(content);
		}
	}
	if (active && ev->type == sf::Event::MouseButtonPressed && ev->mouseButton.button == sf::Mouse::Left && !rect.contains(mouse_pos)) {
		active = false;
	}
}

void InputBox::deactive()
{
	active = false;
}

void InputBox::setCoord(sf::Vector2f crd)
{
	rect = { crd, rect.getSize() };
	input_text.setCoord({ rect.left + rect.height / 8, rect.top + rect.height / 4 });
	input_text.move({ title_text.rect.width, 0 });
	title_text.setCoord({ rect.left + rect.height / 8, rect.top + rect.height / 4 });
	shape.setPosition(rect.getPosition());
}

