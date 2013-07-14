//Name: Mirror Cave
//Level: 3
//Category: シミュレーション,幅優先探索,BFS
//Note:

/*
 * [Lの位置][Rの位置]を状態にして幅優先探索する。
 *
 * オーダーは O(WH)。
 */
#include <iostream>
#include <string>
#include <queue>
 
using namespace std;
 
const int dr[] = {0, -1, 0, 1};
const int dc[][4] = {
    {1, 0, -1, 0},
    {-1, 0, 1, 0}
};

inline bool in_range(int a, int x, int b) {
    return a <= x && x < b;
}

int hash(const pair<int,int> &p) {
    return p.first*50 + p.second;
}

pair<int,int> unhash(int n) {
    return make_pair(n/50, n%50);
}

struct Tag {
    pair<int,int> pos[2];

    Tag() {}
    Tag(pair<int,int> *pa) {
        pos[0] = pa[0];
        pos[1] = pa[1];
    }

    void get(pair<int,int> *pa) const {
        pa[0] = pos[0];
        pa[1] = pos[1];
    }
};

bool solve() {
    int W, H;
    cin >> W >> H;
    if(!W && !H) return false;

    vector<string> field[2];
    pair<int,int> starts[2];
    for(int r = 0; r < H; ++r) {
        string a, b;
        cin >> a >> b;
        field[0].push_back(a);
        field[1].push_back(b);
    }
    for(int i = 0; i < 2; ++i) {
        for(int r = 0; r < H; ++r) {
            for(int c = 0; c < W; ++c) {
                if(field[i][r][c] == "LR"[i]) {
                    starts[i] = make_pair(r, c);
                    field[i][r][c] = '.';
                }
            }
        }
    }

    queue<Tag> q;
    vector<vector<unsigned char> > memo(2500, vector<unsigned char>(2500, 0));
    memo[hash(starts[0])][hash(starts[1])] = 1;
    q.push(starts);
    bool ans = false;
    while(!q.empty()) {
        const Tag t = q.front();
        //cout << t.pos[0].first << ' ' << t.pos[0].second << ' ';
        //cout << t.pos[1].first << ' ' << t.pos[1].second << endl;
        q.pop();

        for(int dir = 0; dir < 4; ++dir) {
            pair<int,int> np[2];
            t.get(np);
            int goalcnt = 0;
            for(int i = 0; i < 2; ++i) {
                int nr = np[i].first + dr[dir];
                int nc = np[i].second + dc[i][dir];
                if(in_range(0, nr, H) && in_range(0, nc, W)) {
                    switch(field[i][nr][nc]) {
                        case '#':
                            nr = np[i].first;
                            nc = np[i].second;
                            break;
                        case '%':
                            goalcnt++;
                            break;
                    }
                } else {
                    nr = np[i].first;
                    nc = np[i].second;
                }
                np[i] = make_pair(nr, nc);
            }
            if(goalcnt == 2) {
                ans = true;
                goto end;
            } else if(goalcnt == 0) {
                const int h1 = hash(np[0]);
                const int h2 = hash(np[1]);
                if(!memo[h1][h2]) {
                    memo[h1][h2] = 1;
                    q.push(Tag(np));
                }
            }
        }
    }
end:
    cout << (ans ? "Yes" : "No") << endl;
    return true;
}
 
int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
     
    for(; solve(); ) ;
    return 0;
}
