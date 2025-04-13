#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <mutex>
#include <atomic>
#include "defenition.h"
#include "functions.h"
#include "CellAutomaton.h"
#include "Table.h"
#include "TypeAutomaton.h"
#include "Button.h"
#include "Text.h"
#include "Slider.h"

std::mutex m1;
Table field;
Text info_crd, info_typeA;
sf::Sprite but_background;
std::ifstream fin;    
sf::View view;

sf::Clock clockrender, clocktps;
void handleevents(sf::RenderWindow* w1, sf::Event* event) {
    while (w1->pollEvent(*event)) {
        if (event->type == sf::Event::Closed) {
            Def::CLOSE = 1;
        }
   //     if (event->type == sf::Event::MouseWheelMoved) {
			//view.setCenter(get_mouse_pos(w1));
			//view.zoom(1 - event->mouseWheel.delta * 0.1f);
            /*sf::Vector2f mouse_pos = get_mouse_pos(w1);
            field.mouselastpos += (mouse_pos - field.mouselastpos) / (float)field.zoom;
            field.zoom += (int)event->mouseWheel.delta;
            field.zoom = std::max(1, field.zoom);*/
        //}
		/*if (event->type == sf::Event::KeyPressed) {
			if ( == sf::Keyboard::R) {
				view.zoom(1.0f);
			}
		}*/
        if (event->type == sf::Event::GainedFocus) {
            std::cout << "Focused!\n";
            Def::focused = true;
        } 
        if (event->type == sf::Event::LostFocus) {
            std::cout << "Disfocused\n";
            Def::focused = false;
        }
	}
    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
    //    view.setCenter(Def::windowsize.x / 2, Def::windowsize.y / 2);
    //    view.setSize(Def::windowsize.x, Def::windowsize.y);
    //}
}
std::thread rendering;

void OpenFile() {
    fin.open("data.txt");
    if (fin.is_open())
        std::cout << "Success!\n";
    else {
        std::cout << "ERROR!\n";
        return;
    }
    std::string line;
    int a = -1;
    std::vector <std::vector<int>> M1;
    while (std::getline(fin, line)) {
        a++;
        M1.push_back({});
        for (char el : line) {
            if (el == '0')
                M1[a].push_back(0);
            else
                M1[a].push_back(1);
        }
    }
    fin.close();
    field.setmatrix(&M1);
}
void UploadFile() {
    std::string namefile = "out";
    int i = 1;
    for (; i <= 10; i++) {
        fin.open(namefile + std::to_string(i) + ".txt");
        if (!fin.is_open())
            break;
        fin.close();
    }
    if (i == 11) {
        std::cout << "too many output files\n";
        return;
    }
    namefile = namefile + std::to_string(i) + ".txt";
    std::ofstream fout(namefile);
    std::vector<std::vector<int>> Matrix = field.getmatrix();
    for (int i = 1; i <= Matrix.size() - 1; i++) {
        for (int j = 1; j < Matrix.size() - 1; j++) {
            fout << Matrix[i][j];
        }
        fout << std::endl;
    }
}
void recalccoord(sf::RenderWindow* w1) {
    sf::Vector2f mouse_pos1 = get_mouse_pos(w1);
    std::string str = "X: " + std::to_string((int)mouse_pos1.x) + "\nY: " + std::to_string((int)mouse_pos1.y);
    info_crd.setString(str);
}
void recalctypeA() {
    std::string str = "Birth: ";
	for (auto el : Def::mode.getbirth()) {
		str += std::to_string(el) + " ";
	}
    str += "\nSurvive: ";
    for (auto el : Def::mode.getsurvive()) {
        str += std::to_string(el) + " ";
	}
	info_typeA.setString(str);
}
static void Close(sf::RenderWindow *w1) {
    std::cout << "Close!" << std::endl;
    Def::running = 0;
    if (rendering.joinable()) {
        rendering.join();
		std::cout << "Thread closed!" << std::endl;
    }
}
void generate_automaton() {
    std::unordered_set<int> birth, survive;
	int max_cnt = Def::typecheckingneighbours;
    for (int i = 1; i <= max_cnt; i++) {
		if (getrandom(0, 1))
			birth.insert(i);
    }
    for (int i = 1; i <= max_cnt; i++) {
		if (getrandom(0, 1))
			survive.insert(i);
    }
	std::cout << "New automaton generated!\n";
	Def::tempA = TypeAutomaton(birth, survive);
	Button::mapactive["SET\nRANDOM"] = Def::tempA;
}
void work_with_graphics(sf::RenderWindow* w1, std::mutex* m1) {
    view.setCenter(Def::windowsize.x / 2, Def::windowsize.y / 2);
    view.setSize(Def::windowsize.x, Def::windowsize.y);
    
    sf::Texture but_background_txtr;
    Def::background.loadFromFile("background3.png");
    but_background_txtr.loadFromImage(Def::background);
    but_background.setTexture(but_background_txtr);
    but_background.setPosition({ field.tablerect.width, 0 });
    but_background.setScale(0.75, 0.75);
    w1->setActive(true);
    while (Def::running) {

        recalccoord(w1);
        recalctypeA();
        if (clockrender.getElapsedTime().asMilliseconds() >= 1000 / Def::FPS) {
            std::string title = "FPS: " + std::to_string((int)(1 / clockrender.restart().asSeconds()));
			w1->setView(view);
            //w1->setTitle(title);
            w1->clear(sf::Color::Blue);
            field.render();
            w1->draw(but_background);
            info_crd.render();
            info_typeA.render();
            for (Button* but : Button::List)
                but->render();
            for (Slider* but : Slider::List)
                but->render();
            w1->display();
        }
    }
	std::cout << "myThread closed!" << std::endl;
	w1->setActive(false);
}

int main() {
    std::srand(std::time(NULL));
    sf::RenderWindow w(sf::VideoMode(Def::windowsize.x, Def::windowsize.y), "CellularAutomaton_v2.2");

    sf::Font myfont;
    myfont.loadFromFile("arial.ttf");
    field = Table(&w, Def::windowsize.y, Def::windowsize.y);
    
    Button::mapactive = { {"LIVE", Def::liveA}, {"CARPET", Def::carpetA}, {"DIAMOEBA", Def::diamobaA},\
    {"DAYNIGHT", Def::daynightA}, { "MAZE", Def::mazeA }, { "CAVES", Def::cavesA }, {"SET\nRANDOM", Def::tempA} };
    Button::active = { "RUN", "STOP", "LIVE", "CARPET", "MAZE", "CAVES", "DAYNIGHT", "DIAMOEBA", "SET\nRANDOM"};
    Def::buttons.loadFromFile("buttons.png");
    sf::RenderWindow* w1 = &w;
    int textsize = 15;
    sf::Color col_but = Def::brightRed, col_but_text = sf::Color::Black;
    sf::Vector2f butcolumn[15][7];
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 7; j++) {
            butcolumn[i][j] = sf::Vector2f({ field.tablerect.width + 10 + 120 * j, 10 + i * (float)60 });
        }
    }

    info_crd.init(&w, "", &myfont, 15, sf::Color::Red, butcolumn[10][4]);
    info_typeA.init(&w, "", &myfont, 15, sf::Color::Red, butcolumn[11][4]);
    Slider controltps, controlchance;
    controltps.init(w1, "TPS:", &myfont, butcolumn[0][2], sf::Vector2f{ 300, 100 }, 30, sf::Color::Black, [](int a) {Def::TPS = a;
        }, 1, 240, Def::TPS);
    controlchance.init(w1, "CHANCE:", &myfont, butcolumn[2][2], sf::Vector2f{ 300, 100 }, 30, sf::Color::Black, [](int a) {Def::chance = a;}, 0, 100, Def::chance);

    Button run, stop, run_one_step, generate, generatecustom, clean, maze, caves, live, daynight, diamoba, carpet, upload, open, \
        close, tps5, tps15, tps30, tps60, tps120, brush_col_1, brush_col_0, setrandombut, newrandombut, typecheckingneighbours;
    brush_col_1.init(w1, "", &myfont, sf::Vector2f{ field.tablerect.width + 570, 10 }, sf::Vector2f(30, 30), textsize, sf::Color::Black, sf::Color::Black, []() {field.brush = 1;}, false);
    brush_col_0.init(w1, "", &myfont, sf::Vector2f{ field.tablerect.width + 570, 50 }, sf::Vector2f(30, 30), textsize, sf::Color::White, sf::Color::White, []() {field.brush = 0;}, false);

    run.init(w1, "RUN", &myfont, butcolumn[0][0], sf::Vector2f{ 100, 50 }, textsize, col_but, col_but_text, []() {Def::RUN = 1;});
    stop.init(w1, "STOP", &myfont, butcolumn[1][0], sf::Vector2f{ 100, 50 }, textsize, col_but, col_but_text, []() {Def::RUN = 0;});
    run_one_step.init(w1, "ONE STEP", &myfont, butcolumn[2][0], sf::Vector2f{ 100, 50 }, textsize, col_but, col_but_text, []() {Def::RUN = 2;});
    generate.init(w1, "GENERATE", &myfont, butcolumn[3][0], sf::Vector2f(100, 50), textsize, col_but, col_but_text, []() {field.setrandom();});
    generatecustom.init(w1, "GENERATE\nSQUARE", &myfont, butcolumn[4][0], sf::Vector2f(100, 50), textsize, col_but, col_but_text, []() {field.setcustom();});
    clean.init(w1, "CLEAN", &myfont, butcolumn[5][0], sf::Vector2f(100, 50), textsize, col_but, col_but_text, []() {field.clean();});

    maze.init(w1, "MAZE", &myfont, butcolumn[0][1], sf::Vector2f(100, 50), textsize, col_but, col_but_text, []() {Def::mode = Def::mazeA;});
    caves.init(w1, "CAVES", &myfont, butcolumn[1][1], sf::Vector2f(100, 50), textsize, col_but, col_but_text, []() {Def::mode = Def::cavesA;});
    live.init(w1, "LIVE", &myfont, butcolumn[2][1], sf::Vector2f(100, 50), textsize, col_but, col_but_text, []() {Def::mode = Def::liveA;});
    daynight.init(w1, "DAYNIGHT", &myfont, butcolumn[3][1], sf::Vector2f(100, 50), textsize, col_but, col_but_text, []() {Def::mode = Def::daynightA;});
    diamoba.init(w1, "DIAMOEBA", &myfont, butcolumn[4][1], sf::Vector2f(100, 50), textsize, col_but, col_but_text, []() {Def::mode = Def::diamobaA;});
    carpet.init(w1, "CARPET", &myfont, butcolumn[5][1], sf::Vector2f(100, 50), textsize, col_but, col_but_text, []() {Def::mode = Def::carpetA;});
    newrandombut.init(w1, "NEW\nRANDOM", &myfont, butcolumn[6][2], sf::Vector2f(100, 50), textsize, col_but, col_but_text, []() {generate_automaton(); Def::mode = Def::tempA;});
    setrandombut.init(w1, "SET\nRANDOM", &myfont, butcolumn[6][1], sf::Vector2f(100, 50), textsize, col_but, col_but_text, []() {Def::mode = Def::tempA;});

    upload.init(w1, "UPLOAD", &myfont, butcolumn[14][1], sf::Vector2f(100, 50), textsize, col_but, col_but_text, UploadFile);
    open.init(w1, "OPEN", &myfont, butcolumn[14][0], sf::Vector2f(100, 50), textsize, col_but, col_but_text, OpenFile);
    close.init(w1, "CLOSE", &myfont, butcolumn[14][2], sf::Vector2f(100, 50), textsize, col_but, col_but_text, []() {Def::CLOSE = 1;});

    typecheckingneighbours.init(w1, "NEIGHBOURS:", &myfont, butcolumn[4][2], sf::Vector2f(150, 60), 14, col_but, col_but_text, []() {Def::typecheckingneighbours = Def::typecheckingneighbours == 8 ? 4 : 8;});
    w.setActive(false);
    rendering = std::thread([](sf::RenderWindow* w1, std::mutex* m1) {
        work_with_graphics(w1, m1);
    }, &w, &m1);

    sf::Event ev;
    while (Def::running) {
        handleevents(&w, &ev);
        if (Def::CLOSE)
            break;
        if (Def::focused) {
            field.check();
            for (auto but : Button::List)
                but->check();
            for (auto but : Slider::List)
                but->check();
        }
        if (clocktps.getElapsedTime().asMilliseconds() >= 1000 / Def::TPS) {
            clocktps.restart();
            if (Def::RUN == 2) {
                field.nextgeneration();
                Def::RUN = 0;
            } else if (Def::RUN == 1) {
                field.nextgeneration();
            }
        }
    }
    Close(&w);
    w.setActive(true);
    w.close();
	std::cout << "Window closed!" << std::endl;

    return 0;
}

