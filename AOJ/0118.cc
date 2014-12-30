//Name: Property Distribution
//Level: 2
//Category: 塗りつぶし,幅優先探索,BFS
//Note: 

/**
 * 同じ記号が連続する領域を塗りつぶしながら、領域数をカウントする。
 *
 * オーダーは O(HW)。
 */
#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

template<typename T, typename U>
int paint(vector<T> &g, int sr, int sc, U nullv) {
    static const int DR[] = {0, -1, 0, 1};
    static const int DC[] = {1, 0, -1, 0};
    const int H = g.size();
    const int W = g[0].size();
    queue<pair<int,int>> q;

    const auto target = g[sr][sc];
    q.push(make_pair(sr, sc));
    g[sr][sc] = nullv;
    int cnt = 1;
    while(!q.empty()) {
        const int r = q.front().first;
        const int c = q.front().second;
        q.pop();
        for(int d = 0; d < 4; ++d) {
            const int nr = r + DR[d];
            const int nc = c + DC[d];
            if(nr < 0 || nr >= H || nc < 0 || nc >= W) continue;
            if(g[nr][nc] != target) continue;
            g[nr][nc] = nullv;
            q.push(make_pair(nr, nc));
            ++cnt;
        }
    }
    return cnt;
}

bool solve() {
    int H, W;
    if(!(cin >> H >> W)) return false;
    if(!H && !W) return false;

    vector<string> field(H);
    for(int r = 0; r < H; ++r) {
        cin >> field[r];
    }
    int ans = 0;
    for(int r = 0; r < H; ++r) {
        for(int c = 0; c < W; ++c) {
            if(field[r][c] != '.') {
                paint(field, r, c, '.');
                ++ans;
            }
        }
    }
    cout << ans << endl;

    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    while(solve()) ;
    return 0;
}
