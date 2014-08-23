#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <cassert>

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

//bool memo[20][1<<20][1<<20];
unordered_set<Tag,H> memo;
int N, color_cnt;
bool dfs(int p, int used, int cache, const vector<int> &as, const vector<Rect> &rs, const vector<vector<vector<int>>> &acc) {
    //cout << used << ' ' << cache << endl;
    assert((used & cache) == 0);
    if(__builtin_popcount(used | cache) == color_cnt) return true;
    if(p == N) return false;
    const Tag t = {p, used, cache};
    if(memo.count(t)) return false;

    const int C = rs.size();
    for(int i = 0; i < C; ++i) { // assign p-th thick color to number i
        if(used & (1<<i)) continue; // continue if it is used
        if(cache & (1<<i)) continue;
        const Rect &r = rs[i];
        for(int j = 0; j < C; ++j) {
            // if not yet painted area is in rect, it cannot be get painted
            if(i == j) continue; // not needed to check itself
            if(!(used & (1<<j))) { 
                int cnt = acc[j][r.b][r.r];
                if(r.l > 0) cnt -= acc[j][r.b][r.l-1];
                if(r.t > 0) cnt -= acc[j][r.t-1][r.r];
                if(r.l > 0 && r.t > 0) cnt += acc[j][r.t-1][r.l-1];
                if(cnt != 0) goto fail;
            }
        }
        {
            //cout << "p: " << p << ' ' << i << endl;
            int nused = used;
            int ncache = cache | (1<<i);
            if(p+1 < N && as[p+1] != as[p]) {
                nused |= ncache;
                ncache = 0;
            }

            if(dfs(p+1, nused, ncache, as, rs, acc)) return true;
        }
fail:
        ;
    }
    {
        int nused = used;
        int ncache = cache;
        if(p+1 < N && as[p+1] != as[p]) {
            nused |= ncache;
            ncache = 0;
        }
        if(dfs(p+1, nused, ncache, as, rs, acc)) return true;
    }
    memo.insert(t);
    return false;
}

bool solve() {
    if(!(cin >> N)) return false;
    if(!N) return false;

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
    color_cnt = colors.size();
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
    memo.clear();
    if(dfs(0, 0, 0, as, rs2, acc)) {
        cout << 1 << endl;
    } else {
        cout << 0 << endl;
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}

