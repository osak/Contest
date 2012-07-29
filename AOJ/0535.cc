#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int dfs(vector<vector<int> > &field, int y, int x) {
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    field[y][x] = 0;
    int ans = 0;
    for(int i = 0; i < 4; ++i) {
        int nx = x+dx[i];
        int ny = y+dy[i];
        if(field[ny][nx]) {
            ans = max(ans, dfs(field, ny, nx)+1);
        }
    }
    field[y][x] = 1;
    return ans;
}

int main() {
    while(true) {
        int M, N;
        cin >> M >> N;
        if(!M && !N) break;

        vector<vector<int> > field(M+2, vector<int>(N+2, 0));
        for(int i = 1; i <= M; ++i) {
            for(int j = 1; j <= N; ++j) {
                cin >> field[i][j];
            }
        }

        int ans = 0;
        for(int i = 1; i <= M; ++i) {
            for(int j = 1; j <= N; ++j) {
                if(field[i][j]) ans = max(ans, dfs(field, i, j)+1);
            }
        }
        cout << ans << endl;
    }
    return 0;
}
