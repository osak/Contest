//Name: DNA repair
//Level: 4
//Category: 文字列,動的計画法,DP,Trie,Aho-Corasick
//Note:

/*
 * 禁止文字列をTrieに格納すると、最大で1020状態のオートマトンになる。
 * このオートマトン上の位置と、文字列上の位置を状態として変更文字数についてDP。
 *
 * TrieはAho-Corasick法を使うことで、マッチングの途中で失敗したときの遷移を正しく記述できる。
 * これは最初にTrieを構築しておき、すべての禁止文字列についてKMP法と同じテーブルを作成する操作を収束するまで繰り返すと得られる。
 * （Aho-Corasick法覚えてなかったので）
 * また，ある禁止文字列が他の禁止文字列の部分文字列になっている場合，どうせ短いほうで引っかかるので長い方は無視して良い．
 *
 * オーダーはO(LS)。ただしLは禁止パターンの合計長、Sは最後の文字列長。
 * KMP法の繰り返しが収束するまでの時間は評価していないが、そんなに遅くないはず……。
 */
#include <cstdio>
#include <string>
#include <cassert>
#include <vector>

using namespace std;

inline int to_idx(char c) {
    switch(c) {
        case 'A': return 0;
        case 'G': return 1;
        case 'C': return 2;
        case 'T': return 3;
    }
    assert(false);
}

struct Node {
    int index;
    Node *next[4];
    bool strict[4];
    bool terminal;
} nodes[1024];

int _pos;
Node* make_node(Node *root) {
    Node &n = nodes[_pos];
    n.index = _pos;
    fill_n(n.next, 4, root);
    fill_n(n.strict, 4, false);
    n.terminal = false;
    ++_pos;
    return &n;
}

void make_trie(Node *root, const string &str) {
    const int N = str.size();
    Node *cur = root;
    for(int i = 0; i < N; ++i) {
        const int c = to_idx(str[i]);
        Node *n = cur->next[c];
        if(n == root) {
            cur->next[c] = n = make_node(root);
            cur->strict[c] = true;
        }
        cur = n;
    }
    cur->terminal = true;
}

bool make_kmp(Node *root, const string &str) {
    const int N = str.size();
    bool changed = false;
    Node *cur = root, *shadow = root;
    for(int i = 0; i < N; ++i) {
        const int c = to_idx(str[i]);
        for(int j = 0; j < 4; ++j) {
            if(cur->strict[j]) continue;
            const Node *curn = cur->next[j];
            const Node *shadown = shadow->next[j];
            if(curn != shadown) {
                cur->next[j] = shadow->next[j];
                changed = true;
            }
        }
        cur = cur->next[c];
        if(i > 0) shadow = shadow->next[c];
    }
    return changed;
}

inline bool update(int &a, int v) {
    if(a > v) {
        a = v;
        return true;
    }
    return false;
}

void print_tree() {
    for(int i = 0; i < _pos; ++i) {
        printf("%d(%d): ", i, nodes[i].terminal);
        for(int j = 0; j < 4; ++j) {
            printf("%d ", nodes[i].next[j]->index);
        }
        puts("");
    }
}

const int INF = 10000000;

// dp[pos][state]
// state indicates before value of read str[pos]
int dp[1024][1024];

int main() {
    int N;
    int CASE = 1;
    while(scanf("%d", &N) != -1) {
        if(!N) break;
        _pos = 0;
        Node *root = make_node(NULL);
        fill_n(root->next, 4, root);

        char buf[1024];
        vector<string> strs;
        bool valid[N];
        fill_n(valid, N, true);
        for(int i = 0; i < N; ++i) {
            scanf("%s", buf);
            const string s(buf);
            strs.push_back(s);
            for(int j = 0; j < i; ++j) {
                if(strs[j].find(s) != string::npos) valid[j] = false;
                if(s.find(strs[j]) != string::npos) valid[i] = false;
            }
        }
        scanf("%s", buf);
        const string str(buf);

        for(int i = 0; i < N; ++i) {
            if(valid[i]) make_trie(root, strs[i]);
        }
        while(true) {
            bool changed = false;
            for(int i = 0; i < N; ++i) {
                if(!valid[i]) continue;
                bool b = make_kmp(root, strs[i]);
                changed = changed || b;
            }
            if(!changed) break;
        }
        //print_tree();

        fill_n((int*)dp, sizeof(dp)/sizeof(int), INF);
        const int L = str.size();
        const int S = _pos;
        dp[0][0] = 0;
        for(int pos = 0; pos < L; ++pos) {
            const int c = to_idx(str[pos]);
            for(int state = 0; state < _pos; ++state) {
                //printf("(%d %d) = %d\n", pos, state, dp[pos][state]);
                Node *cur = &nodes[state];
                for(int i = 0; i < 4; ++i) {
                    int cost = (c == i) ? 0 : 1;
                    Node *next = cur->next[i];
                    if(!next->terminal) update(dp[pos+1][next->index], dp[pos][state]+cost);
                }
            }
        }

        int ans = INF;
        for(int state = 0; state < _pos; ++state) {
            ans = min(ans, dp[L][state]);
        }
        if(ans == INF) ans = -1;
        printf("Case %d: %d\n", CASE, ans);
        ++CASE;
    }
    return 0;
}
