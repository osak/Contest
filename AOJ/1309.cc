#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
#include <cstdio>
#include <cassert>
#include <set>
#include <queue>
#include <map>

using namespace std;

const double EPS = 1e-7;

typedef complex<double> Vector;

inline bool eqv(double a, double b) {
    return fabs(a-b) < EPS;
}

inline bool eqv(const Vector &a, const Vector &b) {
    return eqv(a.real(), b.real()) && eqv(a.imag(), b.imag());
}

inline bool contain(const Vector &p1, const Vector &p2, double y) {
    return min(p1.imag(), p2.imag()) < y && y < max(p1.imag(), p2.imag());
}

Vector linepos(const Vector &p1, const Vector &p2, double y) {
    const Vector &v = p2-p1;
    const double dy = p2.imag()-p1.imag();

    Vector res = p1 + v*(y-p1.imag())/dy;
    res.imag() = y;
    return res;
}

struct Tag {
    double cost;
    int left, right;

    Tag() {}
    Tag(double c, int l, int r) : cost(c), left(l), right(r) {}

    bool operator < (const Tag &other) const {
        return cost > other.cost;
    }
};

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        vector<Vector> v;
        set<int> ys;
        for(int i = 0; i < N; ++i) {
            int x, y;
            cin >> x >> y;
            v.push_back(Vector(x, y));
            ys.insert(y);
        }

        for(set<int>::iterator it = ys.begin(); it != ys.end(); ++it) {
            vector<Vector> new_v;
            for(int i = 0; i+1 < v.size(); ++i) {
                new_v.push_back(v[i]);
                if(contain(v[i], v[i+1], *it)) {
                    const Vector pt = linepos(v[i], v[i+1], *it);
                    new_v.push_back(pt);
                }
            }
            new_v.push_back(v.back());
            v = new_v;
        }
        N = v.size();

        double ans = 0;
        priority_queue<Tag> q;
        map<pair<int,int>, double> memo;
        q.push(Tag(0, 0, N-1));
        while(!q.empty()) {
            Tag t = q.top();
            q.pop();

            assert(eqv(v[t.left].imag(), v[t.right].imag()));
            if(t.left == t.right) {
                ans = t.cost;
                break;
            }
            pair<int,int> key = make_pair(t.left, t.right);
            if(memo.count(key) && memo[key] < t.cost) continue;
            memo[key] = t.cost;

            for(int dl = -1; dl <= 1; ++dl) {
                int nl = t.left + dl;
                if(nl < 0 || N <= nl) continue;
                for(int dr = -1; dr <= 1; ++dr) {
                    int nr = t.right + dr;
                    if(nr < 0 || N <= nr) continue;
                    if(!eqv(v[nl].imag(), v[nr].imag())) continue;

                    pair<int,int> nk = make_pair(nl, nr);
                    double nc = t.cost + abs(v[t.left]-v[nl]) + abs(v[t.right]-v[nr]);
                    if(!memo.count(nk) || nc < memo[nk]) {
                        memo[nk] = nc;
                        q.push(Tag(nc, nl, nr));
                    }
                }
            }
        }

        printf("%.3f\n", ans);
    }

    return 0;
}
