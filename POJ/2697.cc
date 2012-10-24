//Name: A Board Game
//Level: 3
//Category: 探索
//Note: データセット弱い

/*
 * マス目は16マス，石の数は白黒4つで固定なので
 * ・各マスのどこに石が置かれているか
 * ・石が置かれているマスを左上から順に見ていったとき，色はどういう配置か
 * を考えると，16C8 * 8C4 = 900900 状態で全ての盤面を記述できる．
 * これらをメモして幅優先探索すればよい．
 *
 * 状態数は上の通りで，各状態からの遷移を考えるのに全てのマスをなめ，さらに8方向の移動を考えると
 * ループ回数は 900900*16*8 = 約10億 となって危ない気がするが普通に通る．
 *
 * 以下のコードではA*で探索しているが，到達不可能な状態も判定しないといけないので
 * あまり意味はない(後で気づいた)．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

enum Chip{ NONE, WHITE, BLACK };
int field[4][4];
int goal_field[4][4];
int hash() {
    int field_hash = 0, color_hash = 0;
    int color_idx = 0;
    for(int y = 0; y < 4; ++y) {
        for(int x = 0; x < 4; ++x) {
            if(field[y][x] != NONE) {
                field_hash |= (1<<(y*4+x));
                if(field[y][x] == BLACK) color_hash |= (1<<color_idx);
                color_idx++;
            }
        }
    }
    return (field_hash<<8) | color_hash;
}

void dehash(int n) {
    int field_hash = n>>8, color_hash = n & 0xff;
    int color_idx = 0;
    for(int y = 0; y < 4; ++y) {
        for(int x = 0; x < 4; ++x) {
            if(field_hash & (1<<(y*4+x))) {
                if(color_hash & (1<<color_idx)) field[y][x] = BLACK;
                else field[y][x] = WHITE;
                ++color_idx;
            } else {
                field[y][x] = NONE;
            }
        }
    }
}

int heuristic() {
    int correct = 0;
    for(int y = 0; y < 4; ++y) {
        for(int x = 0; x < 4; ++x) {
            if(goal_field[y][x] != NONE && field[y][x] == goal_field[y][x]) ++correct;
        }
    }
    return 8-correct;
}

void print_field() {
    for(int y = 0; y < 4; ++y) {
        for(int x = 0; x < 4; ++x) {
            cout << "*wb"[field[y][x]];
        }
        cout << endl;
    }
    cout << endl;
}

struct Tag {
    int hash_val, cost, h;
    Tag(int hv, int c, int h) : hash_val(hv), cost(c), h(h) {}
    
    bool operator <(const Tag &other) const {
        return cost+h > other.cost+other.h; // Reverse order
    }
};

void make_field(const vector<string> &v) {
    for(int y = 0; y < 4; ++y) {
        for(int x = 0; x < 4; ++x) {
            switch(v[y][x]) {
                case '*':
                    field[y][x] = NONE;
                    break;
                case 'w':
                    field[y][x] = WHITE;
                    break;
                case 'b':
                    field[y][x] = BLACK;
                    break;
            }
        }
    }
}

pair<int,int> try_slide(const int y, const int x, int dir) {
    const static int dx[] = {1, 1, 0, -1, -1, -1, 0, 1};
    const static int dy[] = {0, -1, -1, -1, 0, 1, 1, 1};
    int y_ = y, x_ = x;
    while(true) {
        int ny = y_ + dy[dir];
        int nx = x_ + dx[dir];
        if(ny < 0 || 4 <= ny || nx < 0 || 4 <= nx) break;
        if(field[ny][nx] != NONE) break;
        y_ = ny; x_ = nx;
    }
    if(y_ != y || x_ != x) {
        field[y_][x_] = field[y][x];
        field[y][x] = NONE;
    }
    return make_pair(y_, x_);
}

void undo(int y, int x, const pair<int,int> &to) {
    if(y != to.first || x != to.second) {
        field[y][x] = field[to.first][to.second];
        field[to.first][to.second] = NONE;
    }
}

//const unsigned char INF = 256;
//unsigned char memo[2][1<<24];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int M;
    cin >> M;
    while(M--) {
        vector<string> init(4), goal(4);
        for(int i = 0; i < 4; ++i) {
            cin >> init[i];
        }
        for(int i = 0; i < 4; ++i) {
            cin >> goal[i];
        }
        make_field(init);
        const int start_hash = hash();
        const int hval = heuristic();
        make_field(goal);
        const int goal_hash = hash();
        for(int y = 0; y < 4; ++y) {
            for(int x = 0; x < 4; ++x) {
                goal_field[y][x] = field[y][x];
            }
        }
        map<int, int> memo;
        //fill_n((short*)memo, sizeof(memo)/sizeof(short), INF);

        priority_queue<Tag> q;
        q.push(Tag(start_hash, 0, hval));
        int ans = 1;
        while(!q.empty()) {
            Tag t = q.top();
            q.pop();

            const int parity = t.cost&1;
            const Chip color = parity ? BLACK : WHITE;
            const int key = (t.hash_val<<1) | parity;
            if(memo.count(key) && t.cost > memo[key]) continue;
            memo[key] = t.cost;
            if(t.hash_val == goal_hash) {
                ans = t.cost;
                break;
            }

            dehash(t.hash_val);
            //cout << t.cost << endl;
            //print_field();
            for(int y = 0; y < 4; ++y) {
                for(int x = 0; x < 4; ++x) {
                    if(field[y][x] == color) {
                        for(int dir = 0; dir < 8; ++dir) {
                            pair<int,int> pos = try_slide(y, x, dir);
                            int nh = hash();
                            int np = parity^1;
                            int nk = (nh<<1) | np;
                            if(memo.count(nk) == 0 || memo[nk] > t.cost+1) {
                                memo[nk] = t.cost+1;
                                q.push(Tag(nh, t.cost+1, heuristic()));
                            }
                            undo(y, x, pos);
                        }
                    }
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
