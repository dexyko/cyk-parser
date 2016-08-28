#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <iterator>
#include <sstream>
#include <algorithm>

using namespace std;

const string wspace = " \n\r\t\f\v";

class Helper {
private:
public:
    static string& TrimRight(string& s, const string& t = wspace);
    static string& TrimLeft(string& s, const string& t = wspace);
    static string& Trim(string& s, const string& t = wspace);
    static string Trim(const char* s, const string& t = wspace);
    static vector<string> Tokenize(const string& s, const string& delims = wspace);
    static string TransformSequence(const string& s);
    static bool IsNonTerminal(const string& s);
    static bool IsTerminal(const string& s);
};
