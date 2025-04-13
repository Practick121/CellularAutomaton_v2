#include "defenition.h"

sf::Vector2f Def::windowsize = { 1210 * 1.3, 720 * 1.3 };
int Def::FPS = 30;
int Def::TPS = 30;
int Def::RUN = 0;
int Def::SIZET = 501;
int Def::chance = 50;
bool Def::focused = true;
TypeAutomaton Def::tempA({}, {});
int Def::running = 1, Def::CLOSE = 0, Def::typecheckingneighbours = 8;
sf::Image Def::buttons, Def::background;
sf::Color Def::Grey = sf::Color(160, 160, 160), Def::darkGrey = sf::Color(80, 80, 80), Def::brightRed = sf::Color(255, 83, 73);
TypeAutomaton Def::liveA({ 3 }, { 2, 3 }), Def::mazeA({ 3 }, { 1, 2, 3, 4, 5 }), Def::cavesA({ 5, 6, 7, 8 }, { 4, 5, 6, 7, 8 }), \
Def::diamobaA({ 3, 5, 6, 7, 8 }, { 5, 6, 7, 8 }), Def::carpetA({ 2, 3, 4 }, { }), Def::daynightA({ 3, 6, 7, 8 }, { 3, 4, 6, 7, 8 });
TypeAutomaton Def::mode = Def::liveA;

