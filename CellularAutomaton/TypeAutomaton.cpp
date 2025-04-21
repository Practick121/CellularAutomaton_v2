#include "TypeAutomaton.h"

std::vector<int> TypeAutomaton::getSurvive() { return survive; }
std::vector<int> TypeAutomaton::getBirth() { return birth; }

void TypeAutomaton::setSurvive(std::vector<int> s)
{
    survive = s;
}

void TypeAutomaton::setBirth(std::vector<int> b)
{
    birth = b;
}



int TypeAutomaton::getCntGen() { return cnt_generations; }

void TypeAutomaton::setCntGen(int cnt)
{
    cnt_generations = cnt;
}

std::string TypeAutomaton::getTypenbrs() { return typenbrs; }

void TypeAutomaton::setTypenbrs(std::string s)
{
    typenbrs = s;
}

TypeAutomaton::TypeAutomaton() { };
TypeAutomaton::TypeAutomaton(const std::vector<int> b, const std::vector<int> s, int cnt_gerartions1, std::string typenbrs1) :
    birth{ b },
    survive{ s },
    cnt_generations{ cnt_gerartions1 },
    typenbrs{typenbrs1}
{
}