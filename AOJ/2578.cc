//Name: Disciple Life is Hard
//Level: 3
//Category: 動的計画法,DP,累積和
//Note: RUPC 2014 Day3

/**
 * 問題は3つの部分に分割できる。
 * ・体力をt消費するようなトレーニングの組み合わせで、最大の消費カロリーを求める
 * ・カロリーc以内でドーナツを組み合わせたときの幸福度の最大値を求める
 * ・d日目に体力をsだけ残しているときの幸福度の最大値を求める
 *
 * 1つ目は、[トレーニングの個数][消費体力] = 最大カロリー のDPで求められる（個数制限があるので、逆からDPすると楽）。
 * 2つ目は、カロリーがちょうどcになるときの最大幸福度を求め、maxで累積和を取ればよい。
 * （doughnuts[c] = max happiness[0 ≦c' ≦ c]）
 * 3つ目は、d日目開始時の体力と、その日に行うトレーニングの消費体力を用いてDPできる。
 *
 * オーダーは O(TUS + NTC + DS^2)。
 * ただし、Cは消費可能なカロリーの最大値。
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool solve() {
    int S, T, U, N, O, D;
    if(!(cin >> S >> T >> U >> N >> O >> D)) return false;

    // [count][energy] = max cal
    vector<vector<int>> training(U+1, vector<int>(S+1, -1));
    training[0][0] = 0;
    for(int i = 0; i < T; ++i) {
        int e, c;
        cin >> e >> c;
        for(int u = U; u >= 1; --u) {
            for(int s = S; s >= e; --s) {
                if(training[u-1][s-e] == -1) continue;
                training[u][s] = max(training[u][s], training[u-1][s-e] + c);
            }
        }
    }

    // [cal] = max score
    vector<long long> doughnuts(10001, -1);
    doughnuts[0] = 0;
    for(int i = 0; i < N; ++i) {
        int h, a;
        cin >> h >> a;
        for(int c = a; c <= 10000; ++c) {
            if(doughnuts[c-a] == -1) continue;
            doughnuts[c] = max(doughnuts[c], doughnuts[c-a] + h);
        }
    }
    // cumulate
    for(int c = 1; c <= 10000; ++c) {
        doughnuts[c] = max(doughnuts[c], doughnuts[c-1]);
    }

    // [stamina] = max score
    vector<long long> dp(S+1, -1);
    dp[S] = 0;
    for(int day = 0; day < D; ++day) {
        vector<long long> next(S+1, -1);
        for(int prev = 0; prev <= S; ++prev) { // previous stamina
            if(dp[prev] == -1) continue; // cannot reach such situation
            for(int t = 0; t <= prev; ++t) { // training
                if(training[U][t] == -1) continue; // No such combination of training
                const int ns = min(S, prev - t + O);
                next[ns] = max(next[ns], dp[prev] + doughnuts[training[U][t]]);
            }
        }
        dp.swap(next);
    }
    cout << *max_element(begin(dp), end(dp)) << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
