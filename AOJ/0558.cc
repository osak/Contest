//Name: Cheese
//Level: 2
//Category: グラフ,Graph,最短経路,幅優先探索,BFS
//Note:

/*
 * 要するに1からNまでを順番に最短経路で廻ればよい．
 * 最短経路は幅優先探索で求めることができる．
 *
 * オーダーは O(NHW)。
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <queue>

using namespace std;

const int DR[] = {0, 0, 1, -1};
const int DC[] = {1, -1, 0, 0};
struct Tag {
    int r, c, distance;
    Tag() {}
    Tag(int r, int c, int d) : r(r), c(c), distance(d) {}
};
bool visited[1000][1000];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int H, W, N;
    cin >> H >> W >> N;
    vector<string> field(H);
    pair<int,int> cur;
    for(int i = 0; i < H; ++i) {
        cin >> field[i];
        size_t spos = field[i].find('S');
        if(spos != string::npos) {
            cur = make_pair(i, spos);
        }
    }
    int ans = 0;
    for(int target = 1; target <= N; ++target) {
        for(int i = 0; i < H; ++i) {
            fill_n(visited[i], W, false);
        }
        Tag route;
        queue<Tag> q;
        q.push(Tag(cur.first, cur.second, 0));
        while(!q.empty()) {
            Tag t = q.front();
            q.pop();
            for(int i = 0; i < 4; ++i) {
                int nr = t.r + DR[i];
                int nc = t.c + DC[i];
                if(0 <= nr && nr < H && 0 <= nc && nc < W) {
                    if(field[nr][nc] != 'X' && !visited[nr][nc]) {
                        visited[nr][nc] = true;
                        if(field[nr][nc] == '0'+target) {
                            route = Tag(nr, nc, t.distance+1);
                            goto found;
                        }
                        q.push(Tag(nr, nc, t.distance+1));
                    }
                }
            }
        }
found:
        ans += route.distance;
        cur = make_pair(route.r, route.c);
    }

    cout << ans << endl;
    return 0;
}
