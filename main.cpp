#pragma once
//#pragma comment(lib, "libname.lib")
#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>
#include <string>
#include <fstream>
#include "defenition.h"
#include "functions.h"
#include "CellAutomaton.h"
#include "Table.h"
#include "TypeAutomaton.h"
#include "Button.h"

Table field;

std::ifstream fin;
sf::Clock clockrender, clocktps, timeontick;
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

int main() {
    std::srand(std::time(NULL));
    sf::RenderWindow w(sf::VideoMode(Def::windowsize.x, Def::windowsize.y), "My_window");

    field = Table(&w, Def::windowsize.y - 20, Def::windowsize.y - 20);

    int textsize = 15;
    sf::Color col_but = sf::Color::Red, col_but_text = sf::Color::Black;
    sf::Vector2f butcolumn[15][3];
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 3; j++) {
            butcolumn[i][j] = sf::Vector2f({field.tablerect.width + 10 + 120 * j, 10 + i * (float)60});
        }
    }
    Button brush_col_1(&w, "", sf::Vector2f{ field.tablerect.width + 330, 10 }, sf::Vector2f(30, 30), textsize, sf::Color::Black, sf::Color::Black, []() {field.brush = 1;});
    Button brush_col_0(&w, "", sf::Vector2f{ field.tablerect.width + 330, 50 }, sf::Vector2f(30, 30), textsize, sf::Color::White, sf::Color::White, []() {field.brush = 0;});
    Button run(&w, "RUN", butcolumn[0][0], sf::Vector2f{100, 50}, textsize, col_but, col_but_text, []() {Def::RUN = 1;});
    Button stop(&w, "STOP", butcolumn[1][0], sf::Vector2f{100, 50}, textsize, col_but, col_but_text, []() {Def::RUN = 0;});
    Button run_one_step(&w, "ONE STEP", butcolumn[2][0], sf::Vector2f{100, 50}, textsize, col_but, col_but_text, []() {Def::RUN = 2;});
    Button generate(&w, "GENERATE", butcolumn[3][0], sf::Vector2f(100, 50), textsize, col_but, col_but_text, []() {field.setrandom();});
    Button generatecustom(&w, "GENERATE\nSQUARE", butcolumn[4][0], sf::Vector2f(100, 50), textsize, col_but, col_but_text, []() {field.setcustom();});
    Button clean(&w, "CLEAN", butcolumn[5][0], sf::Vector2f(100, 50), textsize, col_but, col_but_text, []() {field.clean();});
    
    Button maze(&w, "MAZE", butcolumn[0][1], sf::Vector2f(100, 50), textsize, col_but, col_but_text, []() {field.mode = TypeAutomaton({3}, {1, 2, 3, 4, 5});});
    Button caves(&w, "CAVES", butcolumn[1][1], sf::Vector2f(100, 50), textsize, col_but, col_but_text, []() {field.mode = TypeAutomaton({5, 6, 7, 8}, {4, 5, 6, 7, 8});});
    Button live(&w, "LIVE", butcolumn[2][1], sf::Vector2f(100, 50), textsize, col_but, col_but_text, []() {field.mode = TypeAutomaton({3}, {2, 3});});
    Button daynight(&w, "DAYNIGHT", butcolumn[3][1], sf::Vector2f(100, 50), textsize, col_but, col_but_text, []() {field.mode = TypeAutomaton({3, 6, 7, 8}, {3, 4, 6, 7, 8});});
    Button diamoba(&w, "DIAMOEBA", butcolumn[4][1], sf::Vector2f(100, 50), textsize, col_but, col_but_text, []() {field.mode = TypeAutomaton({ 3, 5, 6, 7, 8 }, {5, 6, 7, 8 });});
    Button carpet(&w, "CARPET", butcolumn[5][1], sf::Vector2f(100, 50), textsize, col_but, col_but_text, []() {field.mode = TypeAutomaton({ 2, 3, 4 }, { });});


    Button upload(&w, "UPLOAD", butcolumn[14][1], sf::Vector2f(100, 50), textsize, col_but, col_but_text, UploadFile);
    Button open(&w, "OPEN", butcolumn[14][0], sf::Vector2f(100, 50), textsize, col_but, col_but_text, OpenFile);
    Button close(&w, "CLOSE", butcolumn[14][2], sf::Vector2f(100, 50), textsize, col_but, col_but_text, []() { field.exit();});

    Button tps5(&w, "5", sf::Vector2f{ field.tablerect.width + 250, 10 }, sf::Vector2f(50, 30), textsize, sf::Color::Green, col_but_text, []() {Def::TPS = 5;});
    Button tps15(&w, "15", sf::Vector2f{ field.tablerect.width + 250, 60 }, sf::Vector2f(50, 30), textsize, sf::Color::Green, col_but_text, []() {Def::TPS = 15;});
    Button tps30(&w, "30", sf::Vector2f{ field.tablerect.width + 250, 110 }, sf::Vector2f(50, 30), textsize, sf::Color::Green, col_but_text, []() {Def::TPS = 30;});
    Button tps60(&w, "60", sf::Vector2f{ field.tablerect.width + 250, 160 }, sf::Vector2f(50, 30), textsize, sf::Color::Green, col_but_text, []() {Def::TPS = 60;});
    

    sf::Text info_crd;
    sf::Font font;
    font.loadFromFile("ariali.ttf");
    info_crd.setFont(font);
    info_crd.setFillColor(sf::Color::Black);
    info_crd.setCharacterSize(30);
    info_crd.setStyle(sf::Text::Bold);
    info_crd.setPosition({ field.tablerect.height + 250, field.tablerect.height - 300 });

    sf::RectangleShape but_background;
    but_background.setSize({ Def::windowsize.x - field.tablerect.width, Def::windowsize.y});
    but_background.setPosition({ field.tablerect.width, 0 });
    but_background.setFillColor(sf::Color::Blue);

    while (w.isOpen()) {
        sf::Event ev;
        while (w.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) {
                w.close();
            }
            else if (ev.type == sf::Event::MouseWheelMoved) {
                sf::Vector2f mouse_pos = get_mouse_pos(&w);
                field.mouselastpos += (mouse_pos - field.mouselastpos) / field.zoom;
                field.zoom += (float)ev.mouseWheel.delta;
                field.zoom = std::max(1.f, field.zoom);
                //std::cout << field.zoom << "   " << field.mouse_last_pos.x << ' ' << field.mouse_last_pos.y << std::endl;
            }
        }
        sf::Vector2f mouse_pos1 = get_mouse_pos(&w);
        std::string str = "X: " + std::to_string((int)mouse_pos1.x) + "\nY: " + std::to_string((int)mouse_pos1.y);
        info_crd.setString(str);

        field.check();
        for (auto but : Button::List)
            (*but).check();
        if (clocktps.getElapsedTime().asMilliseconds() >= 1000 / Def::TPS) {
            clocktps.restart();
            std::string tittle = "TPS: " + std::to_string((int)(1 / timeontick.restart().asSeconds()));
            w.setTitle(tittle);
            if (Def::RUN == 2) {
                field.nextgeneration();
                Def::RUN = 0;
            } else if (Def::RUN == 1) {
                field.nextgeneration();
            }
        }
        if (clockrender.getElapsedTime().asMilliseconds() >= 1000 / Def::FPS) {
            clockrender.restart();
            w.clear(sf::Color::Blue);
            field.render();
            w.draw(but_background);
            w.draw(info_crd);
            for (Button* but : Button::List)
                (*but).render();
            w.display();
        }
    }
    return 0;
}

