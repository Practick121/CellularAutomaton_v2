#include "TypeAutomaton.h"

std::unordered_set<int> TypeAutomaton::getsurvive() { return survive; }
std::unordered_set<int> TypeAutomaton::getbirth() { return birth; }
TypeAutomaton::TypeAutomaton() { };
TypeAutomaton::TypeAutomaton(std::unordered_set<int> b, std::unordered_set<int> s) {
    birth = b;
    survive = s;
}
