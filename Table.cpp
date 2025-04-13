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
    cellshape.setSize(cellrect.getSize());
    deathshape.setSize(cellrect.getSize());
    tableshape.setSize(tablerect.getSize());
    cellshape.setFillColor(sf::Color::Black);
    deathshape.setFillColor(sf::Color::Red);
    for (int i = 0; i < Def::SIZET; i++) {
        for (int j = 0; j < Def::SIZET; j++) {
            addQuad(i, j);
        }
    }

    setrandom();
}

void Table::nextgeneration() {
    automaton.nextgeneration(Def::mode);
	updateVertexArray();
}
void Table::setrandom() { 
    automaton.setrandom();
    updateVertexArray();
}
void Table::clean() { 
    automaton.clean(); 
    updateVertexArray();
}
void Table::setcustom() {
    automaton.setcustom();
    updateVertexArray();
}

void Table::updateVertexArray() {
    for (auto el : automaton.update) {
        int i = el.first.x, j = el.first.y;
        automaton.M[i][j] = el.second;
        setColor(i, j, el.second == 1 ? sf::Color::Black : sf::Color::White);
    }
    automaton.update.clear();
}

void Table::setColor(int i, int j, sf::Color col) {
	int index = (i * Def::SIZET + j) * 4;
    for (int k = 0; k < 4; k++) 
        vertexarray[index + k].color = col;
}
bool Table::ispressed() { return sf::Mouse::isButtonPressed(sf::Mouse::Left) && tablerect.contains(get_mouse_pos(w1)); }
std::vector<std::vector<int>> Table::getmatrix() { return automaton.M; }

void Table::addQuad(int i, int j) {
	int x = j * cellrect.width;
	int y = i * cellrect.height;
	std::vector<sf::Vertex> quad(4);
	quad[0].position = sf::Vector2f(x, y);
	quad[1].position = sf::Vector2f(x, y + cellrect.height);
	quad[2].position = sf::Vector2f(x + cellrect.width, y + cellrect.height);
	quad[3].position = sf::Vector2f(x + cellrect.width, y);

	quad[0].color = sf::Color::Black;
	quad[1].color = sf::Color::Black;
	quad[2].color = sf::Color::Black;
	quad[3].color = sf::Color::Black;
    for (int i = 0; i < 4; i++)
        vertexarray.push_back(quad[i]);
}

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
            automaton.M[cell_pos.y][cell_pos.x] = brush;
			setColor(cell_pos.y, cell_pos.x, brush == 1 ? sf::Color::Black : sf::Color::White);
        }
        pressed = true;
    }
    else {
        pressed = false;
    }
}

void Table::render() {
    w1->draw(vertexarray.data(), vertexarray.size(), sf::Quads);
    return;
    /*
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
    for (int i = 0; i < automaton.getsizet(); i++) {

        crd.x = mouselastpos.x - (mouselastpos.x) * (float)zoom;
        for (int j = 0; j < automaton.getsizet(); j++) {
            
            //crd = mouselastpos - (mouselastpos - crd) * (float)zoom;
            cellrect1.left = crd.x;
            cellrect1.top = crd.y;
            if (automaton.M[i][j] == 1 && tablerect.intersects(cellrect1)) {
                cellshape1.setPosition(crd);
                w1->draw(cellshape1);
            }
            else if (tablerect.contains(crd)) {
                deathshape1.setPosition(crd);
                (*w1).draw(deathshape1);
            }
            
            crd.x += dx;
        }
        crd.y += dy;
    }
	*/
}

void Table::setmatrix(std::vector<std::vector<int>>* M1) {
    int len1 = (*M1).size();
    for (int i = 0; i < len1; i++) {
        for (int j = 0; j < (*M1)[i].size(); j++)
            automaton.M[i][j] = (*M1)[i][j];
        for (int j = (*M1)[i].size(); j < automaton.getsizet(); j++) {
            automaton.M[i][j] = 0;
        }
    }
    for (int i = len1; i < automaton.getsizet(); i++) {
        for (int j = 0; j < automaton.getsizet(); j++)
            automaton.M[i][j] = 0;
    }

}

int Table::getrandom(int a, int b) { return automaton.getrandom(a, b); }
