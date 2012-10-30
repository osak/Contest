//Name: Passing the Message
//Level: 3
//Category: DP,スタック
//Note:

/*
 * left follwer を見つけるには，左端から単調減少になる subsequence をスタックで管理すればよい．
 * 単調減少でなくなるような h を追加するときは，スタックトップが h より大きくなるまで pop してから h を push する．
 * このとき，最後に pop した要素が left follwer となる．
 * h より右にいる子供にとっては，h より左で h より背が低い子供は見えないか left follower になり得ないかのどちらかで，どちらにせよ興味がない．
 * right follower は列を反転させて同じことをすればよい．
 *
 * オーダーは O(N)．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>

using namespace std;

int kids[50000];
int lefts[50000], rights[50000];

void calc(int N, int *buf) {
    stack<pair<int,int> > stk;
    for(int i = 0; i < N; ++i) {
        const int h = kids[i];
        int last = -1;
        while(!stk.empty() && stk.top().first < h) {
            last = stk.top().second;
            stk.pop();
        }
        buf[i] = last;
        stk.push(make_pair(kids[i], i));
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    for(int CASE = 1; CASE <= T; ++CASE) {
        int N;
        cin >> N;
        for(int i = 0; i < N; ++i) {
            cin >> kids[i];
        }
        calc(N, lefts);
        reverse(kids, kids+N);
        calc(N, rights);
        reverse(rights, rights+N);
        cout << "Case " << CASE << ":" << endl;
        for(int i = 0; i < N; ++i) {
            const int r = rights[i] >= 0 ? (N-rights[i]) : 0;
            cout << lefts[i]+1 << ' ' << r << endl;
        }
    }
    return 0;
}
