
#include "rule.h"

string STARTING_SYMBOL = "S";

map<string, int> Rule::NT2id;
map<int, string> Rule::id2NT;

string Rule::getNT(int id) {
    if (id2NT.find(id) == id2NT.end()) {
        return "";
    } else {
        return id2NT[id];
    }
}

int Rule::getNumNTs() {
    return NT2id.size();
}

int Rule::getID(const string& NT) {
    if (NT2id.find(NT) == NT2id.end()) {
        NT2id[NT] = NT2id.size() - 1;
        id2NT[NT2id[NT]] = NT;
    }
    return NT2id[NT];
}

int Rule::GetStartingID() {
    if (NT2id.find(STARTING_SYMBOL) == NT2id.end()) {
        return -1;
    }
    return NT2id[STARTING_SYMBOL];
}
