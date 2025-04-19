#include "Global.h"


int Gl::RUN = 0;
int Gl::CNT_GENER = 1;
bool Gl::focused = true;
TypeAutomaton Gl::tempA({}, {});
std::string Gl::input = "INPUT: ";
int Gl::running = 1, Gl::CLOSE = 0;
sf::Image Gl::buttons, Gl::background;
sf::Color Gl::Grey = sf::Color(160, 160, 160), Gl::darkGrey = sf::Color(80, 80, 80), Gl::brightRed = sf::Color(255, 83, 73);

TypeAutomaton Gl::mode = Config::live;

std::thread Gl::rendering;


