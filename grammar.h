#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "rule.h"
#include "helper.h"

using namespace std;

class ChomskyGrammar {
public:
    ChomskyGrammar() {}
    ChomskyGrammar(string fileName) {
        this->LoadFromFile(fileName);
    }
    void LoadFromFile(const string& fileName);
public:
    vector<Rule> rules;
};
