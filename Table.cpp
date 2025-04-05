#include "Table.h"
Table::Table() {}
Table::Table(sf::RenderWindow* window, int width1, int height1) {
    w1 = window;
    tablerect = sf::Rect <float>();
    tablerect.width = width1;
    tablerect.height = height1;
    tablerect.top = 0;
    tablerect.left = 0;
    cellrect.width = tablerect.width / (CellAutomaton::getsizet());
    cellrect.height = tablerect.width / (CellAutomaton::getsizet());
    //tableimage.create(tablerect.width, tablerect.height, sf::Color::White);
    cellshape.setSize(cellrect.getSize());
    deathshape.setSize(cellrect.getSize());
    tableshape.setSize(tablerect.getSize());
    cellshape.setFillColor(sf::Color::Black);
    deathshape.setFillColor(sf::Color::Red);
    automaton.setrandom();
}

void Table::nextgeneration() { automaton.nextgeneration(Def::mode); }
void Table::setrandom() { automaton.setrandom(); }
void Table::clean() { automaton.clean(); }
//void Table::exit() { (*w1).close(); }
bool Table::ispressed() { return sf::Mouse::isButtonPressed(sf::Mouse::Left) && tablerect.contains(get_mouse_pos(w1)); }
std::vector<std::vector<int>> Table::getmatrix() { return automaton.M; }

void Table::check() {
    if (ispressed()) {
        sf::Vector2f mouse_pos = mouselastpos + (get_mouse_pos(w1) - mouselastpos) / (float)zoom;
        sf::Vector2i cell_pos;
        cell_pos.x = (mouse_pos.x - tablerect.left) / cellrect.width;
        cell_pos.y = (mouse_pos.y - tablerect.top) / cellrect.height;
        if (std::max(cell_pos.x, cell_pos.y) >= automaton.getsizet() || std::min(cell_pos.x, cell_pos.y) < 0) {
            std::cout << "abroad\n";
        }
        else {
            automaton.M[cell_pos.y + 1][cell_pos.x + 1] = brush;
        }
        pressed = true;
    }
    else {
        pressed = false;
    }
}

void Table::render() {
    (*w1).draw(tableshape);
    float x = 0, y = 0;
    sf::RectangleShape cellshape1 = cellshape, deathshape1 = deathshape;
    sf::Rect<float> cellrect1 = cellrect;
    cellshape1.setScale(zoom, zoom);
    deathshape1.setScale(zoom, zoom);
    cellrect1.width *= zoom;
    cellrect1.height *= zoom;
    sf::Vector2f crd = { 0, 0 };
    crd = mouselastpos - (mouselastpos - crd) * (float)zoom;
    float dx = cellrect1.width, dy = cellrect1.height;
    for (int i = 1; i <= automaton.getsizet(); i++) {

        crd.x = mouselastpos.x - (mouselastpos.x) * (float)zoom;
        for (int j = 1; j <= automaton.getsizet(); j++) {
            
            //crd = mouselastpos - (mouselastpos - crd) * (float)zoom;
            cellrect1.left = crd.x;
            cellrect1.top = crd.y;
            if (automaton.M[i][j] == 1 && tablerect.intersects(cellrect1)) {
                cellshape1.setPosition(crd);
                w1->draw(cellshape1);
            }
            /*else if (tablerect.contains(crd)) {
                deathshape1.setPosition(crd);
                (*w1).draw(deathshape1);
            }*/
            crd.x += dx;
        }
        crd.y += dy;
    }
}
void Table::setcustom() {
    for (int i = 1; i <= automaton.getsizet(); i++) {
        for (int j = 1; j <= automaton.getsizet(); j++) {
            /*if (j <= my.getSizeT() / 2)
                my.M[i][j] = 0;
            else
                my.M[i][j] = 1;*/
            int dl = 10;
            if (i <= automaton.getsizet()/ 2 + dl && i >= automaton.getsizet() / 2 - dl
                && j <= automaton.getsizet() / 2 + dl && j >= automaton.getsizet() / 2 - dl)
                automaton.M[i][j] = 1;
            else
                automaton.M[i][j] = 0;
        }
    }
}

void Table::setmatrix(std::vector<std::vector<int>>* M1) {
    int len1 = (*M1).size();
    for (int i = 0; i < len1; i++) {
        for (int j = 0; j < (*M1)[i].size(); j++)
            automaton.M[i + 1][j + 1] = (*M1)[i][j];
        for (int j = (*M1)[i].size(); j < automaton.getsizet(); j++) {
            automaton.M[i + 1][j + 1] = 0;
        }
    }
    for (int i = len1; i < automaton.getsizet(); i++) {
        for (int j = 0; j < automaton.getsizet(); j++)
            automaton.M[i + 1][j + 1] = 0;
    }

}

