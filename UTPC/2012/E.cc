#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>
#include <cmath>

using namespace std;

vector<int> gen_order(const vector<long long> &as, long long S, long long M) {
    const int N = as.size();
    vector<pair<long long,int> > v;
    for(int i = 0; i < N; ++i) {
        v.push_back(make_pair(-(as[i]*M % S), i));
    }
    sort(v.begin(), v.end());

    vector<int> res;
    for(int i = 0; i < N; ++i) res.push_back(v[i].second);
    return res;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N;
    cin >> N;
    vector<long long> as(N), bs(N);
    long long S = 0;

    for(int i = 0; i < N; ++i) {
        cin >> as[i] >> bs[i];
        S += as[i];
    }

    long long ans = numeric_limits<long long>::max();
    for(int m = 0; m < S; ++m) {
        vector<int> order = gen_order(as, S, m);
        long long rem = m;
        for(int i = 0; i < N; ++i) {
            rem -= as[i]*m / S;
        }
        long long coef = 0;
        for(int i = 0; i < N; ++i) {
            const int party = order[i];
            long long need = bs[party];
            if(i < rem && need > 0) --need;
            //cout << m << ' ' << party << ' ' << need << endl;
            const long long numer = static_cast<long long>(S)*need - static_cast<long long>(as[party])*m;
            if(numer >= 0) {
                const long long denom = static_cast<long long>(as[party]) * S;
                const long long mod = numer % denom;
                const long long k = numer / denom + (mod == 0 ? 0 : 1);
                coef = max(coef, k);
            }
        }
        ans = min(ans, static_cast<long long>(m + coef*S));
    }
    //cout << ans << endl;
    while(true) {
        bool valid = true;
        vector<int> order = gen_order(as, S, ans);
        vector<long long> got(N, 0);
        long long rem = ans;
        for(int i = 0; i < N; ++i) {
            got[i] += as[i] * ans / S;
            rem -= got[i];
            //cout << "base " << got[i] << endl;
        }
        //cout << "rem: " << rem << endl;
        for(int i = 0; rem > 0 && i < N; ++i) {
            ++got[order[i]];
            --rem;
        }
        for(int i = 0; i < N; ++i) {
            //cout << got[i] << endl;
            if(bs[i] > got[i]) {
                valid = false;
                break;
            }
        }
        if(valid) break;
        ++ans;
    }

    cout << ans << endl;
    return 0;
}
