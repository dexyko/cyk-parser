#include "helper.h"

string& Helper::TrimRight(string& s, const string& t) {
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

string& Helper::TrimLeft(string& s, const string& t) {
    s.erase(0, s.find_first_not_of(t));
    return s;
}

string& Helper::Trim(string& s, const string& t) {
    return TrimRight(TrimLeft(s, t), t);
}

string Helper::Trim(const char* s, const string& t) {
    string ts(s);
    return Trim(ts, t);
}

vector<string> Helper::Tokenize(const string& s, const string& delims) {
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

string Helper::TransformSequence(const string& s) {
    vector<string> words = Tokenize(s, " ,.!?\"'");
    ostringstream out;
    copy(words.begin(), words.end(), ostream_iterator<string>(out, ""));
    string ret = out.str();
    transform(ret.begin(), ret.end(), ret.begin(), ::tolower);
    return ret;
}

bool Helper::IsNonTerminal(const string& s) {
    vector<string> parts = Tokenize(s);
    if (parts.size() != 1 || Trim(parts[0], " ").size() == 0) {
        return false;
    }
    string name = Trim(parts[0], " ");
    return isupper(name[0]);
}

bool Helper::IsTerminal(const string& s) {
    vector<string> parts = Tokenize(s);
    if (parts.size() != 1 || Trim(parts[0], " ").size() == 0) {
        return false;
    }
    string name = Trim(parts[0], " ");
    return islower(name[0]);
}
