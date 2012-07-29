#include <iostream>
#include <string>
#include <vector>
#include <climits>
#include <cstdio>

using namespace std;

const int INF = 100*30;

int main() {
    string A, B;
    cin >> A >> B;

    vector<vector<int> > v(26, vector<int>(26, INF));
    for(int i = 0; i < 26; ++i) v[i][i] = 0;
    int N;
    cin >> N;
    while(N--) {
        char a, b;
        int cost;
        cin >> a >> b >> cost;

        int ia = a-'a', ib = b-'a';
        v[ia][ib] = min(v[ia][ib], cost);
    }

    for(int k = 0; k < 26; ++k) 
        for(int i = 0; i < 26; ++i)
            for(int j = 0; j < 26; ++j)
                v[i][j] = min(v[i][j], v[i][k]+v[k][j]);

    if(A.size() != B.size()) {
        cout << -1 << endl;
    }
    else {
        unsigned ans = 0;
        bool fail = false;
        string res = "";
        for(int i = 0; i < A.size(); ++i) {
            if(A[i] == B[i]) {
                res += A[i];
                continue;
            }
            int ia = A[i]-'a', ib = B[i]-'a';
            char to_ch = 0;
            int cost = INF*10;
            for(int j = 0; j < 26; ++j) {
                if(v[ia][j] < INF && v[ib][j] < INF) {
                    if(v[ia][j]+v[ib][j] < cost) {
                        cost = v[ia][j] + v[ib][j];
                        to_ch = j+'a';
                    }
                }
            }
            if(to_ch == 0) {
                fail = true;
                break;
            }
            ans += cost;
            res += to_ch;
        }
        if(fail) cout << -1 << endl;
        else {
            cout << ans << endl;
            cout << res << endl;
        }
    }
    return 0;
}

