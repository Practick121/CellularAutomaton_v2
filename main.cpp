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

std::mutex m1;
Table field;
sf::Text info_crd;
sf::Sprite but_background;
sf::Event ev;
std::ifstream fin;
sf::Clock clockrender, clocktps, timeontick;
std::thread rendering, checking;
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
static void Close(sf::RenderWindow *w1) {
    std::cout << "Close!" << std::endl;
    Def::running1 = 0;
    checking.join();
    Def::running2 = 0;
    rendering.join();
    exit(0);
}
void work_with_graphics(sf::RenderWindow* w1, std::mutex* m1) {
    sf::Font font;
    font.loadFromFile("ariali.ttf");
    info_crd.setFont(font);
    info_crd.setFillColor(sf::Color::Black);
    info_crd.setCharacterSize(30);
    info_crd.setStyle(sf::Text::Bold);
    info_crd.setPosition({ field.tablerect.height + 250, field.tablerect.height - 300 });
    sf::Texture but_background_txtr;
    Def::background.loadFromFile("background2.png");
    but_background_txtr.loadFromImage(Def::background);
    but_background.setTexture(but_background_txtr);
    but_background.setPosition({ field.tablerect.width, 0 });
    but_background.setScale(0.75, 0.75);
    w1->setActive(true);
    while (Def::running2) {
        //std::this_thread::sleep_for(std::chrono::milliseconds(std::max(0, 1000 / Def::FPS - clockrender.getElapsedTime().asMilliseconds())));
        m1->lock();
        if (clockrender.getElapsedTime().asMilliseconds() >= 1000 / Def::FPS) {
            std::string title = "FPS: " + std::to_string((int)(1 / clockrender.restart().asSeconds()));
            //w1->setTitle(title);
            w1->clear(sf::Color::Blue);
            field.render();
            w1->draw(but_background);
            w1->draw(info_crd);
            for (Button* but : Button::List)
                but->render();
            w1->display();
        }
        m1->unlock();
    }
}
void checking_func(sf::RenderWindow* w1) {
    w1->setActive(false);
    while (Def::running1) {
        field.check();
        for (auto but : Button::List)
            (*but).check();
    }
}
//void but_init(sf::RenderWindow* w1) {
//    
//}
int main() {
    std::srand(std::time(NULL));
    sf::RenderWindow w(sf::VideoMode(Def::windowsize.x, Def::windowsize.y), "CellularAutomaton_v2.1");
    
    
    field = Table(&w, Def::windowsize.y, Def::windowsize.y);
    
    Def::buttons.loadFromFile("buttons.png");
    int textsize = 15;
    sf::Color col_but = Def::brightRed, col_but_text = sf::Color::Black;
    sf::Vector2f butcolumn[15][3];
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 3; j++) {
            butcolumn[i][j] = sf::Vector2f({ field.tablerect.width + 10 + 120 * j, 10 + i * (float)60 });
        }
    }
    sf::RenderWindow* w1 = &w;
    Button brush_col_1(w1, "", sf::Vector2f{ field.tablerect.width + 330, 10 }, sf::Vector2f(30, 30), textsize, sf::Color::Black, sf::Color::Black, []() {field.brush = 1;}, false);
    Button brush_col_0(w1, "", sf::Vector2f{ field.tablerect.width + 330, 50 }, sf::Vector2f(30, 30), textsize, sf::Color::White, sf::Color::White, []() {field.brush = 0;}, false);

    Button run(w1, "RUN", butcolumn[0][0], sf::Vector2f{ 100, 50 }, textsize, col_but, col_but_text, []() {Def::RUN = 1;});
    Button stop(w1, "STOP", butcolumn[1][0], sf::Vector2f{ 100, 50 }, textsize, col_but, col_but_text, []() {Def::RUN = 0;});
    Button run_one_step(w1, "ONE STEP", butcolumn[2][0], sf::Vector2f{ 100, 50 }, textsize, col_but, col_but_text, []() {Def::RUN = 2;});
    Button generate(w1, "GENERATE", butcolumn[3][0], sf::Vector2f(100, 50), textsize, col_but, col_but_text, []() {field.setrandom();});
    Button generatecustom(w1, "GENERATE\nSQUARE", butcolumn[4][0], sf::Vector2f(100, 50), textsize, col_but, col_but_text, []() {field.setcustom();});
    Button clean(w1, "CLEAN", butcolumn[5][0], sf::Vector2f(100, 50), textsize, col_but, col_but_text, []() {field.clean();});

    Button maze(w1, "MAZE", butcolumn[0][1], sf::Vector2f(100, 50), textsize, col_but, col_but_text, []() {Def::mode = Def::mazeA;});
    Button caves(w1, "CAVES", butcolumn[1][1], sf::Vector2f(100, 50), textsize, col_but, col_but_text, []() {Def::mode = Def::cavesA;});
    Button live(w1, "LIVE", butcolumn[2][1], sf::Vector2f(100, 50), textsize, col_but, col_but_text, []() {Def::mode = Def::liveA;});
    Button daynight(w1, "DAYNIGHT", butcolumn[3][1], sf::Vector2f(100, 50), textsize, col_but, col_but_text, []() {Def::mode = Def::daynightA;});
    Button diamoba(w1, "DIAMOEBA", butcolumn[4][1], sf::Vector2f(100, 50), textsize, col_but, col_but_text, []() {Def::mode = Def::diamobaA;});
    Button carpet(w1, "CARPET", butcolumn[5][1], sf::Vector2f(100, 50), textsize, col_but, col_but_text, []() {Def::mode = Def::carpetA;});


    Button upload(w1, "UPLOAD", butcolumn[14][1], sf::Vector2f(100, 50), textsize, col_but, col_but_text, UploadFile);
    Button open(w1, "OPEN", butcolumn[14][0], sf::Vector2f(100, 50), textsize, col_but, col_but_text, OpenFile);
    Button close(w1, "CLOSE", butcolumn[14][2], sf::Vector2f(100, 50), textsize, col_but, col_but_text, []() {Def::CLOSE = 1;});

    Button tps5(w1, "5", sf::Vector2f{ field.tablerect.width + 250, 10 }, sf::Vector2f(50, 30), textsize, sf::Color::Green, col_but_text, []() {Def::TPS = 5;});
    Button tps15(w1, "15", sf::Vector2f{ field.tablerect.width + 250, 60 }, sf::Vector2f(50, 30), textsize, sf::Color::Green, col_but_text, []() {Def::TPS = 15;});
    Button tps30(w1, "30", sf::Vector2f{ field.tablerect.width + 250, 110 }, sf::Vector2f(50, 30), textsize, sf::Color::Green, col_but_text, []() {Def::TPS = 30;});
    Button tps60(w1, "60", sf::Vector2f{ field.tablerect.width + 250, 160 }, sf::Vector2f(50, 30), textsize, sf::Color::Green, col_but_text, []() {Def::TPS = 60;});
    Button tps120(w1, "120", sf::Vector2f{ field.tablerect.width + 250, 210 }, sf::Vector2f(50, 30), textsize, sf::Color::Green, col_but_text, []() {Def::TPS = 120;});



    w.setActive(false);
    rendering = std::thread([](sf::RenderWindow* w1, std::mutex* m1) {
        work_with_graphics(w1, m1);
    }, &w, &m1);
    checking = std::thread([](sf::RenderWindow* w1) {
        checking_func(w1);
    }, &w);
    while (Def::running2) {
        if (Def::CLOSE)
            Close(&w);
        while (w.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed)
                Close(&w);
            if (ev.type == sf::Event::MouseWheelMoved) {
                sf::Vector2f mouse_pos = get_mouse_pos(&w);
                field.mouselastpos += (mouse_pos - field.mouselastpos) / (float)field.zoom;
                field.zoom += (int)ev.mouseWheel.delta;
                field.zoom = std::max(1, field.zoom);
            }
        }
        sf::Vector2f mouse_pos1 = get_mouse_pos(&w);
        std::string str = "X: " + std::to_string((int)mouse_pos1.x) + "\nY: " + std::to_string((int)mouse_pos1.y);
        info_crd.setString(str);

        

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
    return 0;
}

