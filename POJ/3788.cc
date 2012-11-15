//Name: Interior Points of Lattice Polygons
//Level: 3
//Category: 幾何,ブレゼンハム
//Note:

/*
 * 与えられる多角形が凸なので，上から左半分と右半分の頂点を列挙しておき
 * y座標を1ずつ下げながら線分上の座標を計算していく．
 * 整数座標を誤差なく計算する方法としてはブレゼンハムのアルゴリズムが有名かつ高速である．
 * ブレゼンハムは工夫しないと y 座標の差が 0 のときに動かないという問題があるが，
 * この問題では2点を結ぶ線分が水平になるのは一番上か一番下しかないため例外処理で弾くことができる．
 *
 * オーダーは O(N)．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <complex>
#include <cassert>

using namespace std;

typedef complex<int> Vector;

struct Tag {
    int dir; // 0 for left, 1 for right
    Vector v;
    Tag() {}
    Tag(int d, const Vector &v) : dir(d), v(v) {}

    bool operator <(const Tag &other) const {
        // Reverse order
        if(v.imag() != other.v.imag()) return v.imag() > other.v.imag();
        if(dir != other.dir) return dir > other.dir;
        if(dir == 0) return v.real() > other.v.real();
        else return v.real() < other.v.real();
    }
};

struct Ans {
    int y;
    int left, right;
    Ans() {}
    Ans(int y, int l, int r) : y(y), left(l), right(r) {}
};

void bresenham_step(int &current, int &rem, const Vector &dv) {
    rem += abs(dv.real());
    const int forward = rem / abs(dv.imag());
    rem %= abs(dv.imag());
    if(dv.real() > 0) current += forward;
    else current -= forward;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int P;
    cin >> P;
    while(P--) {
        int CASE, N;
        cin >> CASE >> N;
        vector<Vector> polygon(N);
        for(int i = 0; i < N; ++i) {
            cin >> polygon[i].real() >> polygon[i].imag();
        }
        int bottom;
        vector<Tag> events;
        vector<Vector> vs[2];
        {
            int i = 0;
            int prev_y = polygon[0].imag() + 1;
            for(; i < N && polygon[i].imag() <= prev_y; ++i) {
                events.push_back(Tag(1, polygon[i]));
                vs[1].push_back(polygon[i]);
                prev_y = polygon[i].imag();
            }
            bottom = vs[1].back().imag();
            vs[0].push_back(vs[1].back());
            for(; i < N; ++i) {
                events.push_back(Tag(0, polygon[i]));
                vs[0].push_back(polygon[i]);
            }
            vs[0].push_back(polygon[0]);
            reverse(vs[0].begin(), vs[0].end());
        }
        sort(events.begin(), events.end());
        vector<Tag>::const_iterator event_iter = events.begin();
        vector<Vector>::const_iterator vs_iter[2];
        vs_iter[0] = vs[0].begin();
        vs_iter[1] = vs[1].begin();
        int current[2], rem[2];
        current[0] = vs_iter[0]->real();
        current[1] = vs_iter[1]->real();
        rem[0] = rem[1] = 0;
        int y = events[0].v.imag();
        vector<Ans> ans;

        ++event_iter; // Initialize is first event
        // Avoid first horizontal line
        while(event_iter != events.end() && event_iter->v.imag() == y) {
            vs_iter[event_iter->dir]++;
            current[event_iter->dir] = event_iter->v.real();
            assert(rem[event_iter->dir] == 0);
            ++event_iter;
        }
        while(event_iter != events.end()) {
            --y;
            if(y == bottom) break;
            int sign[2];
            for(int i = 0; i < 2; ++i) {
                const Vector diff = *(vs_iter[i]+1) - *vs_iter[i];
                sign[i] = diff.real() == 0 ? 0 : diff.real() > 0 ? 1 : -1;
                //cout << y << ' ' << diff << endl;
                bresenham_step(current[i], rem[i], diff);
            }
            int left = current[0];
            if(rem[0] == 0 || sign[0] > 0) ++left;
            int right = current[1];
            if(rem[1] == 0 || sign[1] < 0) --right;
            if(right-left+1 > 0) ans.push_back(Ans(y, left, right));
            while(event_iter != events.end() && y == event_iter->v.imag()) {
                vs_iter[event_iter->dir]++;
                ++event_iter;
            }
        }
        cout << CASE << ' ' << ans.size() << endl;
        for(vector<Ans>::const_iterator it = ans.begin(); it != ans.end(); ++it) {
            cout << it->y << ' ' << it->left << ' ' << it->right << endl;
        }
    }
    return 0;
}
