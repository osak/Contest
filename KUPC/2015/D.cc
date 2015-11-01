//Name: 
//Level: 
//Category: 
//Note: 

/**
 *
 */
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

bool solve() {
    int N;
    if(!(cin >> N)) return false;

    vector<pair<long long, long long>> ds(N+1);
    for(int i = 0; i < N; ++i) {
        cin >> ds[i].first;
    }
    for(int i = 0; i < N; ++i) {
        cin >> ds[i].second;
    }

    // (day, amt)
    vector<pair<long long, long long>> fastest(N+1);
    vector<long long> bestb(N+1);
    {
        fastest[0] = make_pair(0, 0LL);
        bestb[0] = ds[0].second;
        for(int i = 0; i < N; ++i) {
            const long long rem = fastest[i].second + ds[i].first;
            if(rem < 0) {
                if(bestb[i] <= 0) {
                    fastest[i+1].first = N;
                    break;
                } else {
                    const long long diff = -rem;
                    long long days = diff / bestb[i];
                    if(diff % bestb[i]) days++;
                    fastest[i+1] = make_pair(fastest[i].first + days + 1, rem + bestb[i] * days);
                }
            } else {
                fastest[i+1] = make_pair(fastest[i].first + 1, rem);
            }
            bestb[i+1] = max(bestb[i], ds[i+1].second);
        }
    }
    long long ans = 0;
    for(int i = 0; i <= N; ++i) {
        if(fastest[i].first > N) break;
        ans = max(ans, bestb[i] * (N - fastest[i].first) + fastest[i].second);
    }
    cout << ans << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    while(solve()) {
    }
    return 0;
}
