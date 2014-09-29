//Name: Bridge Removal
//Level: 3
//Category: 木,Tree,動的計画法,DP
//Note:

/**
 * ある部分木を壊すときは、
 * ・その部分木を壊した後、親にもう一度戻ってくる必要がある
 * ・部分木を壊しっぱなしで、親には戻らなくてよい
 * の2つのパターンがある。
 * したがって、注目している頂点をvとすると、それぞれのコストは
 * ・dp[v][戻る必要がある] = Σdp[vの子][戻る必要がある] + d_{v,子}×3
 * ・dp[v][戻る必要がない] = min_{w} Σdp[vの子≠w][戻る必要がある] + d_{v,子×3} + dp[w][戻る必要がない] + d_{v,w}×2
 * となる。
 * あとは、始点を全ての頂点で試せばよい。
 *
 * オーダーは O(N^2)。
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <array>

using namespace std;
typedef unsigned long long ULL;
const ULL INF = 100000ULL * 800 * 4 * 2;

pair<ULL,ULL> calc(int root, int p, const vector<vector<pair<int,int>>> &graph) {
    ULL back = 0, noback = 0;
    pair<ULL,ULL> wspec(0, 0);
    int wd = 0;
    for(const auto &c : graph[root]) {
        if(c.first == p) {
            continue;
        }
        const auto spec = calc(c.first, root, graph);
        if(spec.first == 0) { // 葉は常に直接刈ってよい
            back += c.second;
            noback += c.second;
        } else {
            back += spec.first + c.second*3;
            const ULL tmp1 = noback + spec.first + c.second*3;
            const ULL tmp2 = noback - wspec.second + wspec.first + wd + spec.second + c.second*2;
            if(tmp1 <= tmp2) {
                noback = tmp1;
            } else {
                noback = tmp2;
                wspec = spec;
                wd = c.second;
            }
        }
    }
    //cout << root << ' ' << back << ' ' << noback << endl;
    return make_pair(back, noback);
}

bool solve() {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    vector<vector<pair<int,int>>> graph(N);
    vector<int> ps, ds;
    for(int i = 1; i < N; ++i) {
        int p;
        cin >> p;
        --p;
        ps.push_back(p);
    }
    for(int i = 1; i < N; ++i) {
        int d;
        cin >> d;
        ds.push_back(d);
    }
    for(int i = 0; i < N-1; ++i) {
        graph[ps[i]].emplace_back(i+1, ds[i]);
        graph[i+1].emplace_back(ps[i], ds[i]);
    }

    ULL ans = INF;
    for(int root = 0; root < N; ++root) {
        ans = min(ans, calc(root, -1, graph).second);
        //cout << "-----" << endl;
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
