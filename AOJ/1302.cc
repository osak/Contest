#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    while(true) {
        int M, N;
        cin >> M >> N;
        if(!M && !N) break;

        int ans = M;
        set<int> best;
        vector<int> v(N, 0);
        for(int i = 0; i < N; ++i) {
            string s;
            cin >> s;
            for(int j = 0; j < M; ++j) {
                v[i] <<= 1;
                v[i] |= (s[j] == '1');
            }
        }
        for(int pat = 0; pat < (1<<M); ++pat) {
            set<int> s;
            for(int i = 0; i < N; ++i) s.insert(v[i] & pat);
            if(s.size() == N) {
                int cnt = __builtin_popcount(pat);
                if(cnt < ans) {
                    ans = min(ans, __builtin_popcount(pat));
                    best = s;
                }
            }
        }

        for(set<int>::iterator it = best.begin(); it != best.end(); ++it) {
            for(int i = (1<<M); i; i >>= 1) {
                cout << ((*it&i) ? 1 : 0);
            }
            cout << endl;
        }
        cout << ans << endl;
    }
    return 0;
}
