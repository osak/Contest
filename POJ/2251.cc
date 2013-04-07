//Name: Dungeon Master
//Level: 2
//Category: グラフ,Graph,幅優先探索,BFS
//Note:

/*
 * 幅優先探索するだけ．
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define FOREACH(it,c) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)
#define TIMES(__i,__n) for(int __i = 0; __i < __n; ++__i)

struct State {
    int l, r, c;

    State() {}
    State(int l, int r, int c) : l(l), r(r), c(c) {}
};

struct Cell {
    char c;
    bool visited;

    Cell() {}
    Cell(char c) : c(c), visited(false) {}
};

typedef vector<Cell> FloorRow;
typedef vector<FloorRow> Floor;
typedef vector<Floor> Dungeon;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    while(true) {
        int L, R, C;
        cin >> L >> R >> C;
        if(!L && !R && !C) break;

        State start, end;
        Dungeon dungeon(L);
        TIMES(l, L) {
            Floor &f = dungeon[l];
            f.resize(R);
            TIMES(r, R) {
                string str;
                cin >> str;
                TIMES(c, C) {
                    if(str[c] == 'S') {
                        start = State(l, r, c);
                    } else if(str[c] == 'E') {
                        end = State(l, r, c);
                    }
                    f[r].push_back(Cell(str[c]));
                }
            }
        }

        int ans = -1;
        vector<State> q;
        q.push_back(start);
        dungeon[start.l][start.r][start.c].visited = true;
        for(int turn = 0; ; ++turn) {
            if(q.size() == 0) break;
            vector<State> nextq;
            FOREACH(it, q) {
                const State cur(*it);
                const int DL[] = {0, 0, 0, 0, -1, 1};
                const int DR[] = {-1, 1, 0, 0, 0, 0};
                const int DC[] = {0, 0, 1, -1, 0, 0};
                if(dungeon[cur.l][cur.r][cur.c].c == 'E') {
                    ans = turn;
                    goto end;
                }
                TIMES(i, 6) {
                    const State next(cur.l + DL[i], cur.r + DR[i], cur.c + DC[i]);
                    if((0 <= next.l && next.l < L) &&
                       (0 <= next.r && next.r < R) &&
                       (0 <= next.c && next.c < C) &&
                       (dungeon[next.l][next.r][next.c].c != '#'))
                    {
                        if(!dungeon[next.l][next.r][next.c].visited) {
                            dungeon[next.l][next.r][next.c].visited = true;
                            nextq.push_back(next);
                        }
                    }
                }
            }
            q.swap(nextq);
        }
end:
        if(ans == -1) {
            cout << "Trapped!" << endl;
        } else {
            cout << "Escaped in " << ans << " minute(s)." << endl;
        }
    }
    return 0;
}
