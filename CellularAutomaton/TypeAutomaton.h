#pragma once
#include <iostream>
#include <vector>
class TypeAutomaton {
public:
    std::vector<int> getSurvive(), getBirth();
    void setSurvive(std::vector<int> s), setBirth(std::vector<int> b);
    int getCntGen(); 
    void setCntGen(int cnt);
    std::string getTypeCheck();
    void setTypeCheck(std::string s);
    int getRadius();
    void setRadius(int radius1);
    TypeAutomaton();
    TypeAutomaton(const std::vector<int> b, const std::vector<int> s, int cnt_generations1, std::string typecheck, int radiusCheck);
private:
    std::vector<int> survive, birth;
    int cnt_generations, radius;
    std::string typeCheck;

};