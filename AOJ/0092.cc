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
 * ナイーブに探索するとTLEするため，ここでは二分探索を使って計算量を落としている．
 * オーダーは累積和の計算がO(N^2)，正方形の探索がO(N^2 log N)であるから全体ではO(N^2 log N)．
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
                int left = 0, right = N+1;
                while(left < right-1) {
                    int size = (left+right)>>1;
                    const int er = r+size-1;
                    const int ec = c+size-1;
                    if(er >= N || ec >= N) {
                        right = size;
                    } else {
                        int marks = get(er, ec) - get(er, c-1) - get(r-1, ec) + get(r-1, c-1);
                        if(marks == 0) {
                            left = size;
                        } else {
                            right = size;
                        }
                    }
                }
                ans = max(ans, left);
            }
        }
        cout << ans << endl;
    }
    return 0;
}
