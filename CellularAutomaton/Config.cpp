#include "Config.h"




sf::Vector2i Config::windowSize = { 1620, 1000 };

int Config::SIZET = 500;
int Config::TPS = 30;
int Config::FPS = 30;
int Config::chance = 50;

std::vector<sf::Color> Config::GENER_COLORS = {};

TypeAutomaton Config::live      (s_to_mas1("3"          ), s_to_mas1("2 3"          ), 2,   "M", 1);
TypeAutomaton Config::maze      (s_to_mas1("3"          ), s_to_mas1("1 2 3 4 5"    ), 2,   "M", 1);
TypeAutomaton Config::caves     (s_to_mas1("5, 6, 7, 8" ), s_to_mas1("4 5 6 7 8"    ), 2,   "M", 1);
TypeAutomaton Config::diamoba   (s_to_mas1("3 5 6 7 8"  ), s_to_mas1("5 6 7 8"      ), 2,   "M", 1);
TypeAutomaton Config::carpet    (s_to_mas1("2 3 4"      ), s_to_mas1(""             ), 2,   "M", 1);
TypeAutomaton Config::dayNight  (s_to_mas1("3 6 7 8"    ), s_to_mas1("3 4 6 7 8"    ), 2,   "M", 1);
TypeAutomaton Config::bugs5     (s_to_mas1("34 - 45"    ), s_to_mas1("33 - 57"      ), 2,   "M", 5);
TypeAutomaton Config::modernArt (s_to_mas1("3"          ), s_to_mas1("1 2"          ), 60,  "M", 10);
TypeAutomaton Config::brianBrain(s_to_mas1("2"          ), s_to_mas1(""             ), 3,   "M", 1);
TypeAutomaton Config::starWars  (s_to_mas1("2"          ), s_to_mas1("3 4"          ), 4,   "M", 1);
TypeAutomaton Config::faders    (s_to_mas1("2"          ), s_to_mas1("2"            ), 25,  "M", 1);

std::string Config::pathBackground = "Resources/background.png";
std::string Config::pathButton = "Resources/buttons.png";
std::string Config::pathFont = "Resources/arial.ttf";

std::vector<int> s_to_mas1(std::string s, char sep, bool deleteRepeat)
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
        for (int i = s + 1; i < e; i++)
            Mas.push_back(i);
    }
    std::sort(Mas.begin(), Mas.end());
    if (deleteRepeat) {
        auto last = std::unique(Mas.begin(), Mas.end());
        Mas.erase(last, Mas.end());
    }
    return Mas;
}