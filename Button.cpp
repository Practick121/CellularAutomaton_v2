#include "Button.h"
std::vector<Button*> Button::List;
Button::Button(sf::RenderWindow* window, std::string title1, sf::Vector2f coord1, sf::Vector2f size1, int sizetext, sf::Color colbut1, sf::Color coltext1, void (*func1)()) {
    List.push_back(this);
    w1 = window;
    pressed = false;
    coord = coord1;
    size = size1;
    colbut = colbut1;
    coltext = coltext1;
    title = title1;
    func = func1;
    rect = sf::Rect<float>(coord, size);
    for (int i = 0; i < 4; i++) {
        rectshape[i].setSize(size1);
        rectshape[i].setPosition(coord);
    }
    rectshape[0].setFillColor(colbut);
    rectshape[1].setFillColor(Def::Grey);
    rectshape[2].setFillColor(Def::darkGrey);
    if (title == "RUN" || title == "STOP")
        rectshape[3].setFillColor(sf::Color::Green);
    font.loadFromFile("ariali.ttf");
    text.setFont(font);
    text.setString(title);
    text.setFillColor(coltext);
    text.setCharacterSize(sizetext);
    text.setStyle(sf::Text::Bold);
    float text_width = text.getLocalBounds().width, text_height = text.getLocalBounds().height;
    text.setPosition(coord + sf::Vector2f{ (size.x - text_width) / 2, (size.y - text_height) / 2 });

}
void Button::render() {
    if ((title == "RUN" && Def::RUN == 1) || (title == "STOP" && Def::RUN == 0)) {
        (*w1).draw(rectshape[3]);
    }
    else if (ispressed() && title != "") {
        (*w1).draw(rectshape[2]);
    }
    else if (rect.contains(get_mouse_pos(w1)) && title != "") {
        (*w1).draw(rectshape[1]);
    }
    else {
        (*w1).draw(rectshape[0]);
    }
    (*w1).draw(text);
}
void Button::check() {
    if (ispressed()) {
        if (!pressed) {
            std::cout << "Button is pressed\n";
            func();
        }
        pressed = true;
    }
    else {
        pressed = false;
    }
}
bool Button::ispressed() {
    sf::Vector2 <float> mouse_pos = get_mouse_pos(w1);
    return (sf::Mouse::isButtonPressed(sf::Mouse::Left) && rect.contains(mouse_pos));
}
