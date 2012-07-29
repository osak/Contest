#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Ax {
    int x, s, e;
};

int gcd(int a, int b) {
    if(b > a) return gcd(b, a);
    while(b) {
        int n = a % b;
        a = b;
        b = n;
    }
    return a;
}

inline int lcm(int a, int b) {
    return a*b/gcd(a,b);
}

int main() {
    while(true) {
        int N, V, T;
        cin >> N >> V >> T;
        if(!N && !V && !T) break;

        vector<Ax> axes(N);
        int mx = 1;
        for(int i = 0; i < N; ++i) {
            cin >> axes[i].x >> axes[i].s >> axes[i].e;
            mx = lcm(mx, axes[i].s+axes[i].e);
        }

        bool ok = false;
        for(int s = 0; s < mx; ++s) {
            ok = true;
            for(int i = 0; i < N; ++i) {
                int t = s + ceil((double)axes[i].x / V);
                int mod = axes[i].x % V;
                int ax = t % (axes[i].s+axes[i].e);
                if(((mod==0)?(axes[i].s <= ax):(axes[i].s < ax)) && ax <= axes[i].e) {
                    ok = false;
                    break;
                }
            }
            if(ok) break;
        }

        if(ok) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}
