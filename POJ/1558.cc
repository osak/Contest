//Name: Board Silly
//Level: 1
//Category: やるだけ,シミュレーション
//Note:

/**
 * 全てのコマに対して、指定されたとおりに動きをシミュレーションし、可能かどうか判定する。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

inline string pos_code(int r, int c) {
    char buf[3];
    buf[0] =  "ABCDEFGH"[r];
    buf[1] = "12345678"[c];
    buf[2] = 0;
    return string(buf);
}

int count_token(const vector<string> &field, int r, int c, int dr, int dc) {
    int cnt = 0;
    for(int i = 0; ; ++i) {
        const int nr = r + dr*i;
        const int nc = c + dc*i;
        if(nr < 0 || nr >= 8 || nc < 0 || nc >= 8) break;
        if(field[nr][nc] != '.') ++cnt;
    }
    for(int i = -1; ; --i) {
        const int nr = r + dr*i;
        const int nc = c + dc*i;
        if(nr < 0 || nr >= 8 || nc < 0 || nc >= 8) break;
        if(field[nr][nc] != '.') ++cnt;
    }
    return cnt;
}

void check_move(const vector<string> &field, int r, int c, vector<string> &ans) {
    const string from = pos_code(r, c);
    for(int dr = -1; dr <= 1; ++dr) {
        for(int dc = -1; dc <= 1; ++dc) {
            if(dr == 0 && dc == 0) continue;
            const int cnt = count_token(field, r, c, dr, dc);
            const int nr = r + dr * cnt;
            const int nc = c + dc * cnt;
            if(nr < 0 || nr >= 8 || nc < 0 || nc >= 8) continue;
            if(field[nr][nc] == field[r][c]) continue;
            bool ok = true;
            for(int i = 1; i < cnt; ++i) {
                const int ri = r + dr*i;
                const int ci = c + dc*i;
                if(field[ri][ci] != '.' && field[ri][ci] != field[r][c]) {
                    ok = false;
                    break;
                }
            }
            if(ok) {
                const string to = pos_code(nr, nc);
                ans.push_back(from + "-" + to);
            }
        }
    }
}

bool solve() {
    static bool first = true;
    vector<string> field(8);
    char buf[10];
    TIMES(i, 8) {
        if(scanf(" %s", buf) == EOF) return false;
        field[i] = string(buf);
    }
    char target;
    scanf(" %c", &target);

    vector<string> ans;
    for(int r = 0; r < 8; ++r) {
        for(int c = 0; c < 8; ++c) {
            if(field[r][c] == target) check_move(field, r, c, ans);
        }
    }
    sort(ans.begin(), ans.end());
    if(!first) puts("");
    if(ans.size() == 0) {
        puts("No moves are possible");
    } else {
        TIMES(i, ans.size()) {
            puts(ans[i].c_str());
        }
    }
    first = false;
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
