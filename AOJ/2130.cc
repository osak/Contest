//Name: Billion Million Thousand
//Level: 3
//Category: 再帰,動的計画法,DP
//Note:

/*
 * 数値のパース部とDP部に分かれる。
 * パース部では、メモ化再帰を使って一番大きくなる切り分け方を見つける。
 * DP部では、求めた桁数を作るようにナップザック問題を解く。
 */
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <climits>
#include <map>
#include <algorithm>

using namespace std;

map<string, int> memo;

int parse(const vector<pair<string, int> > &dict, const string &str) {
    int mx = -1;
    if(str.size() == 0) return 0;
    if(memo.count(str) > 0) return memo[str];

    for(int i = 0; i < dict.size(); ++i) {
        const string &s = dict[i].first;
        if(str.compare(0, s.size(), s) == 0) {
            int tmp = parse(dict, str.substr(s.size()));
            if(tmp >= 0) mx = max(mx, tmp+dict[i].second);
        }
    }
    return memo[str] = mx;
}

int main() {
    for(int C = 1; ; ++C) {
        int N;
        cin >> N;
        if(!N) break;

        memo.clear();
        vector<pair<string, int> > v(N);
        for(int i = 0; i < N; ++i) {
            cin >> v[i].first >> v[i].second;
        }

        string str;
        cin >> str;
        int digits = parse(v, str);

        vector<int> dp(digits+1, INT_MAX);
        dp[0] = 0;
        for(int i = 1; i <= digits; ++i) {
            for(int j = 0; j < v.size(); ++j) {
                if(v[j].second <= i) {
                    if(dp[i-v[j].second] != INT_MAX) dp[i] = min(dp[i], (int)(dp[i-v[j].second] + v[j].first.size()));
                }
            }
        }

        cout << "Case " << C << ": " << dp[digits] << endl;
    }
    return 0;
}
