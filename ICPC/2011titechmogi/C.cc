#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <queue>
#include <complex>
using namespace std;
typedef complex<double> P;
static const double EPS = 1e-7;

inline double cross(const  P& a, const P& b) { return a.real()*b.imag() - b.real()*a.imag(); }

struct line
{
    P a, b;
    line() {}
    line(const P& p, const P& q) : a(p), b(q) {}
};

struct segment
{
    P a, b;
    segment() {}
    segment(const P& p, const P& q) : a(p), b(q) {}
    inline bool intersects(const line& ln) const { return cross(ln.b - ln.a, a - ln.a) * cross(ln.b - ln.a, b - ln.a) < EPS; }
    inline P intersection(const line& ln) const
    {
        const P x = b - a;
        const P y = ln.b - ln.a;
        return a + x*(cross(y, ln.a - a))/cross(y, x);
    }
};

int main()
{
    int N;
    while (cin >> N && N != 0) {
        double vw, vc;
        cin >> vw >> vc;
        vector<P> ps(N);
        for (int i = 0; i < N; i++) {
            cin >> ps[i].real() >> ps[i].imag();
        }

        vector<P> nodes(3*N);
        vector<vector<pair<int,double> > > g(3*N);
        for (int i = 0; i < N-1; i++) {
            g[3*i].push_back(make_pair(3*(i+1), vw));
            //printf("make normal edge %d -> %d\n", 3*i, 3*(i+1));
        }
        for (int i = 0; i < N; i++) {
            nodes[3*i] = ps[i];
            line ln(ps[i], ps[i] + P(1, 0));
            if (i > 0 && ps[i-1].imag() > ps[i].imag() + EPS) {
                for (int j = i-2; j >= 0; j--) {
                    segment s(ps[j], ps[j+1]);
                    if (s.intersects(ln)) {
                        nodes[3*i+1] = s.intersection(ln);
                        g[3*j].push_back(make_pair(3*i+1, vw));
                        g[3*i+1].push_back(make_pair(3*i, vc));
                        P& p = nodes[3*i+1];
                        //printf("make left edge %d -> %d(%g,%g) -> %d\n", 3*j, 3*i+1, p.real(), p.imag(), 3*i);
                        break;
                    }
                }
            }
            if (i < N-1 && ps[i].imag() < ps[i+1].imag()) {
                for (int j = i+1; j < N-1; j++) {
                    segment s(ps[j], ps[j+1]);
                    if (s.intersects(ln)) {
                        nodes[3*i+2] = s.intersection(ln);
                        g[3*i].push_back(make_pair(3*i+2, vc));
                        g[3*i+2].push_back(make_pair(3*(j+1), vw));
                        P& p = nodes[3*i+2];
                        //printf("make right edge %d -> %d(%g,%g) -> %d\n", 3*i, 3*i+2, p.real(), p.imag(), 3*(j+1));
                        break;
                    }
                }
            }
        }

        priority_queue<pair<double,int> > q;
        q.push(make_pair(0.0, 0));
        static const double INF = 1e10;
        vector<double> dist(3*N, INF);
        dist[0] = 0.0;
        while (!q.empty()) {
            const double c = -q.top().first;
            const int n = q.top().second;
            q.pop();
            if (n == 3*(N-1)) {
                printf("%.6f\n", c);
                break;
            }
            if (dist[n] < c) {
                continue;
            }

            for (vector<pair<int,double> >::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
                const int m = it->first;
                const double v = it->second;
                const double cc = c + abs(nodes[n] - nodes[m])/v;
                if (cc < dist[m]) {
                    //printf("%d -> %d(%g,%g) v=%g (%g)\n", n, *it, nodes[*it].real(), nodes[*it].imag(), v, cc);
                    dist[m] = cc;
                    q.push(make_pair(-cc, m));
                }
            }
        }
    }
    return 0;
}
