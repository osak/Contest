//Name: Maximum Submatrix 2
//Level: 3
//Category: 動的計画法,DP,貪欲,Greedy,累積和
//Note:

/**
 * 各マスごとに、自分より右に1がいくつ連続しているかを配列でもっておく。
 * 開始列をひとつ決めると、連続している個数が多い行から順に消費していけば有利なのがわかるので、
 * ソートして上から調べていき、現在の幅✕行数で面積を出せばよい。
 *
 * ただし、ソートは愚直にO(N log N)かけるとTLEする。
 * 連続している個数について行数がわかればよいので、計数ソートっぽくしてO(N)にするとよい。
 *
 * オーダーはO(NM)。
 */
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <list>

using namespace std;

int calc(const vector<int> &cnt) {
    int ans = 0;
    const int N = cnt.size();
    int acc = 0;
    for(int i = N-1; i >= 1; --i) {
        acc += cnt[i];
        ans = max(ans, i * acc);
    }
    return ans;
}

bool solve() {
    int R, C;
    if(!(cin >> R >> C)) return false;
    if(!R && !C) return false;

    vector<vector<int>> strs(R);
    for(int i = 0; i < R; ++i) {
        string str;
        cin >> str;
        strs[i].resize(C, 0);
        for(int c = C-1; c >= 0; --c) {
            if(c+1 < C) strs[i][c] = strs[i][c+1];
            if(str[c] == '1') ++strs[i][c];
            else strs[i][c] = 0;
        }
    }
    int ans = 0;
    vector<int> cnt(C+1, 0);
    for(int pos = 0; pos < C; ++pos) {
        fill(cnt.begin(), cnt.end(), 0);
        for(auto &v : strs) {
            ++cnt[v[pos]];
        }
        ans = max(ans, calc(cnt));
    }
    cout << ans << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
