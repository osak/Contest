#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

long long solve() {
    long long E, R;
    int N;
    cin >> E >> R >> N;
    vector<pair<long long,int> > vs(N);
    for(int i = 0; i < N; ++i) {
        cin >> vs[i].first;
        vs[i].second = i;
    }
    sort(vs.begin(), vs.end());
    reverse(vs.begin(), vs.end());

    vector<pair<long long,long long> > range(N, make_pair(0, E));
    long long ans = 0;
    for(vector<pair<long long,int> >::const_iterator it = vs.begin(); it != vs.end(); ++it) {
        long long v = it->first;
        int pos = it->second;
        long long need = range[pos].second;
        long long after = range[pos].first;
        long long use = need - after;
        ans += use * v;
        // Every activity before pos should last some energy
        for(int i = pos-1; i >= 0; --i) {
            range[i].first = max(range[i].first, max(0LL, need - R*(pos-i)));
        }
        // Every activity after pos, max value is constrainted by pos
        for(int i = pos+1; i < N; ++i) {
            range[i].second = min(range[i].second, min(E, after + R*(i-pos)));
        }
    }
    return ans;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int T;
    cin >> T;
    for(int CASE = 1; CASE <= T; ++CASE) {
        long long ans = solve();
        cout << "Case #" << CASE << ": " << ans << endl;
    }
}
