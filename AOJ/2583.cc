//Name: JAG-channel
//Level: 2
//Category: 構文解析,実装
//Note:

/**
 * 最初にスレッドツリーを作成してからフォーマットする。
 * ある行の表示を決めるために必要な情報は
 * ・その行の深さ
 * ・それより浅い深さで、兄弟をもつノードが存在するときの深さ（|を出力するために必要）
 * したがって、最初にスレッドツリーを作る段階であるノードが兄弟をもつかを判定しておき、
 * どこに|を出力する必要があるかどうかを管理しながらDFS順でたどって出力すればよい。
 */
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stack>

using namespace std;

struct Node {
    string message;
    int depth;
    vector<Node*> children;
    bool has_sibiling;

    Node(const string &m, int depth) : message(m), depth(depth), has_sibiling(false) {}

    void add_child(Node *n) {
        if(children.size() > 0) children.back()->has_sibiling = true;
        children.push_back(n);
    }

    void print(unordered_map<int,int> &bars) {
        for(int i = 0; i < depth-1; ++i) {
            if(bars[i+1] > 0) cout << '|';
            else cout << ' ';
        }
        if(depth > 0) cout << '+';
        cout << message << endl;
        if(has_sibiling) bars[depth]++;
        for(Node *n : children) {
            n->print(bars);
        }
        if(has_sibiling) bars[depth]--;
    }
};

bool solve() {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    vector<Node*> roots;
    stack<Node*> stk;
    for(int i = 0; i < N; ++i) {
        string str;
        cin >> str;
        int depth = 0;
        while(str[depth] == '.') ++depth;
        string message = str.substr(depth);
        Node *n = new Node(message, depth);
        if(depth == 0) {
            roots.push_back(n);
            stk.push(n);
        } else {
            while(stk.top()->depth != depth-1) stk.pop();
            stk.top()->add_child(n);
            stk.push(n);
        }
    }
    for(Node *n : roots) {
        unordered_map<int,int> bars;
        n->print(bars);
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
