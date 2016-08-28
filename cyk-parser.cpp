// cyk-parser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


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

struct TestCase {
    string m_grammarFile;
    string m_sequencesFile;
    TestCase(string grammarFile, string sequencesFile) : m_grammarFile(grammarFile), m_sequencesFile(sequencesFile) {}
};

void test(int testID, TestCase testCase) {
    cout << "################ TEST #" << testID << " ###############" << endl;
    cout << "# GRAMMAR FILE:  " << testCase.m_grammarFile << endl;
    cout << "# SEQUENCE FILE: " << testCase.m_sequencesFile << endl;
    cout << "#" << endl;

    try {
        ifstream in(testCase.m_sequencesFile.c_str());
        while (!in.eof()) {
            Rule::Reset();
            ChomskyGrammar grammar;
            grammar.LoadFromFile(testCase.m_grammarFile);

            ParseTree* parseTree;
            CYKParser parser;

            string line;
            getline(in, line);
            if (Helper::Trim(line).size() > 0) {
                if (parser.Parse(line, &grammar, &parseTree)) {
                    cout << "The sequence '" << line << "' was parsed SUCCESSFULLY!" << endl;
                    cout << parseTree->Print("") << endl;
                }
                else {
                    cout << "'" << line << "' DOESN'T belong to the grammar." << endl;
                }
            }
        }
    }
    catch (const char* ex) {
        cout << ex << endl;
    }
}

int main() {
    TestCase testCases[] = {
        TestCase("test_files/grammar1.in", "test_files/sequences.in"),
        TestCase("test_files/grammar2.in", "test_files/sequences.in"),
        TestCase("test_files/grammar3.in", "test_files/sequences.in"),
        TestCase("test_files/grammar4.in", "test_files/sequences.in"),
        TestCase("test_files/grammar5.in", "test_files/sequences.in"),
        TestCase("test_files/grammar6.in", "test_files/sequences.in")
    };
    size_t numTests = 6;
    for (size_t iTest = 0; iTest < numTests; iTest++) {
        test(iTest, testCases[iTest]);
    }
    system("pause");
    return 0;
}
