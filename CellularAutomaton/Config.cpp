#include "Config.h"

sf::Vector2i Config::windowSize = { 1620, 1000 };

int Config::SIZET = 200;
int Config::TPS = 30;
int Config::FPS = 30;
int Config::chance = 50;

std::vector<sf::Color> Config::GENER_COLORS = {};

TypeAutomaton Config::live    ({ 3			   }, { 2, 3            }, 2, "8");
TypeAutomaton Config::maze    ({ 3			   }, { 1, 2, 3, 4, 5   }, 2, "8");
TypeAutomaton Config::caves   ({ 5, 6, 7, 8	   }, { 4, 5, 6, 7, 8   }, 2, "8");
TypeAutomaton Config::diamoba ({ 3, 5, 6, 7, 8 }, { 5, 6, 7, 8      }, 2, "8");
TypeAutomaton Config::carpet  ({ 2, 3, 4	   }, {                 }, 2, "8");
TypeAutomaton Config::daynight({ 3, 6, 7, 8	   }, { 3, 4, 6, 7, 8   }, 2, "8");

