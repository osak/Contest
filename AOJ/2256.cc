//Name: Divide the Cake
//Level: 4
//Category: 幾何,Geometry,確率
//Note:

/**
 * 左側の辺に1点を取ったとき、右側の点が動ける範囲は、いちごを半分に分けられる境界線の間の範囲。
 * この境界線が変化するのは、いちごと右側の角のうち2点を通る直線と、左側の辺との交点をまたぐときだけである。
 * また、この区間内で左側の点がεだけ動いた時、右側の点の動ける範囲の変化分は相似な三角形を用いて
 *   ε(W-x1)/x1 - ε(W-x2)/x2
 * と表せる。
 * ただし、x1とx2は境界上のいちごのx座標。
 *
 * 左側の点に対応する境界上のいちごは、偏角でソートして中央にあるものを選べばよい。
 *
 * オーダーはO(N^3 log N)。
 */
#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>
#include <cstdio>

using namespace std;

typedef complex<long double> P;

const long double EPS = 1e-10;

namespace std {
    bool operator <(const P &p1, const P &p2) {
        if(p1.real() != p2.real()) return p1.real() < p2.real();
        return p1.imag() < p2.imag();
    }
};

bool cmp(const P &p1, const P &p2) {
    return p1.imag() < p2.imag();
}

bool eql(const P &p1, const P &p2) {
    return abs(p1 - p2) < EPS;
}

long double calc_at(const P &pa, const P &pb, long double x) {
    P d = pb - pa;
    if(abs(d.real()) < EPS) {
        if(arg(d) < 0) return -1e10;
        else return 1e10;
    }
    return pa.imag() + d.imag() * ((x - pa.real()) / d.real());
}

long double cross(const P &pa, const P &pb) {
    return pa.real()*pb.imag() - pa.imag()*pb.real();
}

bool solve() {
    int W, H, N;
    cin >> W >> H >> N;
    if(!W && !H && !N) return false;
    N *= 2;

    vector<P> ps(N);
    for(int i = 0; i < N; ++i) {
        int x, y;
        cin >> x >> y;
        ps[i] = P(x, y);
    }
    vector<P> events;
    for(int i = 0; i < N; ++i) {
        for(int j = i+1; j < N; ++j) {
            events.push_back(P(0, calc_at(ps[i], ps[j], 0)));
        }
        events.push_back(P(0, calc_at(ps[i], P(W, 0), 0)));
        events.push_back(P(0, calc_at(ps[i], P(W, H), 0)));
    }
    events.push_back(P(0, 0));
    events.push_back(P(0, H));
    sort(events.begin(), events.end(), cmp);
    //events.erase(unique(events.begin(), events.end(), eql), events.end());
    const int M = events.size();
    long double ans = 0;
    for(int i = 0; i < M-1; ++i) {
        const P &pa = events[i];
        const P &pb = events[i+1];
        if(pa.imag() < 0) continue;
        if(pb.imag() > H) break;
        if(pb.imag() - pa.imag() < EPS) continue;
        //cout << pa << ' ' << pb << endl;
        const P m = (pa+pb) / (long double)2.0;
        long double upper = 0, lower = 0;
        vector<pair<long double,P>> v;
        for(const P &p : ps) {
            const P d = p - m;
            v.push_back(make_pair(arg(d), p));
        }
        sort(v.begin(), v.end());
        //cout << v[0].first << ' ' << v[1].first << endl;
        lower = min<long double>(H, max<long double>(0, calc_at(m, v[N/2-1].second, W)));
        upper = min<long double>(H, max<long double>(0, calc_at(m, v[N/2].second, W)));
        //cout << lower << ' ' << upper << endl;
        long double add = (pb.imag()-pa.imag()) * (upper - lower);
        ans += abs(add);
    }
    printf("%.10Lf\n", ans / H / H);
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
