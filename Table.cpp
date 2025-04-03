#include "Table.h"
Table::Table() {}
Table::Table(sf::RenderWindow* window, int width1, int height1) {
    w1 = window;
    //tablew = width;
    //tableh = height;
    tablerect = sf::Rect <float>();
    tablerect.width = width1;
    tablerect.height = height1;
    tablerect.top = 0;
    tablerect.left = 0;
    //cellw = tablew / (CellAutomaton::getsizet());
    //cellh = tableh / (CellAutomaton::getsizet());
    cellrect.width = tablerect.width / (CellAutomaton::getsizet());
    cellrect.height = tablerect.width / (CellAutomaton::getsizet());
    cellshape.setSize(cellrect.getSize());
    deathshape.setSize(cellrect.getSize());
    tableshape.setSize(tablerect.getSize());
    cellshape.setFillColor(sf::Color::Black);
    deathshape.setFillColor(sf::Color::Black);
    automaton.setrandom();
    mode = TypeAutomaton({ 3 }, { 2, 3 });
}

void Table::nextgeneration() { automaton.nextgeneration(mode); }
void Table::setrandom() { automaton.setrandom(); }
void Table::clean() { automaton.clean(); }
void Table::exit() { (*w1).close(); }
bool Table::ispressed() { return sf::Mouse::isButtonPressed(sf::Mouse::Left) && tablerect.contains(get_mouse_pos(w1)); }
std::vector<std::vector<int>> Table::getmatrix() { return automaton.M; }

void Table::check() {
    if (ispressed()) {
        sf::Vector2f mouse_pos = mouselastpos + (get_mouse_pos(w1) - mouselastpos) / zoom;
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
    for (int i = 1; i <= automaton.getsizet(); i++) {
        x = 0;
        for (int j = 1; j <= automaton.getsizet(); j++) {
            sf::Vector2f crd = { x, y };
            crd = mouselastpos - (mouselastpos - crd) * zoom;
            cellrect1.left = crd.x;
            cellrect1.top = crd.y;
            cellrect1.width *= zoom;
            cellrect1.height *= zoom;
            if (automaton.M[i][j] == 1 && cellrect1.intersects(tablerect)) {
                cellshape1.setPosition(crd);
                (*w1).draw(cellshape1);
            }
            /*else if (tablerect.contains(crd)) {
                deathshape1.setPosition(new_crd);
                (*w1).draw(deathshape1);
            }*/
            x += cellrect.width;
        }
        y += cellrect.height;
    }
}
//bool Table::myintersects(sf::Rect<float> a, sf::Rect<float> b) {
//    //if (a.top + a.height > b.top + b.height)
//    //    std::swap(a, b);
//    float bottoma = a.top + a.height, bottomb = b.top + b.height;
//    float righta = a.left + a.width, rightb = b.left + b.width;
//    if (bottoma < b.top || bottomb < a.top || righta < b.left || rightb < a.left)
//        return false;
//    return true;
//    /*if (bottoma >= b.top && (b.left <= righta && righta <= rightb || b.left <= a.left && a.left <= rightb))
//        return true;
//    return false;*/
//}
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

