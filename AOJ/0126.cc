//Name: Puzzle
//Level: 2
//Category: 実装
//Note: 

/**
 * 問題文の通りに実装する。
 *
 * オーダーは O(1)。
 */
#include <iostream>
#include <vector>

using namespace std;

struct Cell {
    int val;
    bool wrong;

    Cell() : val(0), wrong(false) {}
};

void check_row(vector<vector<Cell>> &f) {
    for(int r = 0; r < 9; ++r) {
        int cnt[10] = {0};
        for(int c = 0; c < 9; ++c) {
            cnt[f[r][c].val]++;
        }
        for(int c = 0; c < 9; ++c) {
            if(cnt[f[r][c].val] > 1) f[r][c].wrong = true;
        }
    }
}

void check_col(vector<vector<Cell>> &f) {
    for(int c = 0; c < 9; ++c) {
        int cnt[10] = {0};
        for(int r = 0; r < 9; ++r) {
            cnt[f[r][c].val]++;
        }
        for(int r = 0; r < 9; ++r) {
            if(cnt[f[r][c].val] > 1) f[r][c].wrong = true;
        }
    }
}

void check_sq(vector<vector<Cell>> &f) {
    for(int r = 0; r < 9; r += 3) {
        for(int c = 0; c < 9; c += 3) {
            int cnt[10] = {0};
            for(int dr = 0; dr < 3; ++dr) {
                for(int dc = 0; dc < 3; ++dc) {
                    cnt[f[r+dr][c+dc].val]++;
                }
            }
            for(int dr = 0; dr < 3; ++dr) {
                for(int dc = 0; dc < 3; ++dc) {
                    if(cnt[f[r+dr][c+dc].val] > 1) f[r+dr][c+dc].wrong = true;
                }
            }
        }
    }
}

bool solve(bool first) {
    vector<vector<Cell>> f(9, vector<Cell>(9));
    for(int r = 0; r < 9; ++r) {
        for(int c = 0; c < 9; ++c) {
            cin >> f[r][c].val;
        }
    }
    if(!first) cout << endl;

    check_row(f);
    check_col(f);
    check_sq(f);
    for(int r = 0; r < 9; ++r) {
        for(int c = 0; c < 9; ++c) {
            cout << (f[r][c].wrong ? '*' : ' ') << f[r][c].val;
        }
        cout << endl;
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    bool first = true;
    int N;
    cin >> N;
    while(N--) {
        solve(first);
        first = false;
    }
    return 0;
}
