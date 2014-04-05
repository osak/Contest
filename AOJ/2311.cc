//Name: Dessert Witch
//Level: 3
//Category: シミュレーション
//Note:

/**
 * 問題文の通りに置く場所を試していき、それぞれの置き方でひっくり返る個数を愚直にシミュレーションすればよい。
 *
 * オーダーはO(N^5)。
 * ただしNは1辺の長さで、N=8。
 */
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define TIMES(i_, n_) for(int i_ = 0; i_ < (n_); ++i_)

int put(vector<string> &field, int r, int c, char ch, bool actual = false) {
    static const int DR[] = {0, -1, -1, -1, 0, 1, 1, 1};
    static const int DC[] = {1, 1, 0, -1, -1, -1, 0, 1};
    int cnt = 0;
    TIMES(dir, 8) {
        int cur_r = r + DR[dir], cur_c = c + DC[dir];
        int tmp = 0;
        int phase = 0;
        while(0 <= cur_r && cur_r < 8 && 0 <= cur_c && cur_c < 8) {
            if(field[cur_r][cur_c] == ch) {
                cnt += tmp;
                if(actual && phase == 0) {
                    phase = 1;
                    cur_r = r+DR[dir];
                    cur_c = c+DC[dir];
                    continue;
                }
                break;
            }
            if(field[cur_r][cur_c] == '.') break;
            if(phase == 1) field[cur_r][cur_c] = ch;
            ++tmp;
            cur_r += DR[dir];
            cur_c += DC[dir];
        }
    }
    if(actual) {
        field[r][c] = ch;
    }
    return cnt;
}

bool mami(vector<string> &field) {
    int max_cnt = 0;
    int best_r, best_c;
    TIMES(r, 8) {
        TIMES(c, 8) {
            if(field[r][c] != '.') continue;
            int cnt = put(field, r, c, 'o');
            if(cnt > max_cnt) {
                max_cnt = cnt;
                best_r = r;
                best_c = c;
            }
        }
    }
    if(max_cnt > 0) {
        put(field, best_r, best_c, 'o', true);
    }
    return max_cnt > 0;
}

bool witch(vector<string> &field) {
    int max_cnt = 0;
    int best_r, best_c;
    for(int r = 7; r >= 0; --r) {
        for(int c = 7; c >= 0; --c) {
            if(field[r][c] != '.') continue;
            int cnt = put(field, r, c, 'x');
            if(cnt > max_cnt) {
                max_cnt = cnt;
                best_r = r;
                best_c = c;
            }
        }
    }
    if(max_cnt > 0) {
        put(field, best_r, best_c, 'x', true);
    }
    return max_cnt > 0;
}

bool solve() {
    vector<string> field(8);
    TIMES(i, 8) {
        cin >> field[i];
    }
    while(true) {
        bool changed = false;
        changed = mami(field) || changed;
        changed = witch(field) || changed;
        if(!changed) break;
    }
    TIMES(i, 8) {
        cout << field[i] << endl;
    }
    return false;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
