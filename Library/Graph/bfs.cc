// Painting algorithm
// Runs in O(HW)
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

// Used in:
// AOJ0118
