#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned long long ULL;
typedef long long LL;

int field[1000][1000];
int row_sum[1000], col_sum[1000];

inline int pow2(int n) {
    return n*n;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N, M;
    cin >> N >> M;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            cin >> field[i][j];
            row_sum[i] += field[i][j];
            col_sum[j] += field[i][j];
        }
    }

    // Decide row
    int best_row = -1;
    ULL cur = 0;
    ULL best_score;
    {
        for(int row = 0; row < N; ++row) {
            for(int col = 0; col < M; ++col) {
                cur += (ULL)field[row][col] * (pow2(2+4*row) + pow2(2+4*col));
            }
        }
        //cout << cur << endl;
        best_score = cur;
        best_row = 0;
        for(int r = 1; r <= N; ++r) {
            // Move row
            for(int back_r = 0; back_r < r-1; ++back_r) {
                const int dist = 2+(r-1-back_r-1)*4;
                cur += (ULL)row_sum[back_r] * (8*dist+16);
            }
            for(int front_r = r; front_r < N; ++front_r) {
                const int dist = 2+(front_r-(r-1))*4;
                cur += (LL)row_sum[front_r] * (-8*dist+16);
            }
            //cout << cur << endl;
            if(cur < best_score) {
                best_score = cur;
                best_row = r;
            }
        }
    }

    // Decide column
    int best_col = 0;
    {
        // Back to best_row
        cur = best_score;
        for(int c = 1; c <= M; ++c) {
            // Move col
            for(int back_c = 0; back_c < c-1; ++back_c) {
                const int dist = 2+(c-1-back_c-1)*4;
                cur += (ULL)col_sum[back_c] * (8*dist+16);
            }
            for(int front_c = c; front_c < M; ++front_c) {
                const int dist = 2+(front_c-(c-1))*4;
                //cout << col_sum[front_c]*(8*dist+16) << endl;
                cur += (LL)col_sum[front_c] * (-8*dist+16);
            }
            //cout << cur << endl;
            if(cur < best_score) {
                best_score = cur;
                best_col = c;
            }
        }
    }

    cout << best_score << endl;
    cout << best_row << ' ' << best_col << endl;
    return 0;
}

