#include "Table.h"

Table::Table(sf::RenderWindow* iw1, Camera* camera1, sf::Rect<float> rect1) :
    iw{ iw1 },
    rect{ rect1 },
    camera{ camera1 }
{
    M.assign(Config::SIZET, std::vector<int>(Config::SIZET, 0));
    initGenerColors(cellColor);
    cellrect = { 0, 0, rect.width / (Config::SIZET) , rect.width / (Config::SIZET) };
    vertexarray.reserve(Config::SIZET * Config::SIZET * 4);
    cellForEach([&](float i, float j) { addQuad(i, j);});
    setrandom();

    shape.setFillColor(backgroundColor);
    shape.setPosition({ 0, 0 });
    shape.setSize(rect.getSize());

}

void Table::nextgeneration() {
    std::vector<int> surv = Gl::mode.getSurvive(), birth = Gl::mode.getBirth();
    cellForEach([&](float i, float j) {
        int cnt = getcntnbrs(i, j);
        if (M[i][j] == 0 && find(birth.begin(), birth.end(), cnt) != birth.end())
            update.push_back({ { i, j }, 1 });
        else if (M[i][j] == 1 && find(surv.begin(), surv.end(), cnt) == surv.end() || M[i][j] > 1)
            update.push_back({ { i, j }, (M[i][j] + 1) % Gl::mode.getCntGen()});
        });
	updateVertexArray();
}
void Table::setBackgroundColor(sf::Color col)
{
    backgroundColor = col;
    shape.setFillColor(col);
}
void Table::setCellColor(sf::Color col)
{
    cellColor = col;
    initGenerColors(col);
    cellForEach([&](float i, float j) {
        update.push_back({{ i, j }, M[i][j]});
        });
    updateVertexArray();
}
void Table::setrandom() { 
    cellForEach([&](float i, float j){
        update.push_back({ { i, j }, ((int)(getrandom(1, 100) <= Config::chance)) });
        });
    updateVertexArray();
}
void Table::clean() { 
    cellForEach([&](float i, float j) {
        M[i][j] = 0;
        update.push_back({ { i, j }, 0 });
    });

    updateVertexArray();
}
void Table::setcustom() {
    cellForEach([&](float i, float j) {
        if (i <= Config::SIZET / 2 + sizeSquare && i >= Config::SIZET / 2 - sizeSquare\
            && j <= Config::SIZET / 2 + sizeSquare && j >= Config::SIZET / 2 - sizeSquare)
            update.push_back({ { i, j }, ((int)(Config::chance >= getrandom(1, 100))) });
        else
            update.push_back({ { i, j }, 0 });
        });
    updateVertexArray();
}

void Table::updateVertexArray() {
    for (auto el : update) {
        int i = el.first.x, j = el.first.y;
        M[i][j] = el.second;
        setColor(i, j, Config::GENER_COLORS[M[i][j]]);
    }
    update.clear();
}
int Table::getcntnbrs(int i, int j) {
    int sz = Config::SIZET;
    int ans = 0;
    int ip = (i - 1 + sz) % sz, jp = (j - 1 + sz) % sz;
    int in = (i + 1 + sz) % sz, jn = (j + 1 + sz) % sz;
    int inn = (in + 1 + sz) % sz, jnn = (jn + 1 + sz) % sz;
    int ipp = (ip - 1 + sz) % sz, jpp = (jp - 1 + sz) % sz;
    int nb4 = isalive(ip, j) + isalive(i, jp) + isalive(i, jn) + isalive(in, j);
    if (Gl::mode.getTypenbrs() == "4")
        return nb4;
    int nb8 = nb4 + isalive(ip, jp) + isalive(ip, jn) + isalive(in, jp) + isalive(in, jn);
    if (Gl::mode.getTypenbrs() == "8")
        return nb8;
    int nb12 = nb8 + isalive(ipp, j) + isalive(inn, j) + isalive(i, jpp) + isalive(i, jnn);
    if (Gl::mode.getTypenbrs() == "12")
        return nb12;
    int nb24 = nb12 +
        isalive(ipp, jpp) + isalive(ipp, jp) + isalive(ip, jpp) +
        isalive(inn, jpp) + isalive(inn, jp) + isalive(in, jpp) +
        isalive(ipp, jnn) + isalive(ipp, jn) + isalive(ip, jnn) +
        isalive(inn, jnn) + isalive(inn, jn) + isalive(in, jnn);
    if (Gl::mode.getTypenbrs() == "24")
        return nb24;
    return 0;
}
bool Table::isalive(int i, int j)
{
    //return M[i][j] > 0;
    return M[i][j] == 1;
}
void Table::printmatrix()
{
    cellForEach([&](float i, float j) {
        std::cout << M[i][j] << ' ';
        if (j == Config::SIZET - 1)
            std::cout << std::endl;
        });
}
void Table::setColor(int i, int j, sf::Color col) {
	int index = (i * Config::SIZET + j) * 4;
    for (int k = 0; k < 4; k++) 
        vertexarray[index + k].color = col;
}
bool Table::ispressed() { return sf::Mouse::isButtonPressed(sf::Mouse::Left) && rect.contains(get_mouse_pos(iw)); }
std::vector<std::vector<int>> Table::getmatrix() { return M; }

void Table::addQuad(int i, int j) {
	int x = j * cellrect.width;
	int y = i * cellrect.height;
	std::vector<sf::Vertex> quad(4);
	quad[0].position = sf::Vector2f(x, y);
	quad[1].position = sf::Vector2f(x, y + cellrect.height);
	quad[2].position = sf::Vector2f(x + cellrect.width, y + cellrect.height);
	quad[3].position = sf::Vector2f(x + cellrect.width, y);
    
    quad[0].color = Config::GENER_COLORS[Gl::mode.getCntGen()];
    quad[1].color = Config::GENER_COLORS[Gl::mode.getCntGen()];
    quad[2].color = Config::GENER_COLORS[Gl::mode.getCntGen()];
    quad[3].color = Config::GENER_COLORS[Gl::mode.getCntGen()];
    for (int i = 0; i < 4; i++)
        vertexarray.push_back(quad[i]);
}

void Table::check() {
    if (ispressed()) {
		sf::Vector2f mouse_pos = get_mouse_pos(iw);
        mouse_pos = iw->mapPixelToCoords({(int)mouse_pos.x, (int)mouse_pos.y}, (*camera).view);
        sf::Vector2i cell_pos = { (int)((mouse_pos.x - rect.left) / cellrect.width),
                                   (int)((mouse_pos.y - rect.top) / cellrect.height) };
        if (std::max(cell_pos.x, cell_pos.y) >= Config::SIZET || std::min(cell_pos.x, cell_pos.y) < 0)
            std::cout << "abroad\n";
        else {
            M[cell_pos.y][cell_pos.x] = brush;
			setColor(cell_pos.y, cell_pos.x, Config::GENER_COLORS[brush]);
        }
        pressed = true;
    }
    else
        pressed = false;
}

void Table::render() {
    iw->draw(shape);
    iw->draw(vertexarray.data(), vertexarray.size(), sf::Quads);
}

void Table::setmatrix(std::vector<std::vector<int>>* M1) {
    clean();
    int len1 = M1->size();
    for (float i = 0; i < std::min(len1, Config::SIZET); i++)
        for (float j = 0; j < std::min(Config::SIZET, (int)(*M1)[i].size()); j++)
            update.push_back({ { i, j }, (*M1)[i][j] });
    updateVertexArray();
}

void Table::newAutomaton(TypeAutomaton aut)
{
    Gl::mode = aut;
}
