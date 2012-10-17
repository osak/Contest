//Name: Aizu Buried Treasure
//Level: 4
//Category: グラフ,Graph,ダイクストラ,Dijkstra
//Note:

/*
 * セルを掘っていくときの状態は
 * ・現在位置(x, y)
 * ・酸素残量
 * ・すでに掘ったマス
 * の3つ．ここで移動は左右か下のみに限られ，また左右移動は1マスずつであることに注目すると
 * すでに掘ったマスは特定のyでのみ有効で，かつ区間で表わせることが分かる．
 * これらの状態の最大値は
 * ・現在位置 = 10 * 10 = 100
 * ・酸素残量 = 51 
 * ・すでに掘ったマス = 10C2 = 45
 * であるから，状態数は 20万ちょい．
 * これらを状態としたグラフの上でダイクストラすればよい．
 *
 * unordered_map を使ったら，状態変数がintのときはMLEした．
 * また，入力は初期酸素が0というものもあるので注意．
 *
 * オーダーはダイクストラが O(E log V)．
 * ただし各状態からは5本(定数)程度しか辺がないため E = O(V)．
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <tr1/unordered_map>

using namespace std;
using namespace tr1;

struct State {
    char x, y, oxygen, left, right;

    State(int x, int y, int o, int l, int r) : x(x), y(y), oxygen(o), left(l), right(r) {}

    bool operator ==(const State &other) const {
        return x == other.x
            && y == other.y
            && oxygen == other.oxygen
            && left == other.left
            && right == other.right;
    }
    struct Hasher {
        size_t operator ()(const State &state) const {
            return (int)state.right + (int)state.left*10 + (int)state.oxygen*10*10 + (int)state.y*10*10*51 + (int)state.x*10*10*51*11;
        }
    };
};

struct Tag {
    State state;
    int cost;

    Tag(const State &s, int c) : state(s), cost(c) {}

    bool operator <(const Tag &other) const {
        return cost > other.cost; // reverse order
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    while(true) {
        int W, H;
        cin >> W >> H;
        if(!W && !H) break;
        int F, M, O;
        cin >> F >> M >> O;
        vector<vector<int> > field(H+1, vector<int>(W)); 
        // 最初の行は酸素1のセルで埋まっているとする(番兵)
        for(int x = 0; x < W; ++x) {
            field[0][x] = 1;
        }
        for(int y = 1; y <= H; ++y) {
            for(int x = 0; x < W; ++x) {
                cin >> field[y][x];
            }
        }

        int ans = F+1;
        priority_queue<Tag> q;
        unordered_map<State,int,State::Hasher> memo;
        // 初期状態
        q.push(Tag(State(0, 0, O, 0, 0), 0));
        memo[q.top().state] = q.top().cost;
        while(!q.empty()) {
            const Tag t = q.top();
            q.pop();
            if(memo.count(t.state) && memo[t.state] < t.cost) continue;
            memo[t.state] = t.cost;

            if(t.state.y == H) {
                ans = t.cost;
                break;
            }

            const static int dx[] = {1, -1, 0};
            const static int dy[] = {0, 0, 1};
            for(int pat = 0; pat < 3; ++pat) {
                bool is_down = (pat == 2);
                const int nx = t.state.x + dx[pat];
                const int ny = t.state.y + dy[pat];
                int no = t.state.oxygen - 1;
                int nc = t.cost;
                if(no <= 0) continue; // 酸素がなくなったら即死
                if(nx < 0 || W <= nx || ny >= H+1) continue;
                // まだ掘ってない場所のみイベント発生
                if(is_down || !(t.state.left <= nx && nx <= t.state.right)) {
                    const int cell = field[ny][nx];
                    if(cell > 0) {
                        no = min(no+cell, M);
                    } else {
                        nc -= cell;
                    }
                }
                const int nl = is_down ? nx : min((int)t.state.left, nx);
                const int nr = is_down ? nx : max((int)t.state.right, nx);
                const State next_state(nx, ny, no, nl, nr);
                if(memo.count(next_state) && memo[next_state] <= nc) continue;
                memo[next_state] = nc;
                q.push(Tag(next_state, nc));
            }
        }
        if(ans > F) cout << "NA" << endl;
        else cout << ans << endl;
    }
    return 0;
}
