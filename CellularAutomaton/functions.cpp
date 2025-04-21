#include "functions.h"

sf::Vector2f get_mouse_pos(sf::RenderWindow* iw) {	return { (float)sf::Mouse::getPosition(*iw).x, (float)sf::Mouse::getPosition(*iw).y }; }
sf::Vector2f get_mouse_pos_desktop() {   return { (float)sf::Mouse::getPosition().x, (float)sf::Mouse::getPosition().y }; }
int getrandom(int a, int b) { return rand() % (b - a + 1) + a; }

void generate_automaton() {
    std::vector<int> birth, survive;
    int max_cnt = std::stoi(Gl::mode.getTypenbrs());
    for (int i = 1; i <= max_cnt; i++)
        if (getrandom(0, 1))
            survive.push_back(i);
    for (int i = 1; i <= max_cnt; i++)
        if (getrandom(0, 1))
            birth.push_back(i);

	Gl::tempA = TypeAutomaton(birth, survive, Gl::mode.getCntGen(), Gl::mode.getTypenbrs());
}

void Close(sf::RenderWindow* iw) {
    std::cerr << "Close!" << std::endl;
    Gl::running = 0;
    if (Gl::rendering.joinable()) {
        Gl::rendering.join();
    }
}

std::vector<int> string_to_mas(std::string s, char sep)
{
    s += sep;
    std::vector<int> Mas;
    int sz = s.size();
    std::string t = "";
    for (int i = 0; i < sz; i++) {
        if (s[i] == sep) {
            if (t != "")
                Mas.push_back(std::stoi(t));
            t = "";
        }
        else
            t += s[i];
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
