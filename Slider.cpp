#include "Slider.h"

std::vector<Slider*> Slider::List;
Slider::Slider(sf::RenderWindow* iw1, std::string title1, sf::Rect<float> rect1, sf::IntRect texture_rect1, sf::Font* ifont1, int size_text1, sf::Color col_text1, void(*func1)(int a), int minvalue1, int maxvalue1, int defaultvalue1) :
	func{ func1 }, 
	min_value{minvalue1}, 
	max_value{maxvalue1},
	value{defaultvalue1},
	ButtonProt(iw1, title1, rect1, ifont1, size_text1, col_text1, false)
{
	List.push_back(this);
	text.setonbutton(rect, "LEFTTOP");
	initSprite(texture_rect1);
	//text.printInfo();
}
Slider::Slider(sf::RenderWindow* iw1, std::string title1, sf::Rect<float> rect1, sf::IntRect texture_rect1, Text example1, void(*func1)(int a), int minvalue1, int maxvalue1, int defaultvalue1):
	func{ func1 },
	min_value{ minvalue1 },
	max_value{ maxvalue1 },
	value{ defaultvalue1 },
	ButtonProt(iw1, title1, rect1, example1, false)
{
	List.push_back(this);
	text.setonbutton(rect, "LEFTTOP");
	initSprite(texture_rect1);
	//text.printInfo();
}
void Slider::initSprite(sf::IntRect texture_rect1) {
	texture.loadFromImage(Gl::buttons, texture_rect1);
	sprite.setTexture(texture);

	int dx = 25;
	slidershape.setRadius(rect.height / 16);
	sliderrect = sf::Rect<float>({ (float)rect.left + dx, (float)(rect.top + rect.height * 0.6) }, { rect.height / 8, rect.height / 8 });
	sliderlinerect = sf::Rect<float>(sliderrect.getPosition(), {rect.width - 2 * dx, slidershape.getRadius() * 2});

	sprite.setScale(rect.width / sprite.getLocalBounds().width, rect.height / sprite.getLocalBounds().height);
	sliderline.setSize(sliderlinerect.getSize());

	slidershape.setPosition(sliderrect.getPosition());
	sprite.setPosition(rect.getPosition());
	sliderline.setPosition(sliderlinerect.getPosition());


	sliderline.setFillColor(Gl::darkGrey);
	slidershape.setFillColor({ sf::Color::Black });
}


void Slider::callfunc() {
	//std::cout << "slider\n";
	func(value);
}

void Slider::check() {
	int new_status = getStatus();
	if (new_status == 2// && status == 1
		) {
		sf::Vector2f mouse_pos = get_mouse_pos(iw);
		value = std::max(0, std::min((int)((mouse_pos.x - sliderlinerect.left) / sliderlinerect.width * (max_value - min_value)), (max_value - min_value))) + min_value;
		//std::cout << "Value: " << value << "\n";
		callfunc();
	}
	status = new_status;

	move((float)(value - min_value) / (max_value - min_value) * (sliderlinerect.width - sliderrect.width));
	std::string title = text.str, new_title;

	for (int i = 0; i < title.size(); i++) {
		new_title += title[i];
		if (title[i] == ':')
			break;
	}
	text.str = new_title;
	text.setString(text.str + std::to_string(value));
}

void Slider::render() {

	iw->draw(sprite);
	iw->draw(sliderline);
	iw->draw(slidershape);
	text.render();
}

void Slider::move(float len)
{
	sliderrect.left = sliderlinerect.left + len;
	slidershape.setPosition(sliderrect.getPosition());
}
