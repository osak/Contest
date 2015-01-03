//Name: アットコーダーモンスターズ
//Level: 5
//Category: 
//Note: 

/**
 *
 */
#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

int chebyshev_dist(const pair<int,int> &a, const pair<int,int> &b) {
    return max(abs(a.first - b.first), abs(a.second - b.second));
}

bool solve(bool first) {
    int N, K;
    if(!(cin >> N >> K)) return false;
    if(!N && !K) return false;

    // solve for N <= 20
    if(N > 20) return false;

    vector<pair<int,int>> v(N);
    for(int i = 0; i < N; ++i) {
        cin >> v[i].first >> v[i].second;
    }
    int best_score = 1000000;
    int ans = 0;
    for(int pat = 0; pat < (1<<N); ++pat) {
        if(__builtin_popcount(pat) != K) continue;
        vector<int> p;
        for(int i = 0; i < N; ++i) {
            if(pat & (1<<i)) p.push_back(i);
        }
        assert(p.size() == K);
        int score = 0;
        for (int i : p) {
            for (int j : p) {
                score = max(score, chebyshev_dist(v[i], v[j]));
            }
        }
        if(score == best_score) {
            ++ans;
        } else if(score < best_score) {
            best_score = score;
            ans = 1;
        }
    }
    cout << best_score << endl;
    cout << ans << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    bool first = true;
    while(solve(first)) {
        first = false;
    }
    return 0;
}
