#include "helper.h"

string& Helper::trimRight(string& s, const string& t) {
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

string& Helper::trimLeft(string& s, const string& t) {
    s.erase(0, s.find_first_not_of(t));
    return s;
}

string& Helper::trim(string& s, const string& t) {
    return trimRight(trimLeft(s, t), t);
}

string Helper::trim(const char* s, const string& t) {
    string ts(s);
    return trim(ts, t);
}

vector<string> Helper::tokenize(const string& s, const string& delims) {
    vector<string> result;
    size_t curPos = s.find_first_not_of(delims, 0);
    size_t nextPos = s.find_first_of(delims, curPos);

    while (curPos != string::npos || nextPos != string::npos) {
        if (nextPos == string::npos) {
            result.push_back(s.substr(curPos, s.size() - curPos));
            curPos = string::npos;
        } else {
            result.push_back(s.substr(curPos, nextPos - curPos));
            curPos = s.find_first_not_of(delims, nextPos);
            nextPos = s.find_first_of(delims, curPos);
        }
    }
    return result;
}

