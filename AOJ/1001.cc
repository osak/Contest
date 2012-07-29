#include <iostream>
#include <string>

using namespace std;

struct Node {
    Node *left, *right;

    Node() : left(NULL), right(NULL) {}

    Node* intersect(Node *other) {
        Node *n = new Node;
        if(this->left && other->left) {
            n->left = this->left->intersect(other->left);
        }
        if(this->right && other->right) {
            n->right = this->right->intersect(other->right);
        }
        return n;
    }

    Node* union_(Node *other) {
        Node *n = new Node;
        if(this->left && other->left) {
            n->left = this->left->union_(other->left);
        }
        else {
            n->left = this->left?this->left : other->left;
        }

        if(this->right && other->right) {
            n->right = this->right->union_(other->right);
        }
        else {
            n->right = this->right?this->right : other->right;
        }

        return n;
    }
};
ostream& operator << (ostream &os, const Node &node) {
    os << '(';
    if(node.left) os << *node.left;
    os << ',';
    if(node.right) os << *node.right;
    os << ')';
}

void skip(const string &str, char c, int &pos) {
    if(str[pos] != c) {
        cout << "Expected " << c << " but found " << str[pos] << " near " << str.substr(pos) << endl;
    }
    ++pos;
}

Node *getNode(const string &str, int &pos) {
    skip(str, '(', pos);

    Node *node = new Node;
    if(str[pos] == '(') node->left = getNode(str, pos);
    skip(str, ',', pos);
    if(str[pos] == '(') node->right = getNode(str, pos);
    skip(str, ')', pos);

    return node;
}

int main() {
    char cmd;
    string s1, s2;

    while(cin >> cmd >> s1 >> s2 && !cin.eof()) {
        int pos = 0;
        Node *n1 = getNode(s1, pos);
        pos = 0;
        Node *n2 = getNode(s2, pos);

        if(cmd == 'i') {
            cout << *(n1->intersect(n2)) << endl;
        }
        else {
            cout << *(n1->union_(n2)) << endl;
        }
    }
    return 0;
}

