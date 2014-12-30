//Name: Patisserie
//Level: 3
//Category: グラフ,Graph,最短経路,動的計画法,DP
//Note: 

/**
 * 半径r1のケーキの右に半径r2のケーキを詰めるとき、中心は sqrt(4*r1*r2) だけずらすことになる。
 * これを利用して、(使ったケーキの集合, 右端の直径)の各状態に対して、右端の中心をおける最小の座標を管理すれば、
 * 最短経路問題（もしくは、DAG性を利用したDP）として解くことが可能である。
 *
 * オーダーは O(N^3 2^N)。
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include <cassert>

using namespace std;

vector<int> n_by_popcnt[13];

bool solve() {
    string line;
    if(!getline(cin, line)) return false;

    istringstream is(line);
    int L;
    is >> L;
    vector<int> rs;
    int v;
    while(is >> v) rs.push_back(v);
    const int N = rs.size();

    sort(begin(rs), end(rs));
    vector<vector<double>> memo(N, vector<double>(1<<N, 1.0 / 0.0));
    for(int i = 0; i < N; ++i) {
        memo[i][1<<i] = rs[i];
    }

    for(int i = 1; i < N; ++i) {
        for (const auto& pat : n_by_popcnt[i]) {
            if((pat & ((1<<N)-1)) != pat) continue;
            for(int prev = 0; prev < N; ++prev) {
                for(int j = 0; j < N; ++j) {
                    if(pat & (1<<j)) continue;
                    const double nd = memo[prev][pat] + sqrt(4 * rs[prev] * rs[j]);
                    const int np = pat | (1<<j);
                    memo[j][np] = min(memo[j][np], nd);
                }
            }
        }
    }

    bool res = false;
    for(int i = 0; i < N; ++i) {
        if(memo[i][(1<<N)-1] + rs[i] <= L) {
            res = true;
            break;
        }
    }
    cout << (res ? "OK" : "NA") << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    for(int i = 0; i < (1<<12); ++i) {
        n_by_popcnt[__builtin_popcount(i)].push_back(i);
    }
    while(solve()) ;
    return 0;
}
