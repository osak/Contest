//Name: FarStrings
//Level: 3
//Category: 文字列,辞書順最小,動的計画法,DP
//Note: SRM617 Div1 Hard

/**
 * 編集距離を固定し先頭から1文字ずつ決めていき、条件を満たすかどうかを判定する。
 * 先頭k文字が決まっているとき、編集距離を最小化するにはsの末尾(N-k)文字を加えれば良い。
 * 逆に最大化するには、sに含まれない文字で残りの(N-k)文字を埋めればよい。
 *
 * オーダーは O(N^4 A)。
 * ただしAはアルファベットの個数(A = 26)。
 */
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <iostream>

using namespace std;

struct FarStrings {
    int edit_distance(const string &s1, const string &s2) {
        static int dp[32][32];
        fill_n((int*)dp, sizeof(dp) / sizeof(int), 100);
        const int N = s1.size();
        const int M = s2.size();
        for(int i = 0; i < N; ++i) {
            dp[i][0] = i;
        }
        for(int i = 0; i < M; ++i) {
            dp[0][i] = i;
        }
        for(int i = 1; i <= N; ++i) {
            for(int j = 1; j <= M; ++j) {
                dp[i][j] = min(
                        dp[i][j-1] + 1, // Remove
                        min(dp[i-1][j] + 1, // Insert
                        dp[i-1][j-1] + (s1[i-1] != s2[j-1]) // Replace
                        ));
            }
        }
        return dp[N][M];
    }

    string calc(const string &s, int need_dist, char not_used) {
        const int N = s.size();
        string res;
        for(int i = 0; i < N; ++i) {
            for(char ch = 'a'; ch <= 'z'; ++ch) {
                const string best_tmp = res + ch + s.substr(i+1);
                const string worst_tmp = res + ch + string(N-i-1, not_used);
                //cout << best_tmp << ' ' << worst_tmp << endl;
                const int best_ed = edit_distance(s, best_tmp);
                const int worst_ed = edit_distance(s, worst_tmp);
                //cout << best_ed << ' ' << worst_ed << endl;
                if(best_ed <= need_dist && need_dist <= worst_ed) {
                    res += ch;
                    break;
                }
            }
        }
        return res;
    }

    vector<string> find(const string &str) {
        vector<string> res;
        const int N = str.size();
        map<char, int> freq;
        for(char ch : str) {
            freq[ch]++;
        }
        char not_used = 0;
        for(char ch = 'a'; ch <= 'z'; ++ch) {
            if(freq[ch] == 0) {
                not_used = ch;
                break;
            }
        }
        for(int i = 1; i <= N; ++i) {
            res.push_back(calc(str, i, not_used));
        }
        return res;
    }
};
