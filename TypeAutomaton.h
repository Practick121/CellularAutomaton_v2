#pragma once
#include <iostream>
#include <vector>
class TypeAutomaton {
public:
    std::vector<int> getsurvive(), getbirth();
    TypeAutomaton();
    TypeAutomaton(const std::vector<int> b, const std::vector<int> s);
private:
    std::vector<int> survive, birth;
};
