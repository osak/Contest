#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

set<string> get(const string &str, const set<string> &ss) {
    int N = str.size();

    set<string> res;
    for(set<string>::const_iterator it = ss.begin(); it != ss.end(); ++it) {
        const string &str2 = *it;
        int M = str2.size();
        vector<vector<string> > dp(N+1, vector<string>(M+1, ""));

        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < M; ++j) {
                if(str[i] == str2[j]) {
                    dp[i+1][j+1] = dp[i][j] + str[i];
                }
                else {
                    if(dp[i][j].size() > 0) res.insert(dp[i][j]);
                }
            }
        }
        for(int i = 0; i < N; ++i)
            if(dp[i][M].size() > 0) res.insert(dp[i][M]);
        for(int i = 0; i < M; ++i) 
            if(dp[N][i].size() > 0) res.insert(dp[N][i]);
        if(dp[N][M].size() > 0) res.insert(dp[N][M]);
    }

    return res;
}

int main() {
    int N, M;
    cin >> N >> M;

    string a;
    cin >> a;
    set<string> ss;
    ss.insert(a);

    for(int i = 1; i < N; ++i) {
        string b;
        cin >> b;

        set<string> tmp = get(b, ss);
        ss = tmp;
    }

    string ans = "";
    for(set<string>::iterator it = ss.begin(); it != ss.end(); ++it) {
        if(ans.size() < it->size()) ans = *it;
    }

    cout << ans.size() << endl;

    return 0;
}
