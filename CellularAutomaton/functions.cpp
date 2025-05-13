#include "functions.h"

sf::Vector2f get_mouse_pos(sf::RenderWindow* iw) {	return { (float)sf::Mouse::getPosition(*iw).x, (float)sf::Mouse::getPosition(*iw).y }; }
sf::Vector2f get_mouse_pos_desktop() {   return { (float)sf::Mouse::getPosition().x, (float)sf::Mouse::getPosition().y }; }
int getrandom(int a, int b) { return rand() % (b - a + 1) + a; }

void generate_automaton() {
    std::vector<int> birth, survive;
    int max_cnt = 0;
    int r = Gl::mode.getRadius();
    if (Gl::mode.getTypeCheck() == "M") {
        max_cnt = (2 * r + 1) * (2 * r + 1);
    }
    else if (Gl::mode.getTypeCheck() == "N") {
        max_cnt = 2 * r * r - 2 * r + 1;
    }
    for (int i = 1; i <= max_cnt; i++)
        if (getrandom(0, 1))
            survive.push_back(i);
    for (int i = 1; i <= max_cnt; i++)
        if (getrandom(0, 1))
            birth.push_back(i);
    Gl::mode.setBirth(birth);
    Gl::mode.setSurvive(survive);
}

void Close(sf::RenderWindow* iw) {
    std::cerr << "Close!" << std::endl;
    Gl::running = 0;
    if (Gl::rendering.joinable()) {
        Gl::rendering.join();
    }
}

std::vector<int> string_to_mas(std::string s, char sep, bool deleteRepeat)
{
    s += sep;
    std::vector<int> Mas;
    std::vector<int> Ranges;
    int sz = s.size();
    std::string t = "";
    for (int i = 0; i < sz; i++) {
        if (s[i] == sep) {
            if (t != "") {
                Mas.push_back(std::stoi(t));
            }
            t = "";
        }
        else if (s[i] == '-')
            Ranges.push_back(Mas.size() - 1);
        else
            t += s[i];
    }
    for (auto el : Ranges) {
        if (el == Mas.size() - 1)
            break;
        int s = Mas[el], e = Mas[el + 1];
        for (int i = s; i <= e; i++)
            Mas.push_back(i);
    }
    
    if (deleteRepeat) {
        std::sort(Mas.begin(), Mas.end());
        auto last = std::unique(Mas.begin(), Mas.end());
        Mas.erase(last, Mas.end());
    }
    return Mas;
}

void initGenerColors(sf::Color live) {
    int n = Gl::mode.getCntGen();
    std::vector <sf::Color> Mas = { { 0, 0, 0, 0 }, live };
    int a = 255;
    sf::Uint8 r1 = live.r, g1 = live.g, b1 = live.b;
    while (Mas.size() < Gl::mode.getCntGen() + 1) {
        a -= a / n;
        n--;
        sf::Color c = sf::Color(r1, g1, b1, a);
        Mas.push_back(c);
    }
    Config::GENER_COLORS = Mas;
}
