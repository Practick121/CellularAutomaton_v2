#include "TypeAutomaton.h"

std::vector<int> TypeAutomaton::getsurvive() { return survive; }
std::vector<int> TypeAutomaton::getbirth() { return birth; }
TypeAutomaton::TypeAutomaton() { };
TypeAutomaton::TypeAutomaton(const std::vector<int> b, const std::vector<int> s):
    birth{ b },
    survive{ s }
{
}
