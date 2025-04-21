#pragma once
#include <iostream>
#include <vector>
class TypeAutomaton {
public:
    std::vector<int> getSurvive(), getBirth();
    void setSurvive(std::vector<int> s), setBirth(std::vector<int> b);
    int getCntGen(); 
    void setCntGen(int cnt);
    std::string getTypenbrs();
    void setTypenbrs(std::string s);
    TypeAutomaton();
    TypeAutomaton(const std::vector<int> b, const std::vector<int> s, int cnt_generations1, std::string typenbrs);
private:
    std::vector<int> survive, birth;
    int cnt_generations;
    std::string typenbrs;
};