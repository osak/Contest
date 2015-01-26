//Name: ゲーマーじゃんけん
//Level: 3
//Category: 確率,期待値
//Note: 

/**
 * 期待値について漸化式を立てる。
 * 残り人数がn人の時、決着が付くまでに必要なラウンド数の期待値をE_nとすると
 *   E_n = 1 + Σ_{1≦i≦n} P(n,i)E_i
 * となる。ただし、P(n,i)は残り人数がn人のとき、1ラウンドの後に残り人数がi人になる確率である。
 * この形のままだとE_nが両辺にあって不便なため、移項して
 *   (1 - P(n, n))E_n = 1 + Σ_{1≦i<n} P(n,i)E_i
 * とすると、E_1 = 0から順に期待値を求めていくことができる。
 * また、P(n,i)はコンビネーションを求めるのと同様のDPによって計算することができる。
 *
 * オーダーは前処理の確率計算でO(N^3)、本質部分の計算はO(N^2)。
 */
#include <iostream>
#include <array>
#include <cassert>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

//const double EPS = 1e-9;

// prob[i][j][k] = i人でグーがj人、チョキがk人になる確率
//array<array<array<double,101>,101>,101> prob;
//array<array<array<int,101>,101>,101> winner;
double prob[101][101][101];
int winner[101][101][101];

int calc_winner(int g, int c, int p) {
    if(g == 0 && c == 0 && p == 0) return -1;

    // Pattern 1
    if(c == 0 && p == 0) return 0;
    if(g == 0 && p == 0) return 1;
    if(g == 0 && c == 0) return 2;

    int minhand = g;
    if(minhand == 0 || (c > 0 && minhand > c)) minhand = c;
    if(minhand == 0 || (p > 0 && minhand > p)) minhand = p;
    assert(minhand > 0);

    const int check = (g == minhand) + (c == minhand) + (p == minhand);
    // Pattern 2.1
    if(check == 1) {
        if(g == minhand) return 0;
        if(c == minhand) return 1;
        if(p == minhand) return 2;
        assert(false);
    }

    // Pattern 2.2
    if(check == 2) {
        if(g == minhand && c == minhand) return 0;
        if(c == minhand && p == minhand) return 1;
        if(p == minhand && g == minhand) return 2;
        assert(false);
    }

    // Pattern 2.3
    if(check == 3) {
        return -1;
    }
    assert(false);
}


void initialize() {
    for(int n = 0; n <= 100; ++n) {
        for(int j = 0; j <= 100; ++j) {
            for(int k = 0; k <= 100; ++k) {
                prob[n][j][k] = 0;
            }
        }
    }
    prob[0][0][0] = 1.0;
    for(int n = 1; n <= 100; ++n) {
        for(int j = 0; j <= n; ++j) {
            for(int k = 0; k <= n-j; ++k) {
                prob[n][j][k] = (prob[n-1][j][k] + prob[n-1][j-1][k] + prob[n-1][j][k-1]) / 3;
                winner[n][j][k] = calc_winner(j, k, n-j-k);
            }
        }
    }
}

bool solve(bool first) {
    int N;
    if(!(cin >> N)) return false;

    vector<vector<double>> mat(N+1, vector<double>(N+2, 0));
    for(int n = 0; n <= N; ++n) {
        for(int j = 0; j <= n; ++j) {
            for(int k = 0; k <= n-j; ++k) {
                int rem = n;
                if(winner[n][j][k] == 0) {
                    rem = j;
                } else if(winner[n][j][k] == 1) {
                    rem = k;
                }
                else if(winner[n][j][k] == 2) {
                    rem = n-j-k;
                }
                // The answer will be NaN or completely nonsense when this line is removed.
                // Compiled with: g++ -Wall -O2 -g -std=c++11 C.cc -o C
                // $ g++ --version
                // Configured with: --prefix=/Applications/Xcode.app/Contents/Developer/usr --with-gxx-include-dir=/usr/include/c++/4.2.1
                //    Apple LLVM version 5.1 (clang-503.0.40) (based on LLVM 3.4svn)
                //    Target: x86_64-apple-darwin13.4.0
                //    Thread model: posix
                //if(n == 0) cerr << n << ' ' << j << ' ' << k << ' ' << prob[n][j][k] << " -> " << rem << endl;

                mat[n][rem] += prob[n][j][k];
                mat[n][N+1] -= prob[n][j][k];
            }
        }
    }
    // E_1 = 0
    mat[1][N+1] = 0;
    for(int r = 0; r <= N; ++r) {
        mat[r][r] -= 1;
    }

    /*
    for(int r = 0; r <= N; ++r) {
        for(int c = 0; c <= N+1; ++c) {
            cout << mat[r][c] << ' ';
        }
        cout << endl;
    }
    */

    vector<double> val(N+1, 0);
    for(int r = 2; r <= N; ++r) {
        for(int c = 2; c < r; ++c) {
            val[r] += val[c] * mat[r][c];
        }
        val[r] += 1;
        val[r] /= -mat[r][r];
    }
    cout << val[N] << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    initialize();
    bool first = true;
    while(solve(first)) {
        first = false;
    }
    return 0;
}
