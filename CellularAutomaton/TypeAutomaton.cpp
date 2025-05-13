#include "TypeAutomaton.h"

std::vector<int> TypeAutomaton::getSurvive() { return survive; }
std::vector<int> TypeAutomaton::getBirth() { return birth; }

void TypeAutomaton::setSurvive(std::vector<int> s){    survive = s; }
void TypeAutomaton::setBirth(std::vector<int> b) {    birth = b; }

int TypeAutomaton::getCntGen() { return cnt_generations; }
void TypeAutomaton::setCntGen(int cnt) {    cnt_generations = cnt; }

std::string TypeAutomaton::getTypeCheck() { return typeCheck; }
void TypeAutomaton::setTypeCheck(std::string s) {   typeCheck = s; }

int TypeAutomaton::getRadius() {    return radius;}
void TypeAutomaton::setRadius(int radius1) {    radius = radius1; }

TypeAutomaton::TypeAutomaton() { };
TypeAutomaton::TypeAutomaton(const std::vector<int> b, const std::vector<int> s, int cnt_gerartions1, std::string typecheck1, int radius1) :
    birth{ b },
    survive{ s },
    cnt_generations{ cnt_gerartions1 },
    typeCheck{typecheck1},
    radius{radius1}
{
}