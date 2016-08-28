#pragma once

#include <string>
#include <sstream>

using namespace std;

class ParseTree {
public:
    ParseTree(int productionID): m_rootProduction(productionID), m_parent(NULL), m_leftNode(NULL), m_rightNode(NULL), m_name("") {}
    ~ParseTree() {
        if (m_leftNode != NULL) {
            delete m_leftNode;
            m_leftNode = NULL;
        }
        if (m_rightNode != NULL) {
            delete m_rightNode;
            m_rightNode = NULL;
        }
    }
    void SetName(const string &name) { m_name = name; }
    void SetLeftNode(ParseTree *node) { m_leftNode = node; }
    void SetRightNode(ParseTree *node) { m_rightNode = node; }
    void SetParent(ParseTree *node) { m_parent = node; }
    string GetName() { return m_name; }
    ParseTree* GetLeftNode() { return m_leftNode; }
    ParseTree* GetRightNode() { return m_rightNode; }
    ParseTree* GetParent() { return m_parent; }
    string Print(string tab) {
        ostringstream out;
        out << tab << m_name;
        if (m_leftNode != NULL) {
            if (m_rightNode == NULL) {
                out << "->" << m_leftNode->Print("");
            } else {
                out << "->\n" << tab << m_leftNode->Print(tab + "\t") << endl;
            }
        }
        if (m_rightNode != NULL) {
            out << tab << m_rightNode->Print(tab + "\t");
        }
        return out.str();
    }
protected:
    int         m_rootProduction;
    ParseTree   *m_parent;
    ParseTree   *m_leftNode;
    ParseTree   *m_rightNode;
    string      m_name;
};
