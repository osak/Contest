//Name: Surrounding Area
//Level: 2
//Category: 塗りつぶし,幅優先探索,BFS
//Note:

/**
 * それぞれの色の杭から、他の杭に干渉しない範囲をその色で塗りつぶす。
 * 最初に空きマスだったマスのうち、片方の色のみで塗りつぶされているマスが囲まれたマスである。
 *
 * オーダーはO(WH)。
 */
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

void paint(const vector<string> &field, int r, int c, vector<vector<bool>> &buf) {
    const int R = field.size();
    const int C = field[0].size();
    const char ch = field[r][c];
    queue<pair<int,int>> q;
    q.push(make_pair(r, c));
    buf[r][c] = true;
    while(!q.empty()) {
        const int cur_r = q.front().first;
        const int cur_c = q.front().second;
        q.pop();
        static const int DR[] = {0, -1, 0, 1};
        static const int DC[] = {1, 0, -1, 0};
        for(int dir = 0; dir < 4; ++dir) {
            const int nr = cur_r + DR[dir];
            const int nc = cur_c + DC[dir];
            if(nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
            if(field[nr][nc] != ch && field[nr][nc] != '.') continue;
            if(buf[nr][nc]) continue;
            buf[nr][nc] = true;
            q.push(make_pair(nr, nc));
        }
    }
}

bool solve() {
    int R, C;
    if(!(cin >> C >> R)) return false;
    if(!R && !C) return false;
    vector<string> field(R);
    for(string &s : field) {
        cin >> s;
    }
    vector<vector<bool>> white(R, vector<bool>(C));
    vector<vector<bool>> black(R, vector<bool>(C));
    for(int r = 0; r < R; ++r) {
        for(int c = 0; c < C; ++c) {
            if(field[r][c] == 'W') {
                paint(field, r, c, white);
            } else if(field[r][c] == 'B') {
                paint(field, r, c, black);
            }
        }
    }
    int w = 0, b = 0;
    for(int r = 0; r < R; ++r) {
        for(int c = 0; c < C; ++c) {
            if(field[r][c] == '.') {
                if(white[r][c] && !black[r][c]) ++w;
                else if(!white[r][c] && black[r][c]) ++b;
            }
        }
    }
    cout << b << ' ' << w << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
