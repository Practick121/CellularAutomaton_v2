#pragma once
#include "TypeAutomaton.h"
#include "Global.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>

sf::Vector2f get_mouse_pos(sf::RenderWindow* w);
sf::Vector2f get_mouse_pos_desktop();

int getrandom(int a, int b);

void generate_automaton();

void Close(sf::RenderWindow* iw);

std::vector<int> string_to_mas(std::string s, char sep = ' ', bool deleatRepeat = false);

void initGenerColors(sf::Color live);