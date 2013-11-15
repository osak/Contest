//Name: Cats Going Straight II
//Level: 4
//Category: 幾何,Geometry,Union Find
//Note:

/**
 * すべての壁は領域を分割するのに使われているという条件から、
 * それぞれの壁の両側領域のうち、同じものをUnion Findでマージしていく。
 * 同じものであるという判定は、辺ijと時計回りで一番近い辺jkをとると、
 * ijとjkの左半分は同じ領域になるという事実を用いる。
 *
 * 最後に、一番右の頂点から出ている辺を使って、外側領域を特定し、
 * 幅優先探索を行う。
 *
 * オーダーはO(W^2)。
 */
 *
#include <iostream>
#include <complex>
#include <vector>
#include <bitset>
#include <cmath>
#include <algorithm>

#define TIMES(i, n) for(int i = 0; i < (n); ++i)

using namespace std;

typedef complex<double> P;
typedef bitset<300> Spec;
const double EPS = 1e-9;
const double PI = acos(-1);

double normalize(double angle) {
    if(angle < 0) return angle + 2*PI;
    return angle;
}

int cmp(double a, double b) {
    const double diff = a-b;
    if(fabs(diff) < EPS) return 0;
    return diff < 0 ? -1 : 1;
}

double dot(const P &a, const P &b) {
    return a.real()*b.real() + a.imag()*b.imag();
}

double cross(const P &a, const P &b) {
    return a.real()*b.imag() - a.imag()*b.real();
}

int root(int n, vector<int> &roots) {
    if(roots[n] == n) return n;
    return roots[n] = root(roots[n], roots);
}

bool unite(int a, int b, vector<int> &roots) {
    const int ra = root(a, roots);
    const int rb = root(b, roots);
    if(ra == rb) return false;
    roots[ra] = rb;
    return true;
}

bool solve() {
    int C, W;
    cin >> C >> W;
    if(!C && !W) return false;

    vector<P> poles;
    vector<vector<int>> graph(C);
    vector<vector<int>> wall_id(C, vector<int>(C));
    TIMES(_, C) {
        double x, y;
        cin >> x >> y;
        poles.push_back(P(x, y));
    }
    TIMES(i, W) {
        int s, t;
        cin >> s >> t;
        --s; --t;
        graph[s].push_back(t);
        graph[t].push_back(s);
        wall_id[s][t] = i*2;
        wall_id[t][s] = i*2+1;
    }

    vector<int> roots(W*2);
    TIMES(i, W*2) {
        roots[i] = i;
    }
    TIMES(i, C) {
        const P &pi = poles[i];
        for(int j : graph[i]) {
            const P &pj = poles[j];
            const P vec = pj - pi;
            const double len = abs(vec);
            int candidate = -1;
            int sin_sgn = -2;
            double cos_val = 2;
            for(int k : graph[j]) {
                if(k == i) continue;
                const P vec2 = poles[k] - pj;
                const int sgn = cmp(cross(vec, vec2), 0);
                const double cv = dot(vec, vec2) / len / abs(vec2) * sgn;
                if(sgn > sin_sgn
                    || (sgn == sin_sgn && cmp(cv, cos_val) < 0))
                {
                    candidate = k;
                    sin_sgn = sgn;
                    cos_val = cv;
                }
            }
            if(candidate != -1) {
                if(unite(wall_id[i][j], wall_id[j][candidate], roots) && false) {
                    cout << "unitea " << i << " " << j << " " << candidate << endl;
                    TIMES(a, W*2) {
                        cout << root(a, roots) << ' ';
                    }
                    cout << endl;
                }
            }
        }
    }
    // Determine outside region
    const int rightmost = distance(poles.begin(),
            max_element(poles.begin(), poles.end(), [](const P &a, const P &b) {
                return a.real() < b.real();
                }));
    const int rm_next = *min_element(
            graph[rightmost].begin(), 
            graph[rightmost].end(),
            [&poles, rightmost](int a, int b) {
            const double arga = normalize(arg(poles[a] - poles[rightmost]));
            const double argb = normalize(arg(poles[b] - poles[rightmost]));
            return arga < argb;
            });
    const int out_id = root(wall_id[rm_next][rightmost], roots);

    Spec init;
    vector<Spec> areas(W*2);
    TIMES(i, W*2) {
        const int area = root(i, roots);
        areas[area][i/2] = true;
        if(area == out_id) init[i/2] = true;
        //cout << area << ' ';
    }
    /*
    for(const Spec &s : areas) {
        if(s.any()) cout << s << endl;
    }
    */
    //cout << endl;
    Spec cur = init;
    //cout << init << endl;
    int turn = 0;
    vector<bool> used(W*2, false);
    while(true) {
        Spec next = cur;
        bool changed = false;
        TIMES(i, W*2) {
            if(!used[i] && (areas[i] & cur).any()) {
                next |= areas[i];
                used[i] = true;
                changed = true;
            }
        }
        if(!changed) break;
        cur = next;
        ++turn;
    }
    cout << turn << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
