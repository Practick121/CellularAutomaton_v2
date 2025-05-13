#pragma once
#include "TypeAutomaton.h"
#include <iostream>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>

class Config {
public:
	static int TPS, FPS, chance;
	static sf::Vector2i windowSize;
	static int SIZET;
	static int CNT_GENER;
	static std::vector<sf::Color> GENER_COLORS;
	static TypeAutomaton live, caves, maze, carpet, dayNight, diamoba, bugs5, modernArt, brianBrain, starWars, faders;
	static std::string pathBackground, pathButton, pathFont;
};

std::vector<int> s_to_mas1(std::string s, char sep=' ', bool deleteRepeat=false);