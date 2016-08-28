#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "helper.h"
#include "rule.h"
#include "parsetree.h"

using namespace std;

void loadRules(const string& fileName, vector<Rule> &rules) {
    ifstream in(fileName.c_str());
    if (!in.is_open()) {
        cerr << "ERROR opening " << fileName << "." << endl;
        return;
    }
    string line, NT, check, next;
    istringstream sin;
    int lineNumber = 1;

    while (!in.eof()) {
        getline(in, line);
        vector<string> parts = Helper::tokenize(line, "->");
        if (parts.size() != 2) {
            sin >> NT;
            if (NT.size() > 0 && sin.good()) {
                if (!sin.eof()) {
                    sin >> check;
                    if (check.size() > 0) {
                        if (islower(check[0])) {
                            if (!sin.eof()) {
                                cerr << "ERROR line #" << lineNumber << ": invalid terminal production. The right side must have non terminal or two NTs." << endl;
                            }
                            rules.push_back(Rule(NT, check));
                        } else {
                            if (sin.eof()) {
                                cerr << "ERROR line #" << lineNumber << ": invalid terminal production. The right side must have two NTs. " << endl;
                            } else {
                                sin >> next;
                                if (!sin.eof()) {
                                    cerr << "ERROR line #" << lineNumber << ": invalid terminal production. Not CNF." << endl;
                                } else {
                                    if (next.size() > 0) {
                                        rules.push_back(Rule(NT, check, next));
                                    } else {
                                        cerr << "ERROR line #" << lineNumber << ": invalid terminal production. Not CNF." << endl;
                                    }
                                }
                            }
                        }
                    } else {
                        cerr << "ERROR line #" << lineNumber << ": invalid production." << endl;
                    }
                } else {
                    cerr << "ERROR line #" << lineNumber << ": invalid production." << endl;
                }
            } else {
                cerr << "ERROR line #" << lineNumber << ": invalid production." << endl;
            }
        } else {
            cerr << "ERROR line #" << lineNumber << ": empty production." << endl;
        }
        lineNumber++;
    }
}

ParseTree* GenParseTree(int il, int len, int prule, vector<Rule> &rules, vector<vector<vector<int> > > &check, ParseTree* parent) {
    ParseTree *root;
    for (int irule = 0; irule < (int) rules.size(); irule++) {
        Rule rule = rules[irule];
        if (check[il][len][rule.getLeft()] != -1 && rule.getLeft() == prule) {
            int im = check[il][len][rule.getLeft()];
            if (im >= 0) {
                if (check[il][im - il + 1][rule.getRight1()] != -1 && check[im + 1][len - (im - il + 1)][rule.getRight2()] != -1) {
                    root = new ParseTree(rule.getLeft());
                    root->SetName(Rule::getNT(rule.getLeft()));
                    root->SetParent(parent);
                    root->SetLeftNode(GenParseTree(il, im - il + 1, rule.getRight1(), rules, check, root));
                    root->SetRightNode(GenParseTree(im + 1, len - (im - il + 1), rule.getRight2(), rules, check, root));
                }
            } else {
                int id = -(check[il][len][rule.getLeft()] + 2);
                root = new ParseTree(rule.getLeft());
                root->SetName(Rule::getNT(rule.getLeft()));
                ParseTree *termChild = new ParseTree(rules[id].getLeft());
                termChild->SetParent(root);
                termChild->SetName(Rule::getNT(rules[id].getRight1()));
                root->SetLeftNode(termChild);
                break;
            }
        }
    }
    return root;
}


bool CockeYoungerKasami(const string& sequence, vector<int> starting, vector<Rule> &rules, ParseTree **root) {
    int numRules = rules.size();
    vector<vector<vector<int> > > check(sequence.size() + 1, vector<vector<int> >(sequence.size() + 1, vector<int>(Rule::getNumNTs())));
//    int check[sequence.size() + 1][sequence.size() + 1][Rule::getNumNTs() + 1];
    for (size_t il = 0; il <= sequence.size(); il++) {
        for (size_t len = 0; len <= sequence.size(); len++) {
            for (size_t irule = 0; irule < rules.size(); irule++) {
                check[il][len][irule] = -1;
            }
        }
    }

    for (size_t il = 0; il < sequence.size(); il++) {
        for (size_t irule = 0; irule < rules.size(); irule++) {
            if (rules[irule].isTerminal()) {
                string terminal = Rule::getNT(rules[irule].getTerminal());
                if (il + terminal.size() <= sequence.size() && sequence.substr(il, terminal.size()) == terminal) {
                    check[il][terminal.size()][rules[irule].getLeft()] = -2 - irule;
                }
            }
        }
    }
    for (int len = 2; len <= (int) sequence.size(); len++) {
        for (int il = 0; il + len <= (int) sequence.size(); il++) {
            for (int irule = 0; irule < (int) rules.size(); irule++) {
                Rule rule = rules[irule];
                if (!rule.isTerminal()) {
                    int right1 = rule.getRight1();
                    int right2 = rule.getRight2();
                    for (int im = il; im < il + len; im++) {
                        if (check[il][im - il + 1][right1] != -1 && check[im + 1][len - (im - il + 1)][right2] != -1) {
                            check[il][len][rule.getLeft()] = im;
                        }
                    }
                }
            }
        }
    }

    for (size_t irule = 0; irule < starting.size(); irule++) {
        if (check[0][sequence.size()][starting[irule]] != -1) {
            *root = GenParseTree(0, sequence.size(), starting[irule], rules, check, NULL);
            return true;
        }

    }
    *root = NULL;
    return false;
}

int main() {
    vector<Rule> rules;
    string s = "  this is test  ";
    cout << Helper::trimLeft(s, " t") << endl;// << trim("    this is test too   ") << endl;
    s = "  another test delimited by, too";
    vector<string> tokens = Helper::tokenize(s, ", ");

    for (vector<string>::iterator it = tokens.begin(); it != tokens.end(); ++it) {
        cout << "'" << *it << "'" << endl;
    }
//    return 0;
    //string testFile = "test1.in";
    //string testWord = "sheeatsafishwithafork";
    //string testFile = "test2.in";
    //string testWord = "ababa";
    //string testFile = "test3.in";
    //string testWord = "baaba";
    //string testFile = "test4.in";
    //string testWord = "aaabbb";
    string testFile = "test_files/test5.in";
    string testWord = "theyoungboysawthedragon";
    //string testWord = "Hegavetheyoungcatsomemilk";
    vector<int> starting;
    starting.push_back(0);

    loadRules(testFile, rules);

    ParseTree* parseTree;
    cout << CockeYoungerKasami(testWord, starting, rules, &parseTree) << endl;
    if (parseTree != NULL) {
        cout << parseTree->Print("") << endl;
    } else {
        cout << "'" << testWord << "' doesn't belong to the grammar." << endl;
    }
}
