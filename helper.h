#pragma once

#include <vector>
#include <string>

using namespace std;

const string wspace = " \n\r\t\f\v";

class Helper {
private:
public:
    static string& trimRight(string& s, const string& t = wspace);
    static string& trimLeft(string& s, const string& t = wspace);
    static string& trim(string& s, const string& t = wspace);
    static string trim(const char* s, const string& t = wspace);
    static vector<string> tokenize(const string& s, const string& delims = wspace);
};
