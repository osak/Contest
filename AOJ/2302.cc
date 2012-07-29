#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <cstdio>
#include <string>

using namespace std;

typedef vector<vector<int> > Matrix;
typedef pair<int, int> Pos;

int dr[] = {0, 1, 0, -1};
int dc[] = {1, 0, -1, 0};

inline bool inRange(int a, int x, int b) {
    return a <= x && x < b;
}

int main() {
    int R, C, M;
    scanf("%d %d %d", &R, &C, &M);

    vector<string> v;
    char buf[100];
    for(int i = 0; i < R; ++i) {
        scanf(" %s", buf);
        v.push_back(string(buf));
    }

    Matrix cons(R), on(R), off(R);
    for(int r = 0; r < R; ++r) {
        for(int c = 0; c < C; ++c) {
            int n;
            scanf(" %d", &n);
            cons[r].push_back(n);
        }
    }
    for(int r = 0; r < R; ++r) {
        for(int c = 0; c < C; ++c) {
            int n;
            scanf(" %d", &n);
            on[r].push_back(n);
        }
    }
    for(int r = 0; r < R; ++r) {
        for(int c = 0; c < C; ++c) {
            int n;
            scanf(" %d", &n);
            off[r].push_back(n);
        }
    }

    vector<pair<int, int> > room;
    vector<vector<vector<int> > > time_seq(R, vector<vector<int> >(C));
    Pos prev_pos;
    int curtime = 0;
    for(int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;

        if(i == 0) {
            time_seq[a][b].push_back(curtime++);
        }
        else {
            const Pos goal(a, b);
            vector<vector<Pos> > prev(R, vector<Pos>(C, make_pair(-1, -1)));
            queue<Pos> q;
            q.push(prev_pos);
            while(!q.empty()) {
                Pos p = q.front();
                q.pop();

                if(p == goal) {
                    Pos cur = p;
                    vector<Pos> route;
                    while(cur != prev_pos) {
                        route.push_back(cur);
                        cur = prev[cur.first][cur.second];
                    }
                    //cout << "route ";
                    for(int i = route.size()-1; i >= 0; --i) {
                        //cout << '(' << route[i].first << ' ' << route[i].second << ") ";
                        const Pos &pp = route[i];
                        time_seq[pp.first][pp.second].push_back(curtime++);
                    }
                    //cout << endl;
                    break;
                }
                for(int i = 0; i < 4; ++i) {
                    int nr = p.first + dr[i];
                    int nc = p.second + dc[i];
                    if(inRange(0, nr, R) && inRange(0, nc, C) && v[nr][nc] == '.' && prev[nr][nc].first == -1) {
                        prev[nr][nc] = p;
                        q.push(Pos(nr, nc));
                    }
                }
            }
        }
        prev_pos = make_pair(a, b);
    }

    //time_seq[prev_pos.first][prev_pos.second].push_back(curtime++);

    int cost = 0;
    for(int r = 0; r < R; ++r) {
        for(int c = 0; c < C; ++c) {
            bool state = false;
            const vector<int> &seq = time_seq[r][c];

            for(int i = 0; i < seq.size(); ++i) {
                //cout << r << ' ' << c << ' ' << seq[i] << endl;
                if(state == false) {
                    cost += on[r][c];
                    state = true;
                }

                if(i+1 < seq.size()) {
                    int cons_is_on = cons[r][c] * (seq[i+1]-seq[i]);
                    if(off[r][c] + on[r][c] > cons_is_on) {
                        cost += cons_is_on;
                    }
                    else {
                        cost += off[r][c];
                        state = false;
                    }
                }
                else {
                    cost += off[r][c];
                    state = false;
                }
            }
        }
    }

    printf("%d\n", cost);
    
    return 0;
}
