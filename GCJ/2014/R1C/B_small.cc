#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

typedef long long LL;
const LL MOD = 1000000007;

void solve(int CASE) {
    int N;
    cin >> N;
    vector<string> v(N);
    for(int i = 0; i < N; ++i) {
        cin >> v[i];
    }
    map<string,int> cnt;
    sort(v.begin(), v.end());
    for(const string s : v) {
        cnt[s]++;
    }
    //v.erase(unique(v.begin(), v.end()), v.end());
    bool used[26];
    LL ans = 0;
    do {
        fill_n(used, 26, false);
        bool ok = true;
        int prev = -1;
        for(const string &s : v) {
            for(const int c : s) {
                if(used[c-'a']) {
                    ok = false;
                    break;
                }
                if(c != prev && prev != -1) {
                    //cout << "used " << (char)prev << endl;
                    used[prev-'a'] = true;
                }
                prev = c;
            }
            if(!ok) break;
        }
        if(ok) {
            ++ans;
            ans %= MOD;
            /*
            for(const string &s : v) {
                cout << s << ' ';
            }
            */
            //cout << endl;
        }
    } while(next_permutation(v.begin(), v.end()));
    for(const auto &p : cnt) {
        for(int i = 1; i <= p.second; ++i) {
            ans *= i;
            ans %= MOD;
        }
    }
    cout << "Case #" << CASE << ": " << ans << endl;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N;
    cin >> N;
    for(int CASE = 1; CASE <= N; ++CASE) {
        solve(CASE);
    }
    return 0;
}
