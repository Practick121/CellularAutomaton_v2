//#pragma once
//#include "Config.h"
//#include "Button.h"
//#include "Global.h"
//#include "functions.h"
//#include "Slider.h"
//#include "Table.h"
//#include "Text.h"
//#include "TypeAutomaton.h"
//#include "InputBox.h"
//#include "Camera.h"
//#include "MyEvent.h"
//#include <fstream>
//#include <iostream>
//#include <random>
//#include <SFML/Graphics.hpp>
//#include <string>
//#include <thread>
//
//class Application {
//public:
//	Application();
//	void runMainThread();
//	void runRenderThread();
//	void handleEvents();
//	void init();
//	void update();
//	void render();
//	void initGenerColors();
//	void switchNbrtype();
//	void Apply();
//	void recalctypeA();
//	void OpenFile();
//	void UploadFile();
//	sf::RenderWindow w;
//	Table field;
//	Text info_typeA;
//	sf::Sprite but_background;
//	std::ifstream fin;
//	Camera camera_table, camera_i, default_camera;
//	sf::Clock clockrender, clocktps, systemclock1, systemclock2;
//	InputBox textbox1, textbox2;
//	sf::Event ev;
//};