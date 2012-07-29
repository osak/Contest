#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cassert>

using namespace std;

typedef complex<int> Vector;

//Verified PKU 2812
double cross(const Vector &v1, const Vector &v2) {
    return (v1.real()*v2.imag()) - (v1.imag()*v2.real());
}
double dot(const Vector &v1, const Vector &v2) {
    return v1.real()*v2.real() + v1.imag()*v2.imag();
}

//Verified AOJ 0012
//Verified PKU 3348
int ccw(const Vector &p1, const Vector &p2, const Vector &p3) {
    const Vector &v1 = p2-p1;
    const Vector &v2 = p3-p1;
    double op = cross(v1, v2);
    if(op > 0) return 1; //ccw
    if(op < 0) return -1; //cw
    if(dot(v1, v2) < 0) return 2; //p3-p1-p2
    if(norm(v1) < norm(v2)) return -2; //p1-p2-p3
    return 0;
}

bool on(const Vector &p11, const Vector &p12, const Vector &p) {
    return ccw(p11, p, p12) == -2;
}

bool intersect(const Vector &p11, const Vector &p12, const Vector &p21, const Vector &p22) {
    int c1 = ccw(p11, p12, p21);
    int c2 = ccw(p11, p12, p22);
    int c3 = ccw(p21, p22, p11);
    int c4 = ccw(p21, p22, p12);
    return (c1*c2 <= 0 && c3*c4 <= 0) || (on(p11, p12, p21) || on(p11, p12, p22) || on(p21, p22, p11) || on(p21, p22, p12));
}


bool cmp(const Vector &p1, const Vector &p2) {
    return p1.real() < p2.real();
}

vector<Vector> convex_hull(const vector<Vector> &points) {
    int N = points.size();
    vector<Vector> v = points;
    sort(v.begin(), v.end(), cmp);
    vector<Vector> hull(2*N);
    int pos = 0;
    for(int i = 0; i < N; ++i) {
        while(pos >= 2 && ccw(hull[pos-2], hull[pos-1], v[i]) <= 0) --pos;
        hull[pos++] = v[i];
    }
    int lim = pos;
    for(int i = N-2; i >= 0; --i) {
        while(pos >= lim+1 && ccw(hull[pos-2], hull[pos-1], v[i]) <= 0) --pos;
        hull[pos++] = v[i];
    }
    hull.erase(hull.begin()+pos, hull.end());
    return hull;
}

int main() {
    assert(on(Vector(100, 100), Vector(500, 500), Vector(300, 300)));
    ios::sync_with_stdio(0);
    while(true) {
        int N, M;
        cin >> N >> M;
        if(!N && !M) break;

        vector<Vector> bs, ws;
        for(int i = 0; i < N; ++i) {
            double x, y;
            cin >> x >> y;
            bs.push_back(Vector(x, y));
        }
        for(int i = 0; i < M; ++i) {
            double x, y;
            cin >> x >> y;
            ws.push_back(Vector(x, y));
        }

        vector<Vector> bs_convex = convex_hull(bs);
        vector<Vector> ws_convex = convex_hull(ws);

        //check intersection
        for(int i = 0; i < bs_convex.size(); ++i) {
            const Vector &p1 = bs_convex[i];
            const Vector &p2 = i+1==bs_convex.size() ? bs_convex[0] : bs_convex[i+1];
            for(int j = 0; j < ws_convex.size(); ++j) {
                const Vector &p3 = ws_convex[i];
                const Vector &p4 = j+1==ws_convex.size() ? ws_convex[0] : ws_convex[j+1];
                if(intersect(p1, p2, p3, p4)) {
                    goto fail;
                }
            }
        }

        //check inclusion
        {
            if(bs_convex.size() >= 4) {
                bool ok = false;
                int dir = 0;
                for(int i = 0; i+1 < bs_convex.size(); ++i) {
                    const Vector &p1 = bs_convex[i];
                    const Vector &p2 = i+1==bs_convex.size() ? bs_convex[0] : bs_convex[i+1];
                    int tmp = ccw(p1, p2, ws_convex[0]);
                    if(tmp == 2 || tmp == 0 || dir*tmp < 0) {
                        ok = true;
                        break;
                    }
                    dir = tmp;
                }
                if(!ok) goto fail;
            }

            if(ws_convex.size() >= 4) {
                bool ok = false;
                int dir = 0;
                for(int i = 0; i+1 < ws_convex.size(); ++i) {
                    const Vector &p1 = ws_convex[i];
                    const Vector &p2 = i+1==ws_convex.size() ? ws_convex[0] : ws_convex[i+1];
                    int tmp = ccw(p1, p2, bs_convex[0]);
                    if(tmp == 2 || tmp == 0 || dir*tmp < 0) {
                        goto succ;
                    }
                    dir = tmp;
                }
                if(!ok) goto fail;
            }
        }
        
succ:
        cout << "YES" << endl;
        continue;
fail:
        cout << "NO" << endl;
    }

    return 0;
}
