#include "Button.h"
std::vector<Button*> Button::List;
std::vector <std::string> Button::active;
std::map <std::string, TypeAutomaton> Button::mapactive;
void Button::init(sf::RenderWindow* window, std::string title1, sf::Font* font1, sf::Vector2f coord1, sf::Vector2f size1, int sizetext1, sf::Color colbut1,\
    sf::Color coltext1, void (*func1)(), bool texture_on1) {
    List.push_back(this);
    w1 = window; // куда отрисовывается объект
    title = title1; // название кнопки (для пользователя)
    coord = coord1; // координаты кнопки
    texture_on = texture_on1; // включена/выключена текстура у кнопки
    pressed = 0; // нажата/отжата кнопка
    size = size1; // размер кнопки
    colbut = colbut1; // цвет кнопки
    coltext = coltext1; // цвет текста
    func = func1; // функция, которую выполняет кнопка (без аргументов)
    rect = sf::Rect<float>(coord, size); // прямоугольник кнопки, для проверки касания мыши
	sizetext = sizetext1; // размер текста
	font = font1; // ссылка на шрифт текста
    for (int i = 0; i < 4; i++) { // каждому из 4х спрайтов задаётся текстура и координата
        rectshape[i].setSize(size1); 
        rectshape[i].setPosition(coord);
    } // 0 - обычный цвет, 1 - цвет при наведении, 2 - цвет при нажатии
    rectshape[0].setFillColor(colbut);
    rectshape[1].setFillColor(Def::Grey);
    rectshape[2].setFillColor(Def::darkGrey);
    if (std::find(active.begin(), active.end(), title) != active.end())
        rectshape[3].setFillColor(sf::Color(176, 0, 0));

    text.init(w1, title, font1, sizetext, coltext, {});
    text.setonbutton(rect);

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
    sprites[1].setColor(Def::Grey);
    sprites[2].setColor(Def::darkGrey);
    sprites[3].setColor(sf::Color(176, 0, 0));
}
void Button::render() {
    if ((title == "RUN" && Def::RUN == 1) || (title == "STOP" && Def::RUN == 0) || (std::find(active.begin(), active.end(), title) != active.end() && mapactive[title] == Def::mode)) {
        draw(3);
    }
    else if (pressed == 2 && title != "") {
        draw(2);
    }
    else if (rect.contains(get_mouse_pos(w1)) && title != "") {
        draw(1);
    }
    else {
        draw(0);
    }
    text.render();
}
void Button::draw(int num) {
    if (texture_on)
        w1->draw(sprites[num]);
    else
        w1->draw(rectshape[num]);
}
void Button::check() {
    if (title == "NEIGHBOURS:") {
        text.setString(title + std::to_string(Def::typecheckingneighbours));
    }
    int condition = ispressed();
    if (condition == 2 && pressed == 1)
        callfunc();
    
    pressed = condition;
}
void Button::callfunc() {
    func();
}
int Button::ispressed() {
    sf::Vector2 <float> mouse_pos = get_mouse_pos(w1);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && rect.contains(mouse_pos))
        return 2;
    if (rect.contains(mouse_pos))
        return 1;
    return 0;
}

