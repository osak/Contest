//Name: Chain Disappearance Puzzle
//Level: 2
//Category: シミュレーション
//Note:

/**
 * 素直にシミュレーションすればよい。
 * 消える石にマークする処理と、消えたところに石を詰める処理は別々に行わないといけないことに注意する。
 *
 * オーダーは O(H^2)。
 */
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void mark(vector<vector<int>> &field, int r, int c, int cnt) {
    for(int cc = c-cnt+1; cc <= c; ++cc) {
        field[r][cc] = 0;
    }
}

int sim(vector<vector<int>> &field) {
    const int H = field.size();
    int score = 0;
    for(int r = 0; r < H; ++r) {
        int cnt = 0;
        int prev = -1;
        for(int c = 0; c < 5; ++c) {
            if(field[r][c] == prev) {
                ++cnt;
            } else {
                if(cnt >= 3 && prev != 0) {
                    score += cnt * prev;
                    mark(field, r, c-1, cnt);
                }
                cnt = 1;
            }
            prev = field[r][c];
        }
        if(cnt >= 3 && prev != 0) {
            score += cnt * prev;
            mark(field, r, 4, cnt);
        }
    }
    if(score > 0) {
        for(int r = H-1; r >= 0; --r) {
            for(int c = 0; c < 5; ++c) {
                if(field[r][c] == 0) {
                    for(int rr = r-1; rr >= 0; --rr) {
                        if(field[rr][c] != 0) {
                            field[r][c] = field[rr][c];
                            field[rr][c] = 0;
                            break;
                        }
                    }
                }
            }
        }
    }
    return score;
}

bool solve() {
    int H;
    if(!(cin >> H)) return false;
    if(!H) return false;

    vector<vector<int>> field(H);
    for(int i = 0; i < H; ++i) {
        for(int j = 0; j < 5; ++j) {
            int v;
            cin >> v;
            field[i].push_back(v);
        }
    }

    int ans = 0;
    while(true) {
        const int score = sim(field);
        if(score == 0) break;
        ans += score;
    }
    cout << ans << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
