#include <iostream>
#include <vector>

using namespace std;

inline bool inRange(int a, int x, int b) {
    return a <= x && x < b;
}

void fill(vector<vector<int> > &v, int r, int c) {
    v[r][c] = 0;
    for(int dr = -1; dr <= 1; ++dr) {
        for(int dc = -1; dc <= 1; ++dc) {
            int nr = r + dr;
            int nc = c + dc;
            if(inRange(0, nr, v.size()) && inRange(0, nc, v[0].size()) && v[nr][nc]) {
                fill(v, nr, nc);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);

    while(true) {
        int C, R;
        cin >> C >> R;
        if(!C && !R) break;

        vector<vector<int> > v(R, vector<int>(C));
        for(int i = 0; i < R; ++i) 
            for(int j = 0; j < C; ++j)
                cin >> v[i][j];

        int cnt = 0;
        for(int r = 0; r < R; ++r) {
            for(int c = 0; c < C; ++c) {
                if(v[r][c]) {
                    ++cnt;
                    fill(v, r, c);
                }
            }
        }

        cout << cnt << endl;
    }

    return 0;
}

