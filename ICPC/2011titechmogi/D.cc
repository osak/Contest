#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <complex>
using namespace std;
typedef complex<double> P;
static const double EPS = 1e-8;
namespace std {
    bool operator<(const P& a, const P& b) {
        if (fabs(a.real() - b.real()) < EPS) {
            return a.imag() < b.imag();
        } else {
            return a.real() < b.imag();
        }
    }
};

inline double dot(const P& a, const P& b) { return a.real()*b.real() + a.imag()*b.imag(); }
inline double cross(const P& a, const P& b) { return a.real()*b.imag() - b.real()*a.imag(); }

void convex(const vector<P>& ps, vector<P>& ch, vector<P>& ys)
{
    const int N = ps.size();
    vector<int> used(2*N, false);
    ch.resize(2*N);
    int k = 0;
    for (int i = 0; i < N; i++) {
        while (k >= 2 && cross(ch[k-1]-ch[k-2], ps[i]-ch[k-2]) <= EPS) {
            k--;
            used[k] = false;
        }
        ch[k] = ps[i];
        used[i] = true;
        k++;
    }
    for (int i = N-2, t = k+1; i >= 0; i--) {
        while (k >= t && cross(ch[k-1]-ch[k-2], ps[i]-ch[k-2]) <= EPS) {
            k--;
            used[k] = false;
        }
        ch[k] = ps[i];
        used[i] = true;
        k++;
    }
    ch.resize(k-1);
    for (int i = 0; i < N; i++) {
        if (!used[i]) {
            ys.push_back(ps[i]);
        }
    }
}

double angle(const P& a, const P& b)
{
    return acos(dot(a, b) / (abs(a)*abs(b)));
}

bool check_length(const vector<P>& xs1, const vector<P>& xs2, int i)
{
    const int M = xs1.size();
    for (int j = 0; j < M; j++) {
        if (fabs(abs(xs1[(j+1)%M] - xs1[j]) - abs(xs2[(i+j+1)%M] - xs2[(i+j)%M])) > EPS) {
            return false;
        }
    }
    return true;
}

bool check_inner(const P& o1, const P& o2, double theta, const vector<P>& ys1, const vector<P>& ys2)
{
    const int M = ys1.size();
    printf("theta=%g\n", theta);
    for (int i = 0; i < M; i++) {
        printf("  angle[%d] = %g\n", i, angle(ys1[i] - o1, ys2[i] - o2) > EPS);
        if (angle(ys1[i] - o1, ys2[i] - o2) > EPS) {
            return false;
        }
    }
    return true;
}

int main()
{
    int N;
    while (scanf("%d", &N) != EOF && N != 0) {
        vector<P> as, bs;
        for (int i = 0; i < N; i++) {
            double x, y;
            scanf("%lf %lf", &x, &y);
            as.push_back(P(x, y));
        }
        for (int i = 0; i < N; i++) {
            double x, y;
            scanf("%lf %lf", &x, &y);
            bs.push_back(P(x, y));
        }

        if (N == 1) {
            puts("0");
            continue;
        }
        vector<P> xs1, xs2, ys1, ys2;
        sort(as.begin(), as.end());
        sort(bs.begin(), bs.end());
        convex(as, xs1, ys1);
        convex(bs, xs2, ys2);
        if (xs1.size() != xs2.size()) {
            while (true) {}
        }
        if (ys1.size() != ys2.size()) {
            while (true) {}
        }
        cout << ys1.size() << ' ' << ys2.size() << endl;
        const int M = xs1.size();
        double ans = 100;
        for (int i = 0; i < M; i++) {
            const double theta = angle(xs1[1] - xs1[0], xs2[(i+1)%M] - xs2[i]);
            if (check_length(xs1, xs2, i) && check_inner(xs1[0], xs2[i], theta, ys1, ys2)) {
                ans = min(ans, theta);
            }
        }
        printf("%.7f\n", ans);
    }
    return 0;
}
