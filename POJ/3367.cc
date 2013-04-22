//Name: Expressions
//Level: 3
//Category: 構文解析,構文木
//Note:

/*
 * スタックのシミュレーションで構文木を作ってから，幅優先順序でノードを出力すればよい．
 *
 * オーダーは文字列料Lに対してO(L)．
 */

#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <stack>
#include <cctype>

using namespace std;

#define FOREACH(it,c) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

struct Node {
    Node *left, *right;
    char val;
} _pool[10000];

int _ptr = 0;
void init() {
    _ptr = 0;
}

Node* create_node(Node *left, Node *right, char val) {
    _pool[_ptr].left = left;
    _pool[_ptr].right = right;
    _pool[_ptr].val = val;
    return &_pool[_ptr++];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;
    TIMES(_, N) {
        init();

        string str;
        cin >> str;
        stack<Node*> stk;
        FOREACH(it, str) {
            if(islower(*it)) {
                stk.push(create_node(NULL, NULL, *it));
            } else {
                Node *right = stk.top();
                stk.pop();
                Node *left = stk.top();
                stk.pop();
                stk.push(create_node(left, right, *it));
            }
        }
        Node *root = stk.top();
        string ans;
        queue<Node*> q;
        q.push(root);
        while(!q.empty()) {
            Node *cur = q.front();
            q.pop();
            ans += cur->val;
            if(isupper(cur->val)) {
                q.push(cur->left);
                q.push(cur->right);
            }
        }
        reverse(ans.begin(), ans.end());
        cout << ans << endl;
    }
    return 0;
}
