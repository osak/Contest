//Name: Let There Be Light
//Level: 3
//Category: 幾何,Geometry
//Note:

/**
 * ある光源から目標点を見たとき、届かせるためには途中にある風船を
 * すべて取り除く必要がある。
 * したがって、逆に考えて、届かせたい光源の組み合わせに対して、それを
 * 実現するような風船の取り除き方をしたとき、その個数がR以下になるかどうかを
 * 確かめればよい。
 *
 * オーダーはO(2^M NR)。
 * 以下のコードではbitsetを使うことで高速化している。
 */
#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <bitset>

using namespace std;

const double EPS = 1e-9;

struct P3 {
    double x, y, z;
    P3() {}
    P3(double x, double y, double z) : x(x), y(y), z(z) {}
};

P3 operator +(const P3 &a, const P3 &b) {
    return P3(a.x+b.x, a.y+b.y, a.z+b.z);
}

P3 operator -(const P3 &a, const P3 &b) {
    return P3(a.x-b.x, a.y-b.y, a.z-b.z);
}

double dot(const P3 &p, const P3 &q) {
    return p.x*q.x + p.y*q.y + p.z*q.z;
}

P3 cross(const P3 &a, const P3 &b) {
    return P3(a.y*b.z - b.y*a.z, a.z*b.x - b.z*a.x, a.x*b.y - b.x*a.y);
}

double abs(const P3 &p) {
    return sqrt(dot(p, p));
}

istream& operator >>(istream &is, P3 &p) {
    return is >> p.x >> p.y >> p.z;
}

// line(a, b) and c
double dist(const P3 &a, const P3 &b, const P3 &c) {
    if(dot(c-a, b-a) <= 0) return abs(c-a);
    if(dot(c-b, a-b) <= 0) return abs(c-b);
    return abs(cross(c-a, b-a)) / abs(b-a);
}

struct Sphere {
    P3 center;
    double r;
};

bool intersect(const P3 &a, const P3 &b, const Sphere &s) {
    const double d_ca = abs(s.center-a);
    const double d_cb = abs(s.center-b);
    if(d_ca < s.r+EPS && d_cb < s.r+EPS) return false;
    return dist(a, b, s.center) < s.r + EPS;
}

bool solve() {
    int N, M, R;
    cin >> N >> M >> R;
    if(!N && !M && !R) return false;

    vector<Sphere> balloons(N);
    vector<P3> lights(M);
    vector<double> brightness(M);
    for(int i = 0; i < N; ++i) {
        cin >> balloons[i].center >> balloons[i].r;
    }
    for(int i = 0; i < M; ++i) {
        cin >> lights[i] >> brightness[i];
    }
    P3 target;
    cin >> target;

    vector<bitset<2000>> dependency(M);
    for(int i = 0; i < M; ++i) { // lights[i]
        for(int j = 0; j < N; ++j) { // balloons[j]
            if(intersect(lights[i], target, balloons[j])) {
                dependency[i][j] = true;
            }
        }
    }
    double ans = 0;
    for(int pat = 0; pat < (1<<M); ++pat) {
        bitset<2000> to_remove;
        for(int i = 0; i < M; ++i) {
            if(pat & (1<<i)) {
                to_remove |= dependency[i];
            }
        }
        if(to_remove.count() > R) continue;

        double res = 0;
        for(int i = 0; i < M; ++i) { // lights[i]
            if((to_remove & dependency[i]) == dependency[i]) {
                //cout << pat << " " << i << endl;
                const P3 d = lights[i] - target;
                res += brightness[i] / dot(d, d);
            }
        }
        ans = max(ans, res);
    }
    printf("%.6f\n", ans);
    return true;
}

int main() {
    cin.tie(0);
    //ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
