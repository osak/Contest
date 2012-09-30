//Name: Square Searching
//Level: 2
//Category: 動的計画法,DP,累積和
//Note:

/*
 * 座標(0,0)と(r,c)をそれぞれ左上，右下に持つ矩形を考えて，その中の*の数を記憶しておく．
 * これを使うと任意の矩形内の*の数がO(1)で求められる．
 * 正方形の左上は任意に決められるのでN^2通り存在し，それに対応する右下の決め方は高々N通りである．
 * (正方形であることに注意)．
 * したがって，ナイーブに探索するとO(N^3)個の正方形について内部の*の数を数え，0個のもののサイズを覚えればよい．
 *
 * ただしこれだとTLEするので，それまでに見つかった最大の正方形より小さいものは考えなくて良いことに注目して枝刈りするとよい．
 * オーダーはO(N^3)だが枝刈りが効くため1秒以内には終わる．
 */
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int dp[1000][1000];
int N;

inline int get(int r, int c) {
    if(r < 0 || r >= N || c < 0 || c >= N) return 0;
    return dp[r][c];
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    while(cin >> N) {
        if(N == 0) break;
        for(int i = 0; i < N; ++i) {
            string line;
            cin >> line;
            for(int c = 0; c < N; ++c) {
                dp[i][c] = get(i-1, c) + get(i, c-1) - get(i-1, c-1);
                if(line[c] == '*') dp[i][c]++;
            }
        }
        int ans = 0;
        for(int r = 0; r < N; ++r) {
            for(int c = 0; c < N; ++c) {
                for(int size = ans+1; size <= N; ++size) {
                    const int er = r + size - 1;
                    const int ec = c + size - 1;
                    if(er >= N || ec >= N) break;
                    const int marks = get(er, ec) - get(er, c-1) - get(r-1, ec) + get(r-1, c-1);
                    if(marks == 0) {
                        ans = max(ans, size);
                    }
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
