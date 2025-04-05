#include "CellAutomaton.h"
int CellAutomaton::SIZET = Def::SIZET;
int CellAutomaton::getrandom(int a, int b) { return rand() % (b - a + 1) + a; }
int CellAutomaton::getsizet() { return SIZET; }
CellAutomaton::CellAutomaton() { M.assign(SIZET + 2, std::vector<int>(SIZET + 2, 0)); }
void CellAutomaton::setrandom() {
    for (int i = 1; i <= SIZET; i++)
        for (int j = 1; j <= SIZET; j++)
            M[i][j] = getrandom(0, 1);
}
int CellAutomaton::getcntnbrs(int i, int j) {
    return M[i - 1][j - 1] + M[i - 1][j] + M[i - 1][j + 1] + M[i][j - 1] + M[i][j + 1]\
        + M[i + 1][j - 1] + M[i + 1][j] + M[i + 1][j + 1];
}
void CellAutomaton::nextgeneration(TypeAutomaton mode) {
    std::vector<std::vector<int>> M2(SIZET + 2, std::vector<int>(SIZET + 2, 0));
    std::unordered_set<int> surv = mode.getsurvive(), birth = mode.getbirth();
    for (int i = 1; i <= SIZET; i++) {
        for (int j = 1; j <= SIZET; j++) {
            //int cnt = getRandom_num(1, 8);
            int cnt = getcntnbrs(i, j);
            if (M[i][j] == 0 && birth.find(cnt) != birth.end())
                M2[i][j] = 1;
            else if (M[i][j] == 1 && surv.find(cnt) != surv.end())
                M2[i][j] = 1;
        }
    }
    for (int i = 1; i <= SIZET; i++)
        for (int j = 1; j <= SIZET; j++)
            M[i][j] = M2[i][j];
}
void CellAutomaton::printmatrix() {
    for (int i = 1; i <= SIZET; i++) {
        for (int j = 1; j <= SIZET; j++) {
            std::cout << M[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
void CellAutomaton::clean() {
    for (int i = 1; i <= SIZET; i++)
        for (int j = 1; j <= SIZET; j++)
            M[i][j] = 0;
}
