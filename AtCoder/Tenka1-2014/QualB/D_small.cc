#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <cassert>
#include <numeric>

using namespace std;

struct Rect {
    int t, l, b, r;
    Rect() : t(300), l(300), b(-100), r(-100) {}
};

struct Tag {
    int n, p1, p2;

    bool operator ==(const Tag &other) const {
        return n == other.n && p1 == other.p1 && p2 == other.p2;
    }
};

struct H {
    size_t operator ()(const Tag &t) const {
        return t.n + t.p1 * 20 + t.p2 * 20 * (1<<20);
    }
};

bool solve() {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;
    if(N > 9) return false;

    vector<int> as(N);
    for(int i = 0; i < N; ++i) {
        cin >> as[i];
    }
    sort(as.begin(), as.end(), greater<int>());

    int H, W;
    cin >> H >> W;
    vector<vector<vector<int>>> acc(N, vector<vector<int>>(H, vector<int>(W, 0)));
    vector<Rect> rs(N);
    set<int> colors;
    for(int r = 0; r < H; ++r) {
        for(int c = 0; c < W; ++c) {
            int f;
            cin >> f;
            acc[f][r][c] = 1;
            rs[f].t = min(rs[f].t, r);
            rs[f].b = max(rs[f].b, r);
            rs[f].l = min(rs[f].l, c);
            rs[f].r = max(rs[f].r, c);
            colors.insert(f);
        }
    }
    for(int i = 0; i < N; ++i) {
        for(int r = 0; r < H; ++r) {
            for(int c = 0; c < W; ++c) {
                if(r > 0) acc[i][r][c] += acc[i][r-1][c];
                if(c > 0) acc[i][r][c] += acc[i][r][c-1];
                if(r > 0 && c > 0) acc[i][r][c] -= acc[i][r-1][c-1];
            }
        }
    }

    vector<Rect> rs2;
    for(Rect &r : rs) {
        if(r.b >= 0) {
            rs2.push_back(r);
            //cout << r.t << ' ' << r.l << ' ' << r.b << ' ' << r.r << endl;
        }
    }

    vector<int> pat(N);
    iota(pat.begin(), pat.end(), 0);
    do {
        int used = 0;
        int cache = 0;
        int cur = 0;
        for(int i : pat) {
            if(cur > 0 && as[cur] != as[cur-1]) {
                used |= cache;
                cache = 0;
            }
            ++cur;
            if(rs[i].b < 0) continue;
            const Rect &r = rs[i];
            for(int j = 0; j < N; ++j) {
                if((used & (1<<j))) continue;
                if(i == j) continue;
                int cnt = acc[j][r.b][r.r];
                if(r.l > 0) cnt -= acc[j][r.b][r.l-1];
                if(r.t > 0) cnt -= acc[j][r.t-1][r.r];
                if(r.l > 0 && r.t > 0) cnt += acc[j][r.t-1][r.l-1];
                if(cnt != 0) goto fail;
            }
            cache |= 1<<i;
        }
        /*
        for(int i : pat) {
            cout << i << endl;
        }
        */
        cout << 1 << endl;
        return true;
fail:
        ;
    } while(next_permutation(pat.begin(), pat.end()));
    cout << 0 << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}

