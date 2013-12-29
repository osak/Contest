//Name: Maze
//Level: 2
//Category: 幅優先探索,BFS
//Note:

/**
 * 一度全部の道を壁にしてから、S-Kマスだけ道を掘り出すようにするとよい。
 * オーダーはO(NM)。
 */
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

void paint(vector<string> &field, int from_r, int from_c, int K) {
    const int R = field.size();
    const int C = field[0].size();
    queue<pair<int,int>> q;
    q.push(make_pair(from_r, from_c));
    field[from_r][from_c] = '.';
    --K;
    while(K > 0) {
        const int r = q.front().first;
        const int c = q.front().second;
        q.pop();
        static const int DR[] = {0, -1, 0, 1};
        static const int DC[] = {1, 0, -1, 0};
        for(int dir = 0; dir < 4; ++dir) {
            const int nr = r + DR[dir];
            const int nc = c + DC[dir];
            if(nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
            if(field[nr][nc] != 'X') continue;
            field[nr][nc] = '.';
            q.push(make_pair(nr, nc));
            if(--K == 0) break;
        }
    }
}

bool solve() {
    int R, C, K;
    if(!(cin >> R >> C >> K)) return false;
    if(!R && !C && !K) return false;

    vector<string> field(R);
    int road_cnt = 0;
    for(int i = 0; i < R; ++i) {
        cin >> field[i];
        for(char &c : field[i]) {
            if(c == '.') {
                c = 'X';
                ++road_cnt;
            }
        }
    }
    for(int r = 0; r < R; ++r) {
        for(int c = 0; c < C; ++c) {
            if(field[r][c] == 'X') {
                paint(field, r, c, road_cnt-K);
                goto end;
            }
        }
    }
end:
    for(const string &s : field) {
        cout << s << endl;
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
