#pragma once
#include "TypeAutomaton.h"
#include "Config.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <SFML/Graphics.hpp>

class Gl {
public:
	static int RUN, running, CLOSE, CNT_GENER;
	static sf::Color Grey, darkGrey, brightRed;
	static sf::Image buttons, background;
	static bool focused;
	static std::vector<std::vector<int>> MyEvents;
	static TypeAutomaton mode, tempA;
	static std::string input;
	static std::thread rendering;
};