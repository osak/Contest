//Name: Walk the Talk
//Level: 3
//Category: 動的計画法,DP,Trie
//Note:

/**
 * Trieを作って文字列の状態を管理する。
 *   dp[x][y][state] = 座標(x,y)より左下で、Trie上の状態がstateであるパターン数
 * とすると、これは累積和と同様の構造になって
 *   dp[x][y][state] = dp[x-1][y][state] + dp[x][y-1][state] - dp[x-1][y-1][state]
 * とできる。
 * また、文字を消費して遷移する場合は
 *   dp[x][y][next] += dp[x][y][state]
 * となる。
 * この問題では、行を下からなめていくため、添字の遷移が逆順になることに注意。
 *
 * オーダーはO(WHK)。
 * ただしKはTrieのノード数。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

typedef long long LL;

struct Node {
    int id;
    bool terminal;
    Node *next[26];
};
Node _pool[4000];
int _pos;

Node* new_node() {
    Node *n = &_pool[_pos];
    n->id = _pos;
    for(int i = 0; i < 26; ++i) {
        n->next[i] = NULL;
    }
    n->terminal = false;
    ++_pos;
    return n;
}

char buf[40][40];
LL dp[40][40][4000];

bool solve() {
    int H, W;
    scanf("%d %d", &H, &W);
    TIMES(i, H) {
        scanf("%s", buf[i]);
    }

    _pos = 0;
    Node *root = new_node();
    char word[10];
    while(scanf("%s", word) != EOF) {
        Node *cur = root;
        char *ptr = word;
        while(*ptr) {
            Node *next = cur->next[*ptr-'A'];
            if(next == NULL) {
                next = cur->next[*ptr-'A'] = new_node();
            }
            cur = next;
            ++ptr;
        }
        cur->terminal = true;
    }

    LL ans = 0;
    dp[H-1][0][0] = 1;
    if(Node *next = root->next[buf[H-1][0]-'A']) {
        dp[H-1][0][next->id] = 1;
    }
    for(int r = H-1; r >= 0; --r) {
        for(int c = 0; c < W; ++c) {
            for(int state = 0; state < _pos; ++state) {
                const Node *cur = &_pool[state];
                int sum = 0;
                if(r+1 < H) sum += dp[r+1][c][state];
                if(c > 0) sum += dp[r][c-1][state];
                if(r+1 < H && c > 0) sum -= dp[r+1][c-1][state];
                dp[r][c][state] += sum;
                if(Node *next = cur->next[buf[r][c]-'A']) {
                    dp[r][c][next->id] += sum;
                }
            }
        }
    }
    for(int state = 0; state < _pos; ++state) {
        if(_pool[state].terminal) ans += dp[0][W-1][state];
    }
    printf("%lld\n", ans);
    return false;
}

int main() {
    while(solve()) ;
    return 0;
}
