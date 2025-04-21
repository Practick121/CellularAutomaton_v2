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
	static std::string typenbrs;
	static int SIZET;
	static int CNT_GENER;
	static std::vector<sf::Color> GENER_COLORS;
	static TypeAutomaton live, caves, maze, carpet, daynight, diamoba;
};