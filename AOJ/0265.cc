//Name: Cats Going Straight
//Level: 4
//Category: 幾何,Geometry
//Note:

/**
 * すべての辺を見ることができるような頂点の組を求める。
 * ある頂点iから辺を見ていったとき、見えるか見えないかが変わる点は
 * 視線が他の頂点jを通る瞬間である。
 * したがって、このような半直線をすべて列挙し、これと多角形の辺の交点を
 * 追加した新しい多角形に対し、すべての辺が見えるかを確かめる。
 *
 * オーダーはO(N^4)。
 */
#include <iostream>
#include <complex>
#include <vector>
#include <algorithm>

using namespace std;

const double EPS = 1e-4;

typedef complex<double> P;

inline double dot(const P &a, const P &b) {
    return a.real()*b.real() + a.imag()*b.imag();
}

inline double cross(const P &a, const P &b) {
    return a.real()*b.imag() - a.imag()*b.real();
}

inline int cmp(double a, double b) {
    const double diff = a-b;
    if(fabs(diff) < EPS) return 0;
    return diff < 0 ? -1 : 1;
}

bool intersectSS(const P &pa, const P &pb, const P &qa, const P &qb) {
    if(cmp(cross(pb-pa, qa-pa) * cross(pb-pa, qb-pa), 0) >= 0) return false;
    if(cmp(cross(qb-qa, pa-qa) * cross(qb-qa, pb-qa), 0) >= 0) return false;
    return true;
}

bool intersectLS(const P &pa, const P &pb, const P &qa, const P &qb) {
    return cmp(cross(pb-pa, qa-pa) * cross(pb-pa, qb-pa), 0) < 0;
}

P intersection(const P &pa, const P &pb, const P &qa, const P &qb) {
    const double A = cross(pb-pa, qb-qa);
    const double B = cross(pb-pa, pb-qa);
    if(cmp(A, 0) == 0 && cmp(B, 0) == 0) return qa;
    return qa + B/A*(qb-qa);
}

bool in_polygon(const P &p, const vector<P> &polygon) {
    const int N = polygon.size();
    int cnt = 0;
    for(int i = 0; i < N; ++i) {
        const int ni = (i+1) % N;
        P va = polygon[i] - p;
        P vb = polygon[ni] - p;
        if(va.imag() > vb.imag()) swap(va, vb);
        if(cmp(va.imag(), 0) <= 0 && cmp(0, vb.imag()) < 0) {
            if(cmp(cross(va, vb), 0) < 0) ++cnt;
        }
        if(cmp(cross(va, vb), 0) == 0 && cmp(dot(va, vb), 0) <= 0) return true;
    }
    return cnt % 2 == 1;
}

bool can_see(const P &pa, const P &pb, const vector<P> &polygon) {
    const int N = polygon.size();
    if(abs(pa-pb) < EPS) return true;
    vector<P> ps;
    for(int i = 0; i < N; ++i) {
        const int ni = (i+1) % N;
        if(abs(polygon[i]-pb) < EPS) continue;
        //if(abs(polygon[ni]-pb) < EPS) continue;
        if(intersectSS(pa, pb, polygon[i], polygon[ni])) return false;
        if(cmp(cross(pb-pa, polygon[i]-pa), 0) == 0 && cmp(dot(pa-polygon[i], pb-polygon[i]), 0) <= 0)
        {
            ps.push_back(polygon[i]);
        }
    }
    ps.push_back(pa);
    ps.push_back(pb);
    sort(ps.begin(), ps.end(), [pa](const P &p1, const P &p2) {
            return norm(pa-p1) < norm(pa-p2);
            });
    for(int i = 0; i+1 < ps.size(); ++i) {
        if(!in_polygon((ps[i]+ps[i+1])*0.5, polygon)) return false;
    }
    return true;
}

bool solve() {
    int N;
    cin >> N;
    if(!N) return false;

    vector<P> polygon(N);
    for(int i = 0; i < N; ++i) {
        double x, y;
        cin >> x >> y;
        polygon[i] = P(x, y);
    }
    vector<P> new_polygon;
    for(int i = 0; i < N; ++i) {
        const P pa = polygon[i];
        const P pb = polygon[(i+1)%N];
        new_polygon.push_back(pa);
        vector<P> buf;
        for(int j = 0; j < N; ++j) {
            const P pj = polygon[j];
            for(int k = 0; k < j; ++k) {
                const P pk = polygon[k];
                if(!intersectLS(pj, pk, pa, pb)) continue;
                const P ip = intersection(pj, pk, pa, pb);
                buf.push_back(ip);
            }
        }
        sort(buf.begin(), buf.end(), [pa](const P &a, const P &b) {
                return norm(pa-a) < norm(pa-b);
                });
        new_polygon.insert(new_polygon.end(), buf.begin(), buf.end());
    }
    const int M = new_polygon.size();
    vector<vector<bool>> visible_mask(N, vector<bool>(M, false));
    for(int j = 0; j < N; ++j) {
        const P p = polygon[j];
        for(int i = 0; i < M; ++i) {
            const int ni = (i+1) % M;
            if(can_see(p, new_polygon[i], polygon)
                && can_see(p, new_polygon[ni], polygon))
            {
                visible_mask[j][i] = true;
            }
        }
    }
    int ans = N;
    for(int pat = 0; pat < (1<<N); ++pat) {
        int popcnt = 0;
        vector<bool> mask(M, false);
        for(int i = 0; i < N; ++i) {
            if(pat & (1<<i)) {
                ++popcnt;
                for(int j = 0; j < M; ++j) {
                    mask[j] = mask[j] | visible_mask[i][j];
                }
            }
        }
        if(all_of(mask.begin(), mask.end(), [](bool b){return b;})) {
            ans = min(ans, popcnt);
        }
    }
    cout << ans << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
