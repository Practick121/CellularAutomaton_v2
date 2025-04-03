#pragma once
#include <iostream>
#include <vector>
#include "unordered_set"
class TypeAutomaton {
public:
    std::unordered_set<int> getsurvive(), getbirth();
    TypeAutomaton();
    TypeAutomaton(std::unordered_set<int> b, std::unordered_set<int> s);
private:
    std::unordered_set<int> survive, birth;
};