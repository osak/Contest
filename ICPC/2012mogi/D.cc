#include <cstdio>
#include <vector>
#include <queue>
#include <complex>
#include <cmath>
using namespace std;
typedef complex<double> P;
static const double EPS = 1e-8;
static const double PI = acos(-1.0);

inline double dot(const P& a, const P& b) { return a.real()*b.real() + a.imag()*b.imag(); }
inline double cross(const P& a, const P& b) { return a.real()*b.imag() - b.real()*a.imag(); }

struct line
{
    P a, b;
    line() {}
    line(const P& p, const P& q) : a(p), b(q) {}

    inline P perpendicular(const P& p) const
    {
        const double t = dot(p-a, a-b)/dot(b-a, b-a);
        return a + t*(a-b);
    }

    inline double distance(const P& p) const
    {
        return abs(cross(p - a, b - a))/abs(b - a);
    }

    bool intersects(const line& ln) const { return !parallel(ln); }
    bool parallel(const line& ln) const { return abs(cross(ln.b - ln.a, b - a)) < EPS; }
};

struct segment
{
    P a, b;
    segment() {}
    segment(const P& p, const P& q) : a(p), b(q) {}
    inline bool intersects(const line& ln) const
    {
        return cross(ln.b - ln.a, a - ln.a) * cross(ln.b - ln.a, b - ln.a) < EPS;
    }

    inline bool intersects(const segment& seg) const
    {
        return
            max(a.real(), b.real()) >= min(seg.a.real(), seg.b.real())
            && max(seg.a.real(), seg.b.real()) >= min(a.real(), b.real())
            && max(a.imag(), b.imag()) >= min(seg.a.imag(), seg.b.imag())
            && max(seg.a.imag(), seg.b.imag()) >= min(a.imag(), b.imag())
            && cross(seg.b - seg.a, a - seg.a) * cross(seg.b - seg.b, b - seg.a) <= EPS
            && cross(b - a, seg.a - a) * cross(b - a, seg.b - a) <= EPS;
    }

    double distance(const segment& seg) const
    {
        double x = min(abs(a - seg.a), abs(a - seg.b));
        x = min(x, abs(b - seg.a));
        x = min(x, abs(b - seg.b));

        line l1(a, b), l2(seg.a, seg.b);
        //if (l1.parallel(l2)) {
        //    //fprintf(stderr, "par %g\n", x);
        //    return x;
        //}

        P p1 = l1.perpendicular(seg.a);
        //if (line(seg.a, p1).intersects(l1)) {
        if (intersects(segment(seg.a, p1))) {
            x = min(x, l1.distance(seg.a));
        }
        //fprintf(stderr, "  x1 = %g\n", x);
        P p2 = l1.perpendicular(seg.b);
        //if (line(seg.b, p2).intersects(l1)) {
        if (intersects(segment(seg.b, p2))) {
            x = min(x, l1.distance(seg.b));
        }
        //fprintf(stderr, "  p2 = (%g, %g)\n", p2.real(), p2.imag());
        //fprintf(stderr, "  x2 = %g\n", x);
        P q1 = l2.perpendicular(a);
        //fprintf(stderr, "  q1 = (%g, %g)\n", q1.real(), q1.imag());
        //if (line(a, q1).intersects(l2)) {
        if (seg.intersects(segment(a, q1))) {
            x = min(x, l2.distance(a));
        }
        //fprintf(stderr, "  x3 = %g\n", x);
        P q2 = l2.perpendicular(b);
        //if (line(b, q2).intersects(l2)) {
        if (seg.intersects(segment(b, q2))) {
            x = min(x, l2.distance(b));
        }
        //fprintf(stderr, "  x4 = %g\n", x);
        return x;
    }
};

struct star
{
    segment segs[5];
    star(double x, double y, double a, double r) {
        P o(x, y);
        P p(x, y + r);
        p -= o;
        P n = polar(1.0, a/180.0*PI);
        p *= n;
        P m = polar(1.0, 72.0/180.0*PI);
        P ps[5];
        for (int i = 0; i < 5; i++) {
            ps[i] = o + p;
            //fprintf(stderr, "ps[%d] = (%g,%g)\n", i, ps[i].real(), ps[i].imag());
            p *= m;
        }
        //fprintf(stderr, "  => p = (%g,%g)\n", p.real(), p.imag());
        for (int i = 0, j = 0; i < 5; i++) {
            segs[i] = segment(ps[j], ps[(j+2) % 5]);
            //fprintf(stderr, "seg[%d] = (%g,%g) - (%g,%g)\n", i, segs[i].a.real(), segs[i].a.imag(), segs[i].b.real(), segs[i].b.imag());
            j = (j+2) % 5;
        }
    }

    double distance(const star& s) const
    {
        double ans = 1e10;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (segs[i].intersects(s.segs[j])) {
                    //fprintf(stderr, "intersects!\n");
                    return 0.0;
                }
                //fprintf(stderr, "seg[%d] - seg[%d]\n", i, j);
                ans = min(ans, segs[i].distance(s.segs[j]));
            }
        }
        return ans;
    }
};

int main()
{
    int N, M, L;
    while (scanf("%d %d %d", &N, &M, &L) != EOF && N != 0) {
        --M; --L;
        vector<star> stars;
        for (int i = 0; i < N; i++) {
            int x, y, a, r;
            scanf("%d %d %d %d", &x, &y, &a, &r);
            stars.push_back(star(x, y, a, r));
        }

        vector<vector<double> > g(N, vector<double>(N));
        for (int i = 0; i < N; i++) {
            for (int j = i+1; j < N; j++) {
                double d = stars[i].distance(stars[j]);
                g[i][j] = g[j][i] = d;
                //fprintf(stderr, "%d - %d: %g\n", i, j, d);
            }
        }
        priority_queue<pair<double,int> > q;
        vector<double> dist(N, 1e10);
        dist[M] = 0;
        q.push(make_pair(0.0, M));
        while (!q.empty()) {
            const double d = -q.top().first;
            const int n = q.top().second;
            q.pop();
            //fprintf(stderr, "from n=%d\n", n);
            if (n == L) {
                printf("%.7f\n", fabs(d));
                break;
            }
            for (int i = 0; i < N; i++) {
                if (n == i) {
                    continue;
                }
                const double dd = d + g[n][i];
                if (dd < dist[i]) {
                    //fprintf(stderr, "  goto n=%d\n", i);
                    dist[i] = dd;
                    q.push(make_pair(-dd, i));
                }
            }
        }
    }
    return 0;
}
