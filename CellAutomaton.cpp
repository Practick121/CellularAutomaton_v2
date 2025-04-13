#include "CellAutomaton.h"
int CellAutomaton::SIZET = Def::SIZET;
int CellAutomaton::getrandom(int a, int b) { return rand() % (b - a + 1) + a; }
int CellAutomaton::getsizet() { return SIZET; }
CellAutomaton::CellAutomaton() { M.assign(SIZET, std::vector<int>(SIZET, 0)); }
void CellAutomaton::setrandom() {
    for (float i = 0; i < SIZET; i++)
        for (float j = 0; j < SIZET; j++)
			update.push_back({ { i, j }, (int)(getrandom(1, 100) <= Def::chance)});
}
int CellAutomaton::getcntnbrs(int i, int j) {

    int ans = 0;
	int ipast = (i - 1 + SIZET) % SIZET, jpast = (j - 1 + SIZET) % SIZET;
	int inext = (i + 1 + SIZET) % SIZET, jnext = (j + 1 + SIZET) % SIZET;

    if (Def::typecheckingneighbours == 4)
        return M[ipast][j] + M[i][jpast] + M[i][jnext] + M[inext][j];
    else
	    return M[ipast][jpast] + M[ipast][j] + M[ipast][jnext] + M[i][jpast] + M[i][jnext] + M[inext][jpast] + M[inext][j] + M[inext][jnext];
}
void CellAutomaton::nextgeneration(TypeAutomaton mode) {
    std::unordered_set<int> surv = mode.getsurvive(), birth = mode.getbirth();
    for (float i = 0; i < SIZET; i+=1) {
        for (float j = 0; j < SIZET; j+=1) {
            int cnt = getcntnbrs(i, j);
            if (M[i][j] == 0 && birth.find(cnt) != birth.end())
                update.push_back({ { i, j }, 1 });
            else if (M[i][j] == 1 && surv.find(cnt) == surv.end())
                update.push_back({ { i, j }, 0 });
        }
    }
}
void CellAutomaton::setcustom() {
    for (float i = 0; i < SIZET; i++) {
        for (float j = 0; j < SIZET; j++) {
            /*if (j <= my.getSizeT() / 2)
                my.M[i][j] = 0;
            else
                my.M[i][j] = 1;*/
            int dl = 10;
            if (i <= SIZET / 2 + dl && i >= SIZET / 2 - dl\
                && j <= SIZET / 2 + dl && j >= SIZET / 2 - dl)
                update.push_back({ { i, j }, (int)(Def::chance >= getrandom(1, 100)) });
            else
				update.push_back({ { i, j }, 0 });
        }
    }
}
void CellAutomaton::printmatrix() {
    for (int i = 0; i < SIZET; i++) {
        for (int j = 0; j < SIZET; j++) {
            std::cout << M[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
void CellAutomaton::clean() {
    for (float i = 0; i < SIZET; i++) {
        for (float j = 0; j < SIZET; j++) {
            M[i][j] = 0;
			update.push_back({ { i, j }, 0 });
        }
    }
}
