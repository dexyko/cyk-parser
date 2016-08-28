#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "helper.h"
#include "rule.h"
#include "parsetree.h"
#include "grammar.h"

using namespace std;

class CYKParser {
public:
    bool Parse(const string& sequence, ChomskyGrammar* grammar, ParseTree** root) {
        //cout << "Parse(" << sequence << "...)" << endl;
        string transformedSequence = Helper::TransformSequence(sequence);
        cout << Rule::GetStartingID() << endl;
        if (Rule::GetStartingID() < 0) {
            cerr << "Missing starting non-terminal 'S'" << endl;
            *root = NULL;
            return false;
        }
        return CockeYoungerKasami(transformedSequence, Rule::GetStartingID(), grammar, root);
    }
private:
    vector<vector<vector<int> > > check;

    bool CockeYoungerKasami(const string& sequence, int starting, ChomskyGrammar* grammar, ParseTree** root) {
        //cout << "CYK(" << sequence << " ...)" << endl;
        check.clear();
        vector<int> perNonTerminal(Rule::getNumNTs());
        vector<vector<int> > perLength;
        //cout << "A" << endl;
        for (size_t i = 0; i <= sequence.size() + 1; i++) {
            perLength.push_back(perNonTerminal);
        }
        //cout << "B" << endl;
        for (size_t i = 0; i <= sequence.size() + 1; i++) {
            //cout<< "i=" << i << "/" << sequence.size() << endl;
            //cout << check.size() << endl;
            //cout << perLength.size() << endl;
            check.push_back(perLength);
        }
        //cout << "C" << endl;
        for (size_t il = 0; il <= sequence.size(); il++) {
          //  cout << "il1:" << il << endl;
            for (size_t len = 0; len <= sequence.size(); len++) {
                for (size_t irule = 0; Rule::getNumNTs(); irule++) {
                    check[il][len][irule] = -1;
                }
            }
        }

        for (size_t il = 0; il < sequence.size(); il++) {
            //    cout << "il=" << il << endl;
            for (size_t irule = 0; irule < grammar->rules.size(); irule++) {
                if (grammar->rules[irule].isTerminal()) {
                    string terminal = Rule::getNT(grammar->rules[irule].getTerminal());
                    if (il + terminal.size() <= sequence.size() && sequence.substr(il, terminal.size()) == terminal) {
                        check[il][terminal.size()][grammar->rules[irule].getLeft()] = -2 - irule;
                    }
                }
            }
        }
        for (int len = 2; len <= (int) sequence.size(); len++) {
            //cout << "len=" << len << endl;
            for (int il = 0; il + len <= (int) sequence.size(); il++) {
                for (int irule = 0; irule < (int) grammar->rules.size(); irule++) {
                    Rule rule = grammar->rules[irule];
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
            if (check[0][sequence.size()][starting] != -1) {
                *root = GenParseTree(0, sequence.size(), starting, grammar, NULL);

                return true;
            }

        *root = NULL;
        return false;
    }
    ParseTree* GenParseTree(int il, int len, int prule, ChomskyGrammar* grammar, ParseTree* parent) {
        //cout << il << ", " << len << ", " << prule << endl;
        ParseTree *root;
        for (int irule = 0; irule < (int) grammar->rules.size(); irule++) {
            Rule rule = grammar->rules[irule];
            if (check[il][len][rule.getLeft()] != -1 && rule.getLeft() == prule) {
                int im = check[il][len][rule.getLeft()];
                if (im >= 0) {
                    if (check[il][im - il + 1][rule.getRight1()] != -1 && check[im + 1][len - (im - il + 1)][rule.getRight2()] != -1) {
                        root = new ParseTree(rule.getLeft());
                        root->SetName(Rule::getNT(rule.getLeft()));
                        root->SetParent(parent);
                        root->SetLeftNode(GenParseTree(il, im - il + 1, rule.getRight1(), grammar, root));
                        root->SetRightNode(GenParseTree(im + 1, len - (im - il + 1), rule.getRight2(), grammar, root));
                    }
                } else {
                    int id = -(check[il][len][rule.getLeft()] + 2);
                    root = new ParseTree(rule.getLeft());
                    root->SetName(Rule::getNT(rule.getLeft()));
                    ParseTree *termChild = new ParseTree(grammar->rules[id].getLeft());
                    termChild->SetParent(root);
                    termChild->SetName(Rule::getNT(grammar->rules[id].getRight1()));
                    root->SetLeftNode(termChild);
                    break;
                }
            }
        }
        return root;
    }
private:

};

