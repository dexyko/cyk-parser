#include "grammar.h"

void ChomskyGrammar::LoadFromFile(const string& fileName) {
    ifstream in(fileName.c_str());
    if (!in.is_open()) {
        cerr << "ERROR opening " << fileName << "." << endl;
        return;
    }
    string line, NT, check, next;
    istringstream sin;

    for (int lineNumber = 1; !in.eof(); ++lineNumber) {
        getline(in, line);
        if (Helper::Trim(line).size() == 0) continue;
        vector<string> parts = Helper::Tokenize(line, "->");
        if (parts.size() == 2) {
            string leftSide = Helper::Trim(parts[0], " ");
            if (!Helper::IsNonTerminal(leftSide)) {
                cerr << "ERROR line #" << lineNumber << ": invalid left side, must be non terminal" << endl;
                continue;
            }
            vector<string> rightSide = Helper::Tokenize(parts[1], " ");
            if (rightSide.size() == 0) {
                cerr << "ERROR line #" << lineNumber << ": invalid right side, must have some derivation" << endl;
                continue;
            }
            if (rightSide.size() == 1) {
                string right = Helper::Trim(rightSide[0]);
                if (!Helper::IsTerminal(right)) {
                    cerr << "ERROR line #" << lineNumber << ": invalid right side, must be terminal" << endl;
                    continue;
                }
                rules.push_back(Rule(leftSide, right));
                continue;
            }
            if (rightSide.size() == 2) {
                string right1 = Helper::Trim(rightSide[0]), right2 = Helper::Trim(rightSide[1]);
                if (!Helper::IsNonTerminal(right1) || !Helper::IsNonTerminal(right2)) {
                    cerr << "ERROR line #" << lineNumber << ": invalid right side, must have two non-terminals" << endl;
                    continue;
                }
                rules.push_back(Rule(leftSide, right1, right2));
                continue;
            }
            cerr << "ERROR line #" << lineNumber << ": invalid right side, must have 1 terminal or 2 non-terminals" << endl;
            continue;
        } else {
            cerr << "ERROR line #" << lineNumber << ": invalid derivation, must be in format LEFT -> RIGHT where\n\tLEFT is non-terminal (named with first capital letter)\n\tRIGHT is either two non-terminals or one terminal" << endl;
            continue;
        }
    }
}
