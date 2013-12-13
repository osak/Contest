//Name: Conting Rectangles is Fun
//Level: 4
//Category: 動的計画法,DP
//Note:

/**
 * (1,1)から(r,c)の範囲にある幅w、高さhの矩形の個数をDPによって求める。
 * このとき、求める答えは
 *   ∑(h=1..c-a+1) ∑(w=1..d-b+1)  cnt[c][d][h][w] 
 *                                - cnt[a+h-2][d][h][w]
 *                                - cnt[c][b+w-2][h][w] 
 *                                + cnt[a+h-2][b+w-2][h][w]
 * となる。
 * このままではO(Q N^2 M^2)になってしまい間に合わないので、上の式の各項を累積和によって高速に求められるようにする。
 * たとえば2項目に関しては、
 *   cnt'[r][c][h][w] = cnt[r+h-2][c][h][w]
 * という写像を考えて、この上で2次元累積和を求めればよい。
 * 他の項についても同様。
 *
 * オーダーはO(Q + N^2 M^2)。
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <bitset>

using namespace std;

typedef long long LL;
typedef bitset<41> Row;

bool can_place[41][41][41][41];
int cnt[41][41][41][41];
int dp[41][41][41][41];
int dp2[41][41][41][41];
int dp3[41][41][41][41];
int dp4[41][41][41][41];

void update(int arr[41][41][41][41], int a, int b, int c, int d) {
    arr[a][b][c][d] += arr[a][b][c-1][d] + arr[a][b][c][d-1] - arr[a][b][c-1][d-1];
}

bool solve() {
    int N, M, Q;
    if(!(cin >> N >> M >> Q)) return false;
    if(!N && !M && !Q) return false;

    vector<Row> field(N+1);
    field[0].set();
    for(int i = 0; i < N; ++i) {
        field[i+1].set();
        string s;
        cin >> s;
        for(int j = 0; j < M; ++j) {
            if(s[j] == '0') field[i+1][j+1] = 0;
        }
    }
    for(int r = 0; r <= 40; ++r) {
        for(int c = 0; c <= 40; ++c) {
            for(int h = 0; h <= 40; ++h) {
                for(int w = 0; w <= 40; ++w) {
                    can_place[r][c][h][w] = false;
                    cnt[r][c][h][w] = 0;
                    dp[r][c][h][w] = 0;
                    dp2[r][c][h][w] = 0;
                    dp3[r][c][h][w] = 0;
                    dp4[r][c][h][w] = 0;
                }
            }
        }
    }

    for(int r = 0; r <= N; ++r) {
        for(int c = 0; c <= M; ++c) {
            for(int h = 0; h <= N; ++h) {
                can_place[r][c][h][0] = true;
                cnt[r][c][h][0] = 1;
            }
            for(int w = 0; w <= M; ++w) {
                can_place[r][c][0][w] = true;
                cnt[r][c][0][w] = 1;
            }
        }
    }
    for(int r = 1; r <= N; ++r) {
        for(int c = 1; c <= M; ++c) {
            for(int h = 1; h <= N; ++h) {
                for(int w = 1; w <= M; ++w) {
                    can_place[r][c][h][w] = can_place[r-1][c][h-1][w] && can_place[r][c-1][h][w-1] && !field[r][c];
                }
            }
        }
    }

    for(int r = 1; r <= N; ++r) {
        for(int c = 1; c <= M; ++c) {
            for(int h = 1; h <= N; ++h) {
                for(int w = 1; w <= M; ++w) {
                    cnt[r][c][h][w] = cnt[r-1][c][h][w] + cnt[r][c-1][h][w] - cnt[r-1][c-1][h][w];
                    if(can_place[r][c][h][w]) cnt[r][c][h][w]++;
                    //cout << r << ' ' << c << ' ' << h << ' ' << w << ' ' << cnt[r][c][h][w] << ' ' << can_place[r][c][h][w] << endl;
                }
            }
        }
    }
    for(int r = 1; r <= N; ++r) {
        for(int c = 1; c <= M; ++c) {
            for(int h = 1; h <= N; ++h) {
                for(int w = 1; w <= M; ++w) {
                    dp[r][c][h][w] = cnt[r][c][h][w];
                    if(r+h-2 <= 40) dp2[r][c][h][w] = cnt[r+h-2][c][h][w];
                    if(c+w-2 <= 40) dp3[r][c][h][w] = cnt[r][c+w-2][h][w];
                    if(r+h-2 <= 40 && c+w-2 <= 40) dp4[r][c][h][w] = cnt[r+h-2][c+w-2][h][w];
                    update(dp, r, c, h, w);
                    update(dp2, r, c, h, w);
                    update(dp3, r, c, h, w);
                    update(dp4, r, c, h, w);
                }
            }
        }
    }
    for(int i = 0; i < Q; ++i) {
        int top, left, bottom, right;
        cin >> top >> left >> bottom >> right;
        const int s1 = dp[bottom][right][bottom-top+1][right-left+1];
        const int s2 = dp2[top][right][bottom-top+1][right-left+1];
        const int s3 = dp3[bottom][left][bottom-top+1][right-left+1];
        const int s4 = dp4[top][left][bottom-top+1][right-left+1];
        cout << s1-s2-s3+s4 << endl;
        /*
        for(int h = 1; h <= bottom-top+1; ++h) {
            for(int w = 1; w <= right-left+1; ++w) {
                ans += cnt[bottom][right][h][w] - cnt[top+h-2][right][h][w] - cnt[bottom][left+w-2][h][w] + cnt[top+h-2][left+w-2][h][w];
            }
        }
        cout << ans << endl;
        */
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
