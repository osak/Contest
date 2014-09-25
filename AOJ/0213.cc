//Name: Subdivide The Land
//Level: 3
//Category: 探索
//Note:

/**
 * パズル「四角に切れ」と同じ問題設定なので、おそらくNP完全である。
 * したがって、効率のよい探索を考える。
 *
 * 全てのマスがどれかの長方形に属していることより、盤面を左上から走査していき、どの番号の長方形に属すかを探索していけばよい。
 * こうすることで、そのマスを左上とした長方形に決め打つことができる。
 * 各番号では、その面積を与える長方形を全て試す。
 */
#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <array>

using namespace std;

typedef bitset<15> State;

struct Rect {
    int r, c, h, w;

    //Rect() : r(0), c(0), h(0), w(0) {}
    Rect() {}
    Rect(int r, int c, int h, int w) : r(r), c(c), h(h), w(w) {}

    bool intersect(const Rect &other) const {
        return (r < other.r+other.h) && (other.r < r+h) && (c < other.c+other.w) && (other.c < c+w);
    }
};

array<array<int,16>,16> field;
vector<Rect> ans;
vector<int> area_of;
int N, W, H;

void dfs(int r, int c, State &state, vector<Rect> &cur) {
    //cout << r << ' ' << c << endl;
    if(r == H) {
        if(ans.size() != 0) throw "Multiple answer";
        ans = cur;
    } else if(c == W) {
        dfs(r+1, 0, state, cur);
    } else {
        bool conquered = false;
        for(int i = 0; i < N; ++i) {
            //if(!state[i]) continue;
            if(cur[i].intersect(Rect(r, c, 1, 1))) {
                conquered = true;
                break;
            }
        }
        if(conquered) {
            dfs(r, c+1, state, cur);
            return;
        }
        for(int b = 0; b < N; ++b) {
            if(state[b]) continue;
            const int area = area_of[b];
            for(int w = 1; w <= area; ++w) {
                if(area % w != 0) continue;
                const int h = area / w;
                const Rect cand(r, c, h, w);
                bool has_b = false;
                // Check: it is in field
                if(r+h > H || c+w > W) goto next;
                // Check: it contains tag b and it is only tag
                for(int dr = 0; dr < h; ++dr) {
                    for(int dc = 0; dc < w; ++dc) {
                        if(field[r+dr][c+dc] != 0 && field[r+dr][c+dc] != b+1) goto next;
                        if(field[r+dr][c+dc] == b+1) has_b = true;
                    }
                }
                if(!has_b) goto next;
                // Check: it doesn't intersect with other rects
                for(int i = 0; i < N; ++i) {
                    if(!state[i]) continue;
                    if(cand.intersect(cur[i])) goto next;
                }
                cur[b] = cand;
                state[b] = true;
                dfs(r, c+1, state, cur);
                state[b] = false;
next:
                ;
            }
        }
    }
}

bool solve() {
    cin >> W >> H >> N;
    if(!W && !H && !N) return false;
    area_of.clear();
    area_of.resize(N, 0);
    int area_sum = 0;
    for(int i = 0; i < N; ++i) {
        int b, k;
        cin >> b >> k;
        area_of[b-1] = k;
        area_sum += k;
    }
    for(int r = 0; r < H; ++r) {
        for(int c = 0; c < W; ++c) {
            cin >> field[r][c];
        }
    }
    try {
        if(area_sum != W*H) {
            throw "Inconsistent input";
        }
        State state;
        vector<Rect> cur(N);
        ans.clear();
        dfs(0, 0, state, cur);
        if(ans.size() == 0) {
            throw "No solution";
        }
        for(int i = 0; i < N; ++i) {
            for(int dr = 0; dr < ans[i].h; ++dr) {
                for(int dc = 0; dc < ans[i].w; ++dc) {
                    field[ans[i].r+dr][ans[i].c+dc] = i+1;
                }
            }
        }
        for(int r = 0; r < H; ++r) {
            for(int c = 0; c < W; ++c) {
                if(c != 0) cout << " ";
                cout << field[r][c];
            }
            cout << endl;
        }
    } catch(const char *msg) {
        //cout << msg << endl;
        cout << "NA" << endl;
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
