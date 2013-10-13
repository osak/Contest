//Name: 文字列
//Level: 5
//Category: 文字列,DP,動的計画法
//Note:

/**
 * dp[i][k] = i種類の文字を使って、k個の隣接ペアを作るパターン数
 * このとき、dp[i][k]に1種類文字を加えた時の遷移は
 *  1. 隣接している文字ペアのうち、新しい文字を挟む場所を決める
 *  2. 1.で決定した場所に入れる文字の個数を決める
 *  3. 2. の後にまだ文字が残っているのであれば、他に入れる場所を決める
 * i, k, 1.の場所の個数, 2.の文字数, 3.の場所の個数のそれぞれは可能な範囲で全探索すればよい。
 * これらは個数さえ決めれば、コンビネーションの計算によってパターン数が求められる。
 *
 * オーダーはO(NSM^3)程度。
 * ただし、Nはアルファベットの文字数(26)、Sは頻度の合計、Mは最大の頻度。
 * ループ回数は最高で 26*260*10^3 = 6760000 回程度になる。
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long LL;

const LL MOD = 1000000007; 

void add(LL &var, LL val) {
    var = (var + val%MOD) % MOD;
}

LL comb[300][300];
void init() {
    comb[0][0] = 1;
    for(int n = 1; n < 300; ++n) {
        for(int k = 0; k <= n; ++k) {
            const LL prev = (k == 0) ? 0 : comb[n-1][k-1];
            add(comb[n][k], prev + comb[n-1][k]);
        }
    }
}

// part x into n pieces (allowing empty)
LL partnum(int x, int n) {
    if(n == 0) return 1;
    return comb[x+n-1][n-1];
}

int main() {
    init();

    const int N = 26;
    vector<int> freqs(N);
    int sum = 0;
    for(int i = 0; i < N; ++i) {
        cin >> freqs[i];
        sum += freqs[i];
    }
    // dp[i] = have i adjacent pairs
    vector<LL> dp(sum+1, 0);
    dp[0] = 1;
    int acc = 0;
    for(int freq : freqs) {
        if(freq == 0) continue;
        vector<LL> next(sum+1, 0);
        for(int i = 0; i <= acc; ++i) {
            if(dp[i] == 0) continue;
            // split k adjacent pairs
            for(int k = 0; k <= min(i, freq); ++k) {
                // using j alphabets
                for(int j = k; j <= freq; ++j) {
                    LL pat = (comb[i][k] * partnum(j-k, k)) % MOD;
                    //cout << i << ' ' << k << ' ' << j << ' ' << pat << endl;
                    if(freq == j) {
                        add(next[i-k+(j-k)], dp[i] * pat);
                    } else {
                        // other alphabets will be inserted in l places
                        // (if remains any)
                        const int remain = freq-j;
                        for(int l = 1; l <= remain; ++l) {
                            const int next_idx = i - k + (j-k) + (remain-l);
                            LL pat2 = (dp[i] * pat % MOD * comb[acc+1-i][l]) % MOD * partnum(remain-l, l);
                            add(next[next_idx], pat2);
                        }
                    }
                    if(k == 0) break;
                }
            }
        }
        acc += freq;
        next.swap(dp);
        /*
        cout << "dp ";
        for(int i = 0; i <= acc; ++i) {
            cout << dp[i] << ' ';
        }
        cout << endl;
        */
    }
    cout << dp[0] << endl;
    return 0;
}
