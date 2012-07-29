//Name: Shopping in JOI Kingdom
//Level: 3
//Category: グラフ,Graph,最短経路
//Note:

/*
 * とりあえず道の途中に家があるときのことは考えず，各頂点についてショッピングモールからの
 * 最短距離を求める．
 * これは各ショッピングモールを始点としたダイクストラで求められる．
 * ただしナイーブにやると最大ケースで死にそうなので，ダイクストラの途中で他のショッピングモールに
 * ぶつかった場合はそこで枝刈りするようにした．
 *
 * ある2頂点があって，それぞれのショッピングモールへの最短距離がaとbで距離lの辺でつながっているとき，
 * この辺上での最遠点では
 * a+ul == b+(1-u)l
 * が成立しているはずであるから，各aとbの組について方程式を解いてulを求め，最大のa+ulを選べばそれが解となる．
 * (最短距離の定義より，min(a,b)+l >= max(a,b)であることに注意)
 */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

struct Road {
    int from, to;
    int len;

    Road() {}
    Road(int f, int t, int l) : from(f), to(t), len(l) {}
};

vector<Road> roads_of[3000];
bool is_shopping_mall[3000];
int min_dist[3000];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N, M, K;
    cin >> N >> M >> K;
    for(int i = 0; i < M; ++i) {
        int a, b, l;
        cin >> a >> b >> l;
        --a; --b;
        roads_of[a].push_back(Road(a, b, l));
        roads_of[b].push_back(Road(b, a, l));
    }
    fill_n(is_shopping_mall, N, false);
    for(int i = 0; i < K; ++i) {
        int a;
        cin >> a;
        --a;
        is_shopping_mall[a] = true;
    }
    fill_n(min_dist, N, INT_MAX);

    static int memo[3000];
    fill_n(memo, N, INT_MAX);
    for(int start = 0; start < N; ++start) {
        if(!is_shopping_mall[start]) continue;
        priority_queue<pair<int, int> > q;
        q.push(make_pair(0, start));
        memo[start] = 0;
        while(!q.empty()) {
            int cost = -q.top().first;
            int pos = q.top().second;
            q.pop();
            if(memo[pos] < cost) continue;
            min_dist[pos] = min(min_dist[pos], cost);

            for(vector<Road>::iterator it = roads_of[pos].begin(); it != roads_of[pos].end(); ++it) {
                if(is_shopping_mall[it->to]) continue;

                int nc = cost + it->len;
                if(memo[it->to] > nc) {
                    memo[it->to] = nc;
                    q.push(make_pair(-nc, it->to));
                }
            }
        }
    }

    int ans = 0;
    for(int i = 0; i < N; ++i) {
        int d = 0;
        const int a = min_dist[i];
        // a+ul == b+vl, u+v == 1
        // a+ul == b+(1-u)l
        // 2ul == b-a+l
        // ul == (b-a+l)/2
        for(vector<Road>::iterator it = roads_of[i].begin(); it != roads_of[i].end(); ++it) {
            const int b = min_dist[it->to];
            if(b >= a) {
                int ul = (b-a+it->len) / 2;
                if((b-a+it->len) % 2 == 1) ++ul;
                d = max(d, min_dist[i] + ul);
            }
        }
        ans = max(ans, d);
    }

    cout << ans << endl;
    return 0;
}
