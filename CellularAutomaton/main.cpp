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
InputBox BirthInput, SurviveInput, Colorinput1, Colorinput2;
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
    std::vector<int> B = Gl::mode.getBirth(), S = Gl::mode.getSurvive();
    std::string str = "Birth: ";
    int st = 0;
    std::sort(B.begin(), B.end());
    std::sort(S.begin(), S.end());
    for (int i = 1; i <= B.size(); i++) {
        if (i == B.size() || B[i] != B[i - 1] + 1) {
            if (i > st + 2)
                str += std::to_string(B[st]) + "-" + std::to_string(B[i - 1]) + " ";
            else if (i == st + 2)
                str += std::to_string(B[st]) + " " + std::to_string(B[i - 1]) + " ";
            else
                str += std::to_string(B[st]) + " ";
            st = i;
        }
    }
    st = 0;
    str += "\nSurvive: ";
    for (int i = 1; i <= S.size(); i++) {
        if (i == S.size() || S[i] != S[i - 1] + 1) {
            if (i > st + 2)
                str += std::to_string(S[st]) + "-" + std::to_string(S[i - 1]) + " ";
            else if (i == st + 2)
                str += std::to_string(S[st]) + " " + std::to_string(S[i - 1]) + " ";
            else
                str += std::to_string(S[st]) + " ";
            st = i;
        }
    }
    str += "\nRadius: " + std::to_string(Gl::mode.getRadius());
    str += "\nCnt Generations: " + std::to_string(Gl::mode.getCntGen());
    str += "\nType Check: " + Gl::mode.getTypeCheck();
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
void ApplyColor() {
    std::vector<int> c1, c2;
    c1 = string_to_mas(Colorinput1.content);
    c2 = string_to_mas(Colorinput2.content);
    if (c1.size() == 0) c1 = { (int)field.backgroundColor.r, (int)field.backgroundColor.g, (int)field.backgroundColor.b};
    if (c2.size() == 0) c2 = { (int)field.cellColor.r, (int)field.cellColor.g, (int)field.cellColor.b};
    while (c1.size() < 3)
        c1.push_back(0);
    while (c2.size() < 3)
        c2.push_back(0);

    sf::Color col1, col2;
    auto to_col = [](int a) {return std::max(0, std::min(255, a));};
    col1 = sf::Color(to_col(c1[0]), to_col(c1[1]), to_col(c1[2]));
    col2 = sf::Color(to_col(c2[0]), to_col(c2[1]), to_col(c2[2]));
    field.setBackgroundColor(col1);
    field.setCellColor(col2);
}

void ApplyBirthSurvive() {
    std::vector<int> B, S;
    B = string_to_mas(BirthInput.content, ' ', true);
    S = string_to_mas(SurviveInput.content, ' ', true);
    for (auto el : B)
        std::cout << el << ' ';
    std::cout << std::endl;
    std::sort(B.begin(), B.end());
    std::sort(S.begin(), S.end());
    Gl::mode.setBirth(B);
    Gl::mode.setSurvive(S);
    Gl::tempA = Gl::mode;
}

void switchNbrtype() {
    if (Gl::mode.getTypeCheck() == "M")
        Gl::mode.setTypeCheck("N");
    else if (Gl::mode.getTypeCheck() == "N")
        Gl::mode.setTypeCheck("M");
}
int main() {
    //ЗАГРУЗКА РЕСУРСОВ
    sf::Font myfont;
    myfont.loadFromFile(Config::pathFont);
    Gl::buttons.loadFromFile(Config::pathButton);
    Gl::background.loadFromFile(Config::pathBackground);
    sf::Texture but_background_txtr;
    but_background_txtr.loadFromImage(Gl::background);
    but_background.setTexture(but_background_txtr);
    but_background.setPosition({ field.rect.width, 0 });
    but_background.setScale(0.65, 0.65);

    //ИНИЦИАЛИЗАЦИЯ ОБЪЕКТОВ КЛАССОВ

    initGenerColors(sf::Color::Black);
    std::srand(std::time(NULL));
    sf::RenderWindow w(sf::VideoMode(Config::windowSize.x, Config::windowSize.y), "CellularAutomaton_v2.3.2");
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
    sf::Vector2f grid[30][14];
    for (int i = 0; i < 30; i++)
        for (int j = 0; j < 14; j++)
            grid[i][j] = sf::Vector2f({ field.rect.width + 10 + 60 * j, 10 + i * (float)30 });

    BirthInput.init(iw, "Birth: ", { {0, 0}, {400, 50} }, &myfont);
    SurviveInput.init(iw, "Survive: ", { {0, 0}, {400, 50} }, &myfont);
    Colorinput1.init(iw, "RGB \nbackground: ", { {0, 0}, {240, 50} }, &myfont, -1, 15);
    Colorinput2.init(iw, "RGB cell: ", { {0, 0}, {240, 50} }, &myfont, -1, 15);


    info_typeA = Text(iw, "", &myfont, 15, sf::Color::White, { 0, 0 });

    Text ex_sl_t(iw, "exapmple1", &myfont, 20, sf::Color::Black, { 0, 0 }, false);
    Text ex_but_t(iw, "example2", &myfont, 15, sf::Color::Black, { 0, 0 }, false);
    Text ex_but_t2(iw, "example2", &myfont, 10, sf::Color::Black, { 0, 0 }, false);

    Slider controlTps(iw, "TPS:", { {0, 0}, sf::Vector2f{220, 70} }, default_texture, ex_sl_t, [](int a) {Config::TPS = a;}, 1, 100, []() {return Config::TPS;});
    Slider controlChance(iw, "CHANCE:", { {0, 0}, sf::Vector2f{ 220, 70 } }, default_texture, ex_sl_t, [](int a) {Config::chance = a;}, 0, 100, []() {return Config::chance;});
    Slider controlGeneration(iw, "CNT GENERATION: ", { {0, 0}, sf::Vector2f(220, 70) }, default_texture, &myfont, 15, sf::Color::Black, [](int a) {Gl::mode.setCntGen(a); initGenerColors(field.cellColor);}, 2, 100, []() {return Gl::mode.getCntGen();});
    Slider controlCustomGenerate(iw, "SIZE: ", { {0, 0}, sf::Vector2f(220, 70) }, default_texture, &myfont, 15, sf::Color::Black, [](int a) { field.sizeSquare = a; }, 1, 100, []() {return field.sizeSquare;});
    Slider controlRadius(iw, "RADIUS: ", { {0, 0}, sf::Vector2f(220, 70) }, default_texture, ex_sl_t, [](int a) {Gl::mode.setRadius(a);}, 1, 10, []() {return Gl::mode.getRadius();});

    Button brushCol1(iw, "", { {0, 0} , sf::Vector2f(50, 50) }, sf::IntRect(195, 0, 30, 30), ex_but_t, []() {field.brush = 1;}, { 0, false }, false);
    Button brushCol0(iw, "", { {0, 0}, sf::Vector2f(50, 50) }, sf::IntRect(165, 0, 30, 30), ex_but_t, []() {field.brush = 0;}, { 0, false }, false);
    Button run(iw, "RUN", { {0, 0}, sf::Vector2f{ 100, 50 } }, default_texture, ex_but_t, []() {Gl::RUN = 1;}, { 2, true });
    Button stop(iw, "STOP", { {0, 0}, sf::Vector2f{ 100, 50 } }, default_texture, ex_but_t, []() {Gl::RUN = 0;}, { 2, true });
    Button oneStep(iw, "ONE STEP", { {0, 0}, sf::Vector2f{ 100, 50 } }, default_texture, ex_but_t, []() {Gl::RUN = 2;}, { 2, false });
    Button generate(iw, "GENERATE", { {0, 0}, sf::Vector2f(100, 50) }, default_texture, ex_but_t, []() {field.setrandom();});
    Button generateCustom(iw, "GENERATE\nSQUARE", { {0, 0}, sf::Vector2f(100, 50) }, default_texture, ex_but_t, []() {field.setcustom();});
    Button clean(iw, "CLEAN", { {0, 0}, sf::Vector2f(100, 50) }, default_texture, ex_but_t, []() {field.clean();});

    Button maze(iw, "MAZE", { {0, 0}, sf::Vector2f(70, 30) }, default_texture, ex_but_t2, []() {field.newAutomaton(Config::maze);}, { 1, true });
    Button caves(iw, "CAVES", { {0, 0}, sf::Vector2f(70, 30) }, default_texture, ex_but_t2, []() {field.newAutomaton(Config::caves);}, { 1, true });
    Button live(iw, "LIVE", { {0, 0}, sf::Vector2f(70, 30) }, default_texture, ex_but_t2, []() {field.newAutomaton(Config::live);}, { 1, true });
    Button dayNight(iw, "DAYNIGHT", { {0, 0}, sf::Vector2f(70, 30) }, default_texture, ex_but_t2, []() {field.newAutomaton(Config::dayNight);}, { 1, true });
    Button amoeba(iw, "AMOEBA", { {0, 0}, sf::Vector2f(70, 30) }, default_texture, ex_but_t2, []() {field.newAutomaton(Config::diamoba);}, { 1, true });
    Button carpet(iw, "CARPET", { {0, 0}, sf::Vector2f(70, 30) }, default_texture, ex_but_t2, []() {field.newAutomaton(Config::carpet);}, { 1, true });
    Button modernArt(iw, "MODERN ART", { {0, 0}, sf::Vector2f(70, 30) }, default_texture, ex_but_t2, []() {field.newAutomaton(Config::modernArt);}, { 1, true });
    Button bugs5(iw, "BUGS5", { {0, 0}, sf::Vector2f(70, 30) }, default_texture, ex_but_t2, []() {field.newAutomaton(Config::bugs5);}, { 1, true });
    Button brianBrain(iw, "BRIAN BRAIN", { {0, 0}, sf::Vector2f(70, 30) }, default_texture, ex_but_t2, []() {field.newAutomaton(Config::brianBrain);}, { 1, true });
    Button starWars(iw, "STAR WARS", { {0, 0}, sf::Vector2f(70, 30) }, default_texture, ex_but_t2, []() {field.newAutomaton(Config::starWars);}, { 1, true });
    Button faders(iw, "FADERS", { {0, 0}, sf::Vector2f(70, 30) }, default_texture, ex_but_t2, []() {field.newAutomaton(Config::faders);}, { 1, true });
    //Button custom1(iw, "CUSTOM1", {{0, 0}, sf::Vector2f(100, 50)}, default_texture, ex_but_t, []() {Gl::mode = TypeAutomaton({2, 8}, {0, 2, 3, 4, 7});}, {1, true});
	//Button custom2(iw, "CUSTOM2", {{0, 0}, sf::Vector2f(100, 50)}, default_texture, ex_but_t, []() {Gl::mode = TypeAutomaton({ 1, 2, 5, 6, 8 }, { 0, 1, 4, 6, 7, 8 });}, {1, true});
    Button newrandombut(iw, "NEW\nRANDOM", {{0, 0}, sf::Vector2f(100, 50)}, default_texture, &myfont, 13, sf::Color::Black, []() {generate_automaton();}, {1, false});
    Button setrandombut(iw, "SET\nRANDOM", {{0, 0}, sf::Vector2f(100, 50)}, default_texture, &myfont, 13, sf::Color::Black, []() {Gl::mode = Gl::tempA;}, {1, true});

    Button upload(iw, "UPLOAD", {{0, 0}, sf::Vector2f(100, 50)}, default_texture, ex_but_t, UploadFile);
    Button open(iw, "OPEN", {{0, 0}, sf::Vector2f(100, 50)}, default_texture, ex_but_t, OpenFile);
    Button close(iw, "CLOSE", {{0, 0}, sf::Vector2f(100, 50)}, default_texture, ex_but_t, []() {Gl::CLOSE = 1;});

    Button typeCheck(iw, "NEIGHBOURS:", {{0, 0}, sf::Vector2f(150, 50)}, default_texture, &myfont, 14, sf::Color::Black, switchNbrtype);
    
    Button applyBirthSurvive(iw, "Apply", { {0, 0}, sf::Vector2f(100, 50) }, default_texture, ex_but_t, ApplyBirthSurvive);

    Button applyColor(iw, "Apply", { {0, 0}, sf::Vector2f(100, 50) }, default_texture, ex_but_t, ApplyColor);
    std::map<Button*, sf::Vector2i> But_Coords = { {&run, {0, 0}}, {&stop, {2, 0}}, {&oneStep, {4, 0}}, {&generate, {6, 0}}, {&generateCustom, {8, 0}}, { &clean, {10, 0} },\
    {&brushCol1, { 12, 0 }}, { &brushCol0, {12, 1} }, { &setrandombut, {14, 7} }, { &newrandombut, { 16, 7 } }, { &open, {29, 0} }, { &upload, {29, 2} }, { &close, {29, 4} },\
    {&live, { 21, 0 }}, { &maze, {22, 0} }, { &caves, {23, 0} }, { &dayNight, { 24, 0 } }, { &amoeba, {25, 0} }, { &carpet, {26, 0} }, { &modernArt, {21, 2} }, { &bugs5, {22, 2} },\
    {&brianBrain, { 23, 2 }}, { &starWars, {24, 2} }, { &faders, {25, 2} } };
    for (auto but : Button::List) {
        sf::Vector2i crd = But_Coords[but];
        but->setCoord(grid[crd.x][crd.y]);
    }
    controlTps.setCoord(grid[0][2]);
    controlGeneration.setCoord(grid[3][2]);
    controlChance.setCoord(grid[6][2]);
    controlCustomGenerate.setCoord(grid[9][2]);
    controlRadius.setCoord(grid[9][6]);

    BirthInput.setCoord(grid[14][0]);
    SurviveInput.setCoord(grid[16][0]);
    applyBirthSurvive.setCoord(grid[18][0]);
    info_typeA.setCoord(grid[18][2]);

    Colorinput1.setCoord(grid[0][6]);
    Colorinput2.setCoord(grid[2][6]);
    applyColor.setCoord(grid[4][6]);
    typeCheck.setCoord(grid[6][6]);

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

