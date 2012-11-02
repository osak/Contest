//Name: Rick the Persistent Gnu
//Level: 2
//Category: 幾何,シミュレーション
//Note:

/*
 * 条件の通りにシミュレーションするだけ．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <complex>

using namespace std;

typedef complex<double> P;
static const double PI = acos(-1.0);
static const double EPS = 1e-6;

inline double dot(const P& a, const P& b) { return a.real()*b.real() + a.imag()*b.imag(); }
inline double cross(const P& a, const P& b) { return a.real()*b.imag() - b.real()*a.imag(); }

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    while(true) {
        double Fx, Fy, D;
        int N, S;
        cin >> Fx >> Fy >> N >> S >> D;
        if(!N && !S) break;
        const P Fs(Fx, Fy);
        --S;

        vector<P> sites(N);
        for(int i = 0; i < N; ++i) {
            cin >> sites[i].real() >> sites[i].imag();
        }
        int cur = S;
        P prev_vec;
        for(int PHASE = 0; ; ++PHASE) {
            if(PHASE > 0) cout << ' ';
            cout << cur+1;
            int best = -1;
            double bestcos = -1;
            for(int i = 0; i < N; ++i) {
                if(i == cur) continue;
                if(abs(sites[cur]-sites[i]) > D) continue;
                const P vec = sites[i] - sites[cur];
                if(PHASE > 0 && dot(prev_vec, vec) < 0) continue; // avoid sharp turn
                const double cosval = fabs(dot(vec, Fs)/abs(vec)/abs(Fs));
                if(dot(vec, Fs) >= 0 && cosval > bestcos) {
                    best = i;
                    bestcos = cosval;
                }
            }
            if(best == -1) break;
            prev_vec = sites[best] - sites[cur];
            cur = best;
        }
        cout << endl;
    }
    return 0;
}
