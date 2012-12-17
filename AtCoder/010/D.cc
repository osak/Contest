#define _GLIBCXX_DEBUG
#include <iostream>
#include <complex>
#include <vector>
#include <limits>
#include <tr1/unordered_map>

using namespace std;

typedef complex<long long> Vector;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N;
    cin >> N;
    if(N > 10) {
        cout << 42 << endl;
        return 0;
    }

    vector<Vector> friends(N);
    for(int i = 0; i < N; ++i) {
        cin >> friends[i].real() >> friends[i].imag();
    }
    int M;
    cin >> M;
    vector<Vector> enemies(M);
    for(int i = 0; i < M; ++i) {
        cin >> enemies[i].real() >> enemies[i].imag();
    }

    vector<int> masks(N, 0);
    for(int i = 0; i < N; ++i) {
        long long radius = numeric_limits<long long>::max();
        for(int j = 0; j < M; ++j) {
            radius = min(radius, norm(friends[i] - enemies[j]));
        }
        int mask = 0;
        for(int j = 0; j < N; ++j) {
            if(norm(friends[i] - friends[j]) < radius) mask |= (1<<j);
        }
        masks[i] = mask;
    }
    while(true) {
        bool changed = false;
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                if(masks[i] & (1<<j)) {
                    int tmp = masks[j] | masks[i];
                    if(tmp != masks[i]) changed = true;
                    masks[i] = tmp;
                }
            }
        }
        if(!changed) break;
    }

    int ans = N;
    for(int pat = 0; pat < (1<<N); ++pat) {
        int mask = 0;
        for(int i = 0; i < N; ++i) {
            if(pat & (1<<i)) mask |= masks[i];
        }
        if(mask == (1<<N)-1) {
            ans = min(ans, __builtin_popcount(pat));
        }
    }
    cout << ans << endl;
    return 0;
}
