#include <iostream>
#include <vector>
#include <string>

using namespace std;

inline bool inRange(int a, int x, int b) {
    return a <= x && x <= b;
}

int dfs(vector<vector<string> > &plate, int k, int r, int c) {
    const int d[][3] = { {-1, 0, 0}, {1, 0, 0}, {0, -1, 0}, {0, 1, 0}, {0, 0, -1}, {0, 0, 1} };

    int K = plate.size();
    int R = plate[0].size();
    int C = plate[0][0].size();
    int cnt = 0;
    for(int i = 0; i < 6; ++i) {
        int kk = k+d[i][0], rr = r+d[i][1], cc=c+d[i][2];
        if(inRange(0, kk, K-1) && inRange(0, rr, R-1) && inRange(0, cc, C-1) && plate[kk][rr][cc] == '.') {
            ++cnt;
            plate[kk][rr][cc] = '#';
            cnt += dfs(plate, kk, rr, cc);
        }
    }
    return cnt;
}

int main() {
    int K, N, M;
    cin >> K >> N >> M;
    vector<vector<string> > plate(K, vector<string>(N));

    for(int i = 0; i < K; ++i) {
        for(int j = 0; j < N; ++j) {
            cin >> plate[i][j];
        }
    }

    int R, C;
    cin >> R >> C;
    --R; --C;

    plate[0][R][C] = '#';
    cout << dfs(plate, 0, R, C)+1 << endl;

    return 0;
}
