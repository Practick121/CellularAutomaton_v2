#pragma once
#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <SFML/Graphics.hpp>
#include "TypeAutomaton.h"
class Def {
public:
	static sf::Vector2f windowsize;
	static int TPS, FPS, RUN, SIZET, running1, running2, CLOSE;
	static sf::Color Grey, darkGrey, brightRed;
	static sf::Image buttons, background;
	static TypeAutomaton mode, liveA, cavesA, mazeA, daynightA, diamobaA, carpetA;
};
