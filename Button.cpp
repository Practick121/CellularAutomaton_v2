#include "Button.h"
std::vector<Button*> Button::List;
Button::Button(sf::RenderWindow* window, std::string title1, sf::Vector2f coord1, sf::Vector2f size1, int sizetext, sf::Color colbut1, sf::Color coltext1, void (*func1)(), bool texture_on1) {
    List.push_back(this);
    w1 = window;
    texture_on = texture_on1;
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
    if (std::find(active.begin(), active.end(), title) != active.end())
        rectshape[3].setFillColor(sf::Color(176, 0, 0));
    font.loadFromFile("ariali.ttf");
    text.setFont(font);
    text.setString(title);
    text.setFillColor(coltext);
    text.setCharacterSize(sizetext);
    text.setStyle(sf::Text::Bold);
    float text_width = text.getLocalBounds().width, text_height = text.getLocalBounds().height;
    text.setPosition(coord + sf::Vector2f{ (size.x - text_width) / 2, (size.y - text_height) / 2 });
    std::vector<std::string> temp = { "5", "15", "30", "60", "120" };
    if (std::find(temp.begin(), temp.end(), title) != temp.end()) {
        texture.loadFromImage(Def::buttons, sf::IntRect(643, 284, 88, 75));
        std::cout << "loaded1\n";
    }
    else {
        texture.loadFromImage(Def::buttons, sf::IntRect(234, 77, 165, 72));
        std::cout << "loaded2\n";
    }
    for (int i = 0; i < 4; i++) {
        sprites[i].setTexture(texture);
        sprites[i].setPosition(coord);
        sprites[i].setScale(rect.width / sprites[i].getLocalBounds().width, rect.height / sprites[i].getLocalBounds().height);
    }
    sprites[0].setColor(colbut);
    sprites[1].setColor(sf::Color(255, 255, 255));
    sprites[2].setColor(Def::darkGrey);
    sprites[3].setColor(sf::Color(176, 0, 0));
}
void Button::render() {
    /*if ((title == "RUN" && Def::RUN == 1) || (title == "STOP" && Def::RUN == 0) || std::find(active.begin(), active.end(), title) != active.end() && mapactive[title] == Def::mode) {
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
    (*w1).draw(text);*/

    if ((title == "RUN" && Def::RUN == 1) || (title == "STOP" && Def::RUN == 0) || std::find(active.begin(), active.end(), title) != active.end() && mapactive[title] == Def::mode) {
        draw(3);
    }
    else if (ispressed() && title != "") {
        draw(2);
    }
    else if (rect.contains(get_mouse_pos(w1)) && title != "") {
        draw(1);
    }
    else {
        draw(0);
    }
    w1->draw(text);
}
void Button::draw(int num) {
    if (texture_on)
        w1->draw(sprites[num]);
    else
        w1->draw(rectshape[num]);
}
void Button::check() {
    if (ispressed()) {
        if (!pressed) {
            std::cout << "Button is pressed\n";
            callfunc();
        }
        pressed = true;
    }
    else {
        pressed = false;
    }
}
void Button::callfunc() {
    std::cout << "base\n";
    func();
}
bool Button::ispressed() {
    sf::Vector2 <float> mouse_pos = get_mouse_pos(w1);
    return (sf::Mouse::isButtonPressed(sf::Mouse::Left) && rect.contains(mouse_pos));
}

Button1::Button1(sf::RenderWindow* w1, std::string str1, sf::Vector2f coord1, sf::Vector2f size1, int sizetext, sf::Color col1, sf::Color col_text1, void (*func1)(sf::RenderWindow* window)): \
        Button(w1, str1, coord1, size1, sizetext, col1, col_text1, []() {}) {
    func = func1;
}
void Button1::callfunc() {
    std::cout << "son\n";
    func(w1);
}
