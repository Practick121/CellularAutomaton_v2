#include "Table.h"

Table::Table(sf::RenderWindow* iw1, Camera* camera1, sf::Rect<float> rect1) :
    iw{ iw1 },
    rect{ rect1 },
    camera{ camera1 },
    Color_for_Gener{ Config::GENER_COLORS }
{
    M.assign(Config::SIZET, std::vector<int>(Config::SIZET, 0));

    cellrect = { 0, 0, rect.width / (Config::SIZET) , rect.width / (Config::SIZET) };
    vertexarray.reserve(Config::SIZET * Config::SIZET * 4);
    cellForEach([&](float i, float j) { addQuad(i, j);});
    setrandom();
}

void Table::nextgeneration() {
    std::vector<int> surv = Gl::mode.getsurvive(), birth = Gl::mode.getbirth();
    cellForEach([&](float i, float j) {
        int cnt = getcntnbrs(i, j);
        if (M[i][j] == 0 && find(birth.begin(), birth.end(), cnt) != birth.end())
            update.push_back({ { i, j }, Gl::CNT_GENER });
        //else if (M[i][j] > 0 && find(surv.begin(), surv.end(), cnt) == surv.end())
        //    update.push_back({ { i, j }, M[i][j] - 1});
        else if (M[i][j] == Gl::CNT_GENER && find(surv.begin(), surv.end(), cnt) == surv.end())
            update.push_back({ { i, j }, M[i][j] - 1 });
        else if (M[i][j] != 0 && M[i][j] != Gl::CNT_GENER)
            update.push_back({ {i, j}, M[i][j] - 1 });
        });
	updateVertexArray();
}
void Table::setrandom() { 
    cellForEach([&](float i, float j){
        update.push_back({ { i, j }, Gl::CNT_GENER * ((int)(getrandom(1, 100) <= Config::chance)) });
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
        int dl = 10;
        if (i <= Config::SIZET / 2 + dl && i >= Config::SIZET / 2 - dl\
            && j <= Config::SIZET / 2 + dl && j >= Config::SIZET / 2 - dl)
            update.push_back({ { i, j }, Gl::CNT_GENER * ((int)(Config::chance >= getrandom(1, 100))) });
        else
            update.push_back({ { i, j }, 0 });
        });
    updateVertexArray();
}

void Table::updateVertexArray() {
    for (auto el : update) {
        int i = el.first.x, j = el.first.y;
        M[i][j] = el.second;
        setColor(i, j, Color_for_Gener[M[i][j]]);
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
    if (Config::typecheckingneighbours == "4")
        return nb4;
    int nb8 = nb4 + isalive(ip, jp) + isalive(ip, jn) + isalive(in, jp) + isalive(in, jn);
    if (Config::typecheckingneighbours == "8")
        return nb8;
    int nb12 = nb8 + isalive(ipp, j) + isalive(inn, j) + isalive(i, jpp) + isalive(i, jnn);
    if (Config::typecheckingneighbours == "12")
        return nb12;
    int nb24 = nb12 +
        isalive(ipp, jpp) + isalive(ipp, jp) + isalive(ip, jpp) +
        isalive(inn, jpp) + isalive(inn, jp) + isalive(in, jpp) +
        isalive(ipp, jnn) + isalive(ipp, jn) + isalive(ip, jnn) +
        isalive(inn, jnn) + isalive(inn, jn) + isalive(in, jnn);
    if (Config::typecheckingneighbours == "24")
        return nb24;
    return 0;
}
bool Table::isalive(int i, int j)
{
    //return M[i][j] > 0;
    return M[i][j] == Gl::CNT_GENER;
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

    quad[0].color = Color_for_Gener[Gl::CNT_GENER];
	quad[1].color = Color_for_Gener[Gl::CNT_GENER];
	quad[2].color = Color_for_Gener[Gl::CNT_GENER];
	quad[3].color = Color_for_Gener[Gl::CNT_GENER];
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
			setColor(cell_pos.y, cell_pos.x, Color_for_Gener[brush]);
        }
        pressed = true;
    }
    else
        pressed = false;
}

void Table::render() {
    iw->draw(vertexarray.data(), vertexarray.size(), sf::Quads);
}

void Table::setmatrix(std::vector<std::vector<int>>* M1) {
    clean();
    int len1 = M1->size();
    for (float i = 0; i < len1; i++)
        for (float j = 0; j < (*M1)[i].size(); j++)
            update.push_back({ { i, j }, (*M1)[i][j] });
    updateVertexArray();
}
