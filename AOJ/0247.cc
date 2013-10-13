//Name: Ice Maze
//Level: 3
//Category: 探索,幅優先探索,BFS,ヒューリスティック
//Note:

/**
 * まず、1マスの氷は壁と同じとみなせる。
 * 次に、それぞれの氷の固まりについて侵入可能回数を管理することを考えると、最悪のパターンでは
 * 2マスの氷が36個敷き詰めてあるような迷路が考えられる。
 * このとき、状態数は2^36*12*12であるが、多くの状態が到達不能であると考えられる。
 * したがって、この状態をすべてハッシュ値として記憶しながら幅優先探索を行うことが考えられる。
 *
 * 実際、この方針で実装するとAOJでは通る。
 * さらに計算量の削減を考えるのであれば、両側全探索を行う、ヒューリスティックによるコスト関数を導入してA*を行う、などの方法が考えられる。
 */
#include <iostream>
#include <unordered_set>
#include <string>
#include <array>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef unsigned long long ULL;

int ORD, N;
ULL h(const vector<int> &v, int y, int x) {
    ULL res = 0;
    for(int i : v) {
        res *= ORD;
        res += i;
    }
    res *= 12;
    res += y;
    res *= 12;
    res += x;
    return res;
}

void d(ULL val, vector<int> &v, int &y, int &x) {
    v.resize(N, 0);
    x = val % 12;
    val /= 12;
    y = val % 12;
    val /= 12;
    for(int i = v.size()-1; i >= 0; --i) {
        v[i] = val % ORD;
        val /= ORD;
    }
}

const int DY[] = {0, -1, 0, 1};
const int DX[] = {1, 0, -1, 0};

inline bool in_range(int a, int x, int b) {
    return a <= x && x < b;
}

int X, Y;
int bfs(vector<string> &v, int y, int x, array<array<int,12>,12> &field, int label) {
    int cnt = 0;
    queue<pair<int,int>> q;
    q.push(make_pair(y, x));
    while(!q.empty()) {
        int cy = q.front().first;
        int cx = q.front().second;
        q.pop();
        v[cy][cx] = '$';
        field[cy][cx] = label;
        ++cnt;
        for(int i = 0; i < 4; ++i) {
            const int ny = cy + DY[i];
            const int nx = cx + DX[i];
            if(in_range(0, ny, Y) && in_range(0, nx, X) && v[ny][nx] == 'X') {
                q.push(make_pair(ny, nx));
            }
        }
    }
    return cnt;
}

bool solve() {
    cin >> X >> Y;
    if(!X && !Y) return false;

    vector<string> v(Y);
    for(string &s : v) {
        cin >> s;
    }

    array<array<int,12>,12> field;
    pair<int,int> start, goal;
    vector<int> ice;
    ice.push_back(0);
    for(int y = 0; y < Y; ++y) {
        for(int x = 0; x < X; ++x) {
            if(v[y][x] == 'X') {
                int cnt = bfs(v, y, x, field, -(int)ice.size());
                if(cnt == 1) {
                    field[y][x] = 0;
                } else {
                    ice.push_back(cnt/2);
                }
            } else if(v[y][x] == '#') {
                field[y][x] = 0;
            } else if(v[y][x] != '$') {
                field[y][x] = 1;
                if(v[y][x] == 'S') {
                    start = make_pair(y, x);
                } else if(v[y][x] == 'G') {
                    goal = make_pair(y, x);
                }
            }
        }
    }

    N = ice.size();
    ORD = *max_element(ice.begin(), ice.end())+1;
    vector<int> state(N, 0);
    vector<ULL> q[2];
    unordered_set<ULL> memo;
    q[0].push_back(h(state, start.first, start.second));
    memo.insert(q[0].back());
    int turn = 0;
    while(q[0].size() > 0) {
        q[1].clear();
        for(const auto &s : q[0]) {
            int x, y;
            d(s, state, y, x);
            //cout << turn << ": " << x << ' ' << y << ' ' << "s " << state[1] << endl;
            if(y == goal.first && x == goal.second) {
                goto end;
            }
            for(int i = 0; i < 4; ++i) {
                const int ny = y + DY[i];
                const int nx = x + DX[i];
                if(in_range(0, ny, Y) && in_range(0, nx, X)) {
                    if(field[ny][nx] < 0) {
                        const int idx = -field[ny][nx];
                        if(state[idx] >= ice[idx]) continue;
                        state[idx]++;
                        const ULL nh = h(state, ny, nx);
                        if(memo.count(nh) == 0) {
                            memo.insert(nh);
                            q[1].push_back(nh);
                        }
                        state[idx]--;
                    } else if(field[ny][nx] == 1) {
                        const ULL nh = h(state, ny, nx);
                        if(memo.count(nh) == 0) {
                            memo.insert(nh);
                            q[1].push_back(nh);
                        }
                    }
                }
            }
        }
        ++turn;
        q[0].swap(q[1]);
    }
end:
    cout << turn << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;

    return 0;
}
