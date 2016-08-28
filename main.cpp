
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "helper.h"
#include "rule.h"
#include "parsetree.h"
#include "grammar.h"
#include "cyk.h"

using namespace std;


int main() {
    //string testFile = "test1.in";
    //string testSequence = "sheeatsafishwithafork";
    //string testFile = "test2.in";
    //string testSequence = "ababa";
    //string testFile = "test3.in";
    //string testSequence = "baaba";
    //string testFile = "test4.in";
    //string testSequence = "aaabbb";
    //string testFile = "test_files/test5.in";
    //string testSequence = "theyoungboysawthedragon";
    //string testSequence = "Hegavetheyoungcatsomemilk";
    string testFile = "test_files/test6.in";
    string testSequence = "The dog saw the man.    ";

    ChomskyGrammar grammar;
    grammar.LoadFromFile(testFile);

    vector<int> starting;
    starting.push_back(0);

    ParseTree* parseTree;
    CYKParser parser;
    if (parser.Parse(testSequence, &grammar, &parseTree)) {
        cout << "The sequence '" << testSequence << "' was parsed SUCCESSFULLY!" << endl;
        cout << parseTree->Print("") << endl;
    } else {
        cout << "'" << testSequence << "' DOESN'T belong to the grammar." << endl;
    }


    return 0;
}
