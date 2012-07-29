#include <iostream>
#include <vector>
#include <complex>
#include <utility>
#include <cstdio>
#include <cassert>
#include <algorithm>

using namespace std;

typedef complex<double> Vector;
typedef pair<Vector,Vector> Line;

const double EPS = 1e-7;

namespace std {
    bool operator < (const Vector &a, const Vector &b) {
        return a.real() < b.real();
    }
};

inline bool eqv(double a, double b) {
    return fabs(a-b) < EPS;
}

struct Comp {
    vector<Vector> vs;
    Comp(const vector<Vector> &vs) : vs(vs) {}

    bool operator ()(const int a, const int b) const {
        if(eqv(vs[a].real(), vs[b].real())) return a < b;
        return vs[a] < vs[b];
    }
};


//Verified PKU 2812
double cross(const Vector &v1, const Vector &v2) {
    return (v1.real()*v2.imag()) - (v1.imag()*v2.real());
}

bool intersect(const Vector &p11, const Vector &p12, const Vector &p21, const Vector &p22) {
    return (cross(p12-p11, p21-p11)*cross(p12-p11, p22-p11) < 0 &&
            cross(p22-p21, p11-p21)*cross(p22-p21, p12-p21) < 0 );
}

//Verified AOJ 0012
//Verified PKU 3348
double ccw(const Vector &p1, const Vector &p2, const Vector &p3) {
    return cross(p2-p1, p3-p1);
}

//Verified AOJ 1267(maybe too weak)
Vector crosspoint(const Line &l1, const Line &l2) {
    double a = cross(l1.second-l1.first, l2.second-l2.first);
    double b = cross(l1.second-l1.first, l1.second-l2.first);
    if(fabs(a) < EPS && fabs(b) < EPS) return l2.first;
    assert(fabs(a) >= EPS);
    return l2.first + b / a * (l2.second-l2.first);
}

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        int VW, VC;
        cin >> VW >> VC;

        vector<Vector> vs(N);
        vector<vector<double> > cost(N*3, vector<double>(N*3, 1e12));
        for(int i = 0; i < N; ++i) {
            cin >> vs[i].real() >> vs[i].imag();
        }

        for(int i = N-1; i >= 0; --i) {
            //Search Right
            double y = vs[i].imag();
            if(i+1 < N && vs[i+1].imag() > y) {
                for(int j = i+1; j < N; ++j) {
                    if(vs[j].imag() < y || eqv(vs[j].imag(), y)) {
                        //intersect with line (vs[j], vs[j-1])
                        //cout << "intersect " << vs[i] << ' '  << vs[j] << endl;
                        Vector pt = crosspoint(Line(vs[j], vs[j-1]+(vs[j-1]-vs[j])), Line(vs[i], Vector(vs[j].real()+10, y)));
                        vs.push_back(pt);
                        int idx = (int)vs.size()-1;
                        cost[idx][i] = (pt.real() - vs[i].real()) / VC;
                        break;
                    }
                }
            }

            //Search Left
            if(i-1 >= 0 && vs[i-1].imag() > y) {
                for(int j = i-1; j >= 0; --j) {
                    if(vs[j].imag() < y || eqv(vs[j].imag(), y)) {
                        //intersect with line (vs[j+1], vs[j])
                        Vector pt = crosspoint(Line(vs[j+1], vs[j]+(vs[j]-vs[j+1])), Line(vs[i], Vector(vs[j].real()-10, y)));
                        vs.push_back(pt);
                        int idx = (int)vs.size()-1;
                        cost[i][idx] = (vs[i].real() - pt.real()) / VC;
                        break;
                    }
                }
            }
        }

        vector<int> order(vs.size());
        for(int i = 0; i < order.size(); ++i) order[i] = i;
        sort(order.begin(), order.end(), Comp(vs));

        vector<double> best(vs.size(), 1e12);
        best[order[vs.size()-1]] = 0;
        for(int i = (int)vs.size()-1; i >= 1; --i) {
            int cur = order[i];
            int next = order[i-1];
            cost[cur][next] = abs(vs[next]-vs[cur]) / VW;

            for(int j = 0; j < i; ++j) {
                int nx = order[j];
                assert(cost[cur][nx] >= 0);
                best[nx] = min(best[nx], best[cur] + cost[cur][nx]);
            }
            //cout << best[cur] << endl;
        }

        printf("%.7f\n", best[order[0]]);
    }

    return 0;
}
