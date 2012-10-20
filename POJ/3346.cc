//Name: Treasure of the Chimp Island
//Level: 3
//Category: ダイクストラ,Dijkstra
//Note:

/*
 * [y][x][ダイナマイトの数] でダイクストラするだけ．
 * 辺数の最大値は定数なので，頂点数 V に対してオーダーは O(V log V)．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <queue>

using namespace std;

const int INF = 100*100*10;
struct Tag {
    int y, x, dynamites;
    int cost;
    Tag(int y, int x, int d, int c) : y(y), x(x), dynamites(d), cost(c) {}

    bool operator <(const Tag &other) const {
        return cost > other.cost; // Reverse order
    }
};

int memo[100][100][10];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    while(true) {
        vector<string> field;
        while(true) {
            string line;
            getline(cin, line);
            if(line == "--") return 0;
            if(line == "") break;
            field.push_back(line);
        }
        const int H = field.size();
        const int W = field[0].size();

        priority_queue<Tag> q;
        for(int y = 0; y < H; ++y) {
            for(int x = 0; x < W; ++x) {
                for(int i = 0; i <= 9; ++i) memo[y][x][i] = INF;
                if(field[y][x] == '#') {
                    q.push(Tag(y, x, 0, 0));
                } else if(isalpha(field[y][x])) {
                    const int d = field[y][x] - 'A' + 1;
                    q.push(Tag(y, x, d, 0));
                }
            }
        }
        int ans = INF;
        while(!q.empty()) {
            Tag t = q.top();
            q.pop();
            if(t.cost > memo[t.y][t.x][t.dynamites]) continue;
            memo[t.y][t.x][t.dynamites] = t.cost;

            const static int dx[] = {1, 0, -1, 0};
            const static int dy[] = {0, 1, 0, -1};
            for(int i = 0; i < 4; ++i) {
                const int nx = t.x + dx[i];
                const int ny = t.y + dy[i];
                if(nx < 0 || W <= nx || ny < 0 || H <= ny) continue;
                if(field[ny][nx] == '*') continue;
                if(field[ny][nx] == '$') {
                    ans = t.cost;
                    goto end;
                }
                if(field[ny][nx] == '.') {
                    if(memo[ny][nx][t.dynamites] > t.cost) {
                        memo[ny][nx][t.dynamites] = t.cost;
                        q.push(Tag(ny, nx, t.dynamites, t.cost));
                    }
                } else if(isdigit(field[ny][nx])) {
                    // Use dynamite
                    if(t.dynamites > 0) {
                        const int nd = t.dynamites-1;
                        if(memo[ny][nx][nd] > t.cost) {
                            memo[ny][nx][nd] = t.cost;
                            q.push(Tag(ny, nx, nd, t.cost));
                        }
                    }
                    // Not use dynamite
                    const int nc = t.cost + field[ny][nx] - '0';
                    if(memo[ny][nx][t.dynamites] > nc) {
                        memo[ny][nx][t.dynamites] = nc;
                        q.push(Tag(ny, nx, t.dynamites, nc));
                    }
                }
            }
        }
end:
        if(ans == INF) cout << "IMPOSSIBLE" << endl;
        else cout << ans << endl;
    }
    return 0;
}
