//Name: 
//Level: 
//Category: 
//Note: 

/**
 *
 */
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>
#include <cassert>
#include <cctype>
#include <queue>

using namespace std;

struct Node {
    Node *lhs, *rhs;
    char val;

    Node(const char val) : lhs(nullptr), rhs(nullptr), val(val) {}

    bool isDigit() const {
        return isdigit(val);
    }

    bool isOp() const {
        return !isDigit();
    }

    void dump(int level=0) const {
        cout << string(level, ' ');
        cout << val << endl;
        if(isOp()) {
            lhs->dump(level+1);
            rhs->dump(level+1);
        }
    }
};

Node* parse(const string &str) {
    vector<Node*> stk;
    for(const char c : str) {
        Node *node = new Node(c);
        if(node->isOp()) {
            assert(stk.size() >= 2);
            node->rhs = stk.back(); stk.pop_back();
            node->lhs = stk.back(); stk.pop_back();
            stk.push_back(node);
        } else if(node->isDigit()) {
            stk.push_back(node);
        } else {
            assert(false);
        }
    }
    assert(stk.size() == 1);
    return stk.back();
}

string convert(const Node *root) {
    queue<const Node*> q;
    string res;
    q.push(root);
    while(!q.empty()) {
        const Node *cur = q.front();
        q.pop();
        res += cur->val;
        if(cur->isOp()) {
            q.push(cur->lhs);
            q.push(cur->rhs);
        }
    }
    reverse(res.begin(), res.end());
    return res;
}

bool solve() {
    string str;
    if(!(cin >> str)) return false;
    Node *root = parse(str);
    //root->dump();
    cout << convert(root) << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    while(solve()) {
    }
    return 0;
}
