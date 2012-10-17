//Name: Parliament
//Level: 2
//Category: 動的計画法,DP,累積和
//Note:

/*
 * 累積和を取って参照する典型問題．
 *
 * オーダーは入力と累積和の作成が最大で， O(RS)．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

inline int get(int r, int s, const vector<vector<int> > &v) {
    const int R = v.size();
    const int S = v[0].size();
    if(r < 0 || R <= r || s < 0 || S <= s) return 0;
    return v[r][s];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int N;
    cin >> N;
    while(N--) {
        int R, S;
        cin >> R >> S;
        vector<vector<int> > v(R, vector<int>(S));
        for(int r = 0; r < R; ++r) {
            for(int c = 0; c < S; ++c) {
                cin >> v[r][c];
            }
        }
        for(int r = 0; r < R; ++r) {
            for(int c = 0; c < S; ++c) {
                v[r][c] += get(r-1, c, v) + get(r, c-1, v) - get(r-1, c-1, v);
            }
        }
        int D;
        cin >> D;
        while(D--) {
            int r1, s1, r2, s2;
            cin >> r1 >> s1 >> r2 >> s2;
            --r1; --s1; --r2; --s2;
            const int sum = get(r2, s2, v) - get(r1-1, s2, v) - get(r2, s1-1, v) + get(r1-1, s1-1, v);
            cout << "Absolutni hodnota pohodlnosti je " << sum << " bodu." << endl;
        }
        cout << endl;
    }
    return 0;
}
