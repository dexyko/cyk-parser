#pragma once

#include <string>
#include <sstream>
#include <map>

using namespace std;

class Rule {
public:
    Rule(string NT, string T): m_isTerminal(true), m_left(getID(NT)), m_right1(getID(T)), m_right2(-1) {}
    Rule(string NT, string NT1, string NT2): m_isTerminal(false), m_left(getID(NT)), m_right1(getID(NT1)), m_right2(getID(NT2)) {}
    string toString() {
        ostringstream out;
        if (m_isTerminal) {
            out << m_left << ":" << getNT(m_left) << " -> " << m_right1 << ":" << getNT(m_right1);
        } else {
            out << m_left << ":" << getNT(m_left) << " -> " << m_right1 << ":" << getNT(m_right1) << "  " << m_right2 << ":" << getNT(m_right2);
        }
        return out.str();
    }

    bool isTerminal() { return m_isTerminal; }
    int getLeft() { return m_left; }
    int getTerminal() { return m_right1; }
    int getRight1() { return m_right1; }
    int getRight2() { return m_right2; }

    static string getNT(int id);
    static int getNumNTs();

    static int GetStartingID();
protected:
    static map<string, int> NT2id;
    static map<int, string> id2NT;

    static int getID(const string& NT);

    bool    m_isTerminal;
    int     m_left;
    int     m_right1, m_right2;
};
