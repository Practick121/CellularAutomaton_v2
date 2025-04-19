#pragma once
#include "Config.h"
#include "Button.h"
#include "Global.h"
#include "functions.h"
#include "Slider.h"
#include "Table.h"
#include "Text.h"
#include "TypeAutomaton.h"
#include "InputBox.h"
#include "Camera.h"
#include <fstream>
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include <string>
#include <thread>

Table field;
Text info_typeA;
sf::Sprite but_background;
std::ifstream fin;    
Camera camera_table, camera_i, default_camera;
sf::Clock clockrender, clocktps, systemclock1, systemclock2;
InputBox textbox1, textbox2;
void handleevents(sf::RenderWindow* iw, sf::Event* event) {
    while (iw->pollEvent(*event)) {
        for (auto box : InputBox::List)
            box->check(event);
        if (event->type == sf::Event::Closed)
            Gl::CLOSE = 1;
        if (event->type == sf::Event::MouseWheelMoved)
            camera_table.addZoom(1 - event->mouseWheel.delta * 0.1f);
        if (event->type == sf::Event::GainedFocus)
            Gl::focused = true;
        if (event->type == sf::Event::LostFocus)
            Gl::focused = false;
        if (event->type == sf::Event::TextEntered)
            Gl::input += static_cast<char>(event->text.unicode);
        if (event->type == sf::Event::KeyPressed)
            switch (event->key.code) {
            case sf::Keyboard::Left:
                camera_table.move({ -5, 0 });
                break;
            case sf::Keyboard::Right:
                camera_table.move({ 5, 0 });
                break;
            case sf::Keyboard::Up:
                camera_table.move({ 0, -5 });
                break;
            case sf::Keyboard::Down:
                camera_table.move({ 0, 5 });
                break;
            case sf::Keyboard::M:
                camera_table.addZoom(0.9);
                break;
            case sf::Keyboard::N:
                camera_table.addZoom(1.1);
                break;
            case sf::Keyboard::R:
                camera_table.reset();
                break;
            }
        if (event->type == sf::Event::MouseButtonPressed)
            switch (event->mouseButton.button) {
            case sf::Mouse::Middle:
                camera_table.setActive(true);
                break;
            case sf::Mouse::Right:
                Gl::RUN = 1 - Gl::RUN;
                break;
            }
        if (event->type == sf::Event::MouseButtonReleased && event->mouseButton.button == sf::Mouse::Middle)
            camera_table.setActive(false);
    }
}

void OpenFile() {
    fin.open("data.txt");
    if (!fin.is_open()) {
        std::cerr << "ERROR!\n";
        return;
    }
    std::string line;
    int a = -1;
    std::vector <std::vector<int>> M1;
    while (std::getline(fin, line)) {
        a++;
        M1.push_back({});
        for (char el : line) {
            M1[a].push_back(el - '0');
        }
    }
    fin.close();
    field.setmatrix(&M1);
}
void UploadFile() {
    std::string namefile = "out";
    int i = 0;
    while(++i) {
        fin.open(namefile + std::to_string(i) + ".txt");
        if (!fin.is_open())
            break;
        fin.close();
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

void recalctypeA() {
    std::string str = "Birth: ";
	for (auto el : Gl::mode.getbirth()) {
		str += std::to_string(el) + " ";
	}
    str += "\nSurvive: ";
    for (auto el : Gl::mode.getsurvive()) {
        str += std::to_string(el) + " ";
	}
	info_typeA.setString(str);
}

void work_with_graphics(sf::RenderWindow* iw) {
    iw->setActive(true);

    while (Gl::running) {
        if (systemclock2.getElapsedTime().asMilliseconds() >= 10) {
            systemclock2.restart();
            recalctypeA();
        }
        if (clockrender.getElapsedTime().asMilliseconds() >= 1000 / Config::FPS) {
            std::string title = "FPS: " + std::to_string((int)(1 / clockrender.restart().asSeconds()));
            //iw->setTitle(title);
            iw->clear(Gl::darkGrey);
            camera_table.setCamera();
            field.render();
            camera_i.setCamera();
            iw->draw(but_background);
            info_typeA.render();
            for (InputBox* box : InputBox::List)
                box->render();
            for (Button* but : Button::List)
                but->render();
            for (Slider* but : Slider::List)
                but->render();
            iw->display();
        }
    }
	iw->setActive(false);
}

void Apply() {
    std::vector<int> B, S;
    B = string_to_mas(textbox1.content);
    S = string_to_mas(textbox2.content);
    for (auto el : B)
        std::cout << el << ' ';
    std::cout << std::endl;
    std::sort(B.begin(), B.end());
    std::sort(S.begin(), S.end());
    Gl::mode = TypeAutomaton(B, S);
}

void switchNbrtype() {
    if (Config::typecheckingneighbours == "4")
        Config::typecheckingneighbours = "8";
    else if (Config::typecheckingneighbours == "8")
        Config::typecheckingneighbours = "12";
    else if (Config::typecheckingneighbours == "12")
        Config::typecheckingneighbours = "24";
    else if (Config::typecheckingneighbours == "24")
        Config::typecheckingneighbours = "4";
}

int main() {
    //ЗАГРУЗКА РЕСУРСОВ
    sf::Font myfont;
    myfont.loadFromFile("arial.ttf");
    Gl::buttons.loadFromFile("buttons.png");
    Gl::background.loadFromFile("background.png");
    sf::Texture but_background_txtr;
    but_background_txtr.loadFromImage(Gl::background);
    but_background.setTexture(but_background_txtr);
    but_background.setPosition({ field.rect.width, 0 });
    but_background.setScale(0.65, 0.65);

    //ИНИЦИАЛИЗАЦИЯ ОБЪЕКТОВ КЛАССОВ
    std::srand(std::time(NULL));
    sf::RenderWindow w(sf::VideoMode(Config::windowSize.x, Config::windowSize.y), "CellularAutomaton_v2.3");
    w.setActive(false);
    field = Table(&w, &camera_table, { 0, 0, (float)Config::windowSize.y, (float)Config::windowSize.y });
    sf::Event ev;
    sf::RenderWindow* iw = &w;

    camera_i = Camera(iw, { field.rect.width, 0, (float)(Config::windowSize.x - field.rect.width), (float)Config::windowSize.y });
    camera_table = Camera(iw, { field.rect.left, field.rect.top, field.rect.width, field.rect.height });
    default_camera = Camera(iw, { 0, 0, (float)Config::windowSize.x, (float)Config::windowSize.y });

    int textsize = 15;
    sf::Color col_but = Gl::brightRed, col_but_text = sf::Color::Black;
    sf::IntRect default_texture = { 1, 1, 162, 71 };
    sf::Vector2f butcolumn[15][7];
    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 7; j++)
            butcolumn[i][j] = sf::Vector2f({ field.rect.width + 10 + 120 * j, 10 + i * (float)60 });

    textbox1.init(iw, "Birth  ", { butcolumn[8][1], {400, 50} }, &myfont);
    textbox2.init(iw, "Survive  ", { butcolumn[9][1], {400, 50} }, &myfont);

    info_typeA = Text(iw, "", &myfont, 20, sf::Color::White, butcolumn[10][2]);

    Text ex_sl_t(iw, "exapmple1", &myfont, 30, sf::Color::Black, {0, 0}, false);
    Text ex_but_t(iw, "example2", &myfont, 15, sf::Color::Black, { 0, 0 }, false);

    Slider controltps(iw, "TPS:", {butcolumn[0][2], sf::Vector2f{ 300, 100 }}, default_texture, ex_sl_t, [](int a) {Config::TPS = a;}, 1, 100, Config::TPS);
    Slider controlchance(iw, "CHANCE:", {butcolumn[2][2], sf::Vector2f{ 300, 100 }}, default_texture, ex_sl_t, [](int a) {Config::chance = a;}, 0, 100, Config::chance);
    Slider controlgeneration(iw, "CNT GENERATION: ", { butcolumn[4][2], sf::Vector2f(300, 100) }, default_texture, &myfont, 23, sf::Color::Black, [](int a) {Gl::CNT_GENER = a; field.brush = a; }, 1, Config::GENER_COLORS.size() - 1, Gl::CNT_GENER);

    Button brush_col_1(iw, "", sf::Rect<float>(sf::Vector2f{ field.rect.width + 570, 10 }, sf::Vector2f(30, 30)), sf::IntRect(195, 0, 30, 30), ex_but_t, []() {field.brush = Gl::CNT_GENER;}, {0, false}, false);
    Button brush_col_0(iw, "", sf::Rect<float>(sf::Vector2f{ field.rect.width + 570, 50 }, sf::Vector2f(30, 30)), sf::IntRect(165, 0, 30, 30), ex_but_t, []() {field.brush = 0;}, {0, false}, false);
    Button run(iw, "RUN", { butcolumn[0][0], sf::Vector2f{ 100, 50 } }, default_texture, ex_but_t, []() {Gl::RUN = 1;}, { 2, true });
    Button stop(iw, "STOP", { butcolumn[1][0], sf::Vector2f{ 100, 50 } }, default_texture, ex_but_t, []() {Gl::RUN = 0;}, { 2, true });
    Button run_one_step(iw, "ONE STEP", {butcolumn[2][0], sf::Vector2f{ 100, 50 }}, default_texture, ex_but_t, []() {Gl::RUN = 2;}, {2, false});
    Button generate(iw, "GENERATE", {butcolumn[3][0], sf::Vector2f(100, 50)}, default_texture, ex_but_t, []() {field.setrandom();});
    Button generatecustom(iw, "GENERATE\nSQUARE", {butcolumn[4][0], sf::Vector2f(100, 50)}, default_texture, ex_but_t, []() {field.setcustom();});
    Button clean(iw, "CLEAN", { butcolumn[5][0], sf::Vector2f(100, 50) }, default_texture, ex_but_t, []() {field.clean(); Gl::RUN = 0;}, { 2, false }, true);

    Button maze(iw, "MAZE", { butcolumn[0][1], sf::Vector2f(100, 50) }, default_texture, ex_but_t, []() {Gl::mode = Config::maze;}, { 1, true });
    Button caves(iw, "CAVES", {butcolumn[1][1], sf::Vector2f(100, 50)}, default_texture, ex_but_t, []() {Gl::mode = Config::caves;}, {1, true});
    Button live(iw, "LIVE", {butcolumn[2][1], sf::Vector2f(100, 50) }, default_texture, ex_but_t, []() {Gl::mode = Config::live;}, {1, true});
    Button daynight(iw, "DAYNIGHT", {butcolumn[3][1], sf::Vector2f(100, 50)}, default_texture, ex_but_t, []() {Gl::mode = Config::daynight;}, {1, true});
    Button amoeba(iw, "AMOEBA", {butcolumn[4][1], sf::Vector2f(100, 50)}, default_texture, ex_but_t, []() {Gl::mode = Config::diamoba;}, {1, true});
    Button carpet(iw, "CARPET", {butcolumn[5][1], sf::Vector2f(100, 50)}, default_texture, ex_but_t, []() {Gl::mode = Config::carpet;}, {1, true});
    Button custom1(iw, "CUSTOM1", {butcolumn[7][0], sf::Vector2f(100, 50)}, default_texture, ex_but_t, []() {Gl::mode = TypeAutomaton({2, 8}, {0, 2, 3, 4, 7});}, {1, true});
	Button custom2(iw, "CUSTOM2", {butcolumn[7][1], sf::Vector2f(100, 50)}, default_texture, ex_but_t, []() {Gl::mode = TypeAutomaton({ 1, 2, 5, 6, 8 }, { 0, 1, 4, 6, 7, 8 });}, {1, true});
    Button newrandombut(iw, "NEW\nRANDOM", {butcolumn[6][2], sf::Vector2f(100, 50)}, default_texture, ex_but_t, []() {generate_automaton(); Gl::mode = Gl::tempA;}, {1, false});
    Button setrandombut(iw, "SET\nRANDOM", {butcolumn[6][1], sf::Vector2f(100, 50)}, default_texture, ex_but_t, []() {Gl::mode = Gl::tempA;}, {1, true});

    Button upload(iw, "UPLOAD", {butcolumn[14][1], sf::Vector2f(100, 50)}, default_texture, ex_but_t, UploadFile);
    Button open(iw, "OPEN", {butcolumn[14][0], sf::Vector2f(100, 50)}, default_texture, ex_but_t, OpenFile);
    Button close(iw, "CLOSE", {butcolumn[14][2], sf::Vector2f(100, 50)}, default_texture, ex_but_t, []() {Gl::CLOSE = 1;});

    Button typecheckingneighbours(iw, "NEIGHBOURS:", {butcolumn[6][3], sf::Vector2f(150, 60)}, default_texture, &myfont, 14, sf::Color::Black, switchNbrtype);
    
    Button apply(iw, "Apply", { butcolumn[10][1], sf::Vector2f(100, 50) }, default_texture, ex_but_t, Apply);

    Gl::rendering = std::thread([&](sf::RenderWindow* iw) {
        work_with_graphics(iw);
    }, &w);

    // ОСНОВНОЙ ЦИКЛ
    while (Gl::running) {

        if (systemclock1.getElapsedTime().asMilliseconds() >= 10) {
            systemclock1.restart();
            handleevents(&w, &ev);
            if (Gl::CLOSE)
                break;     
        }
        if (Gl::focused) {
            field.check();
            camera_table.check();
            for (auto but : Button::List)
                but->check();
            for (auto but : Slider::List)
                but->check();
        }
        if (clocktps.getElapsedTime().asMilliseconds() >= 1000 / Config::TPS) {
            clocktps.restart();
            if (Gl::RUN == 2) {
                field.nextgeneration();
                Gl::RUN = 0;
            } else if (Gl::RUN == 1) {
                field.nextgeneration();
            }
        }
    }
    Close(&w);
    w.setActive(true);
    w.close();
    return 0;
}

