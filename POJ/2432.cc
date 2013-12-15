//Name: Around the world
//Level: 4
//Category: グラフ,Graph,角度,幅優先探索,BFS
//Note:

/**
 * 累積移動角度が0より大きい状態で元の場所に戻ってこれればよい。
 * 時計回りに移動することを考えると、ある頂点に移動するときは、以前にそこに来た時よりも累積角度が大きくなければ意味がない。
 * したがって、累積角度を記録しながらBFSすることで最短距離が求められる。
 *
 * 同じ頂点に2回来ること自体は意味があり、
 * 4 4
 * 0
 * 178
 * 347
 * 359
 * 1 4
 * 4 2
 * 2 3
 * 3 4
 * のようなケースでは、最初と最後に4番を通る必要がある。
 *
 * オーダーはO(N+M)。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

bool solve() {
    int N, M;
    if(scanf("%d %d", &N, &M) == EOF) return false;
    if(!N && !M) return false;

    static int lngs[5000];
    TIMES(i, N) {
        scanf("%d", lngs+i);
    }
    {
        int offset = lngs[0];
        TIMES(i, N) {
            lngs[i] = lngs[i] - offset + 360;
            lngs[i] %= 360;
        }
    }
    static pair<int,int> edges[50000];
    static int start_of[5000];
    TIMES(i, M) {
        int a, b;
        scanf("%d %d", &a, &b);
        --a; --b;
        edges[i*2] = make_pair(a, b);
        edges[i*2+1] = make_pair(b, a);
    }
    sort(edges, edges+M*2);
    fill_n(start_of, N, -1);
    TIMES(i, M*2) {
        if(i == 0) {
            start_of[edges[i].first] = i;
        } else {
            if(edges[i-1].first != edges[i].first) {
                start_of[edges[i].first] = i;
            }
        }
    }

    static int memo[5000];
    TIMES(i, N) {
        memo[i] = -180 * 10000;
    }
    vector<pair<int,int> > q[2];
    q[0].push_back(make_pair(0, 0));
    int ans = -1;
    for(int turn = 0; q[0].size() > 0; ++turn) {
        const int K = q[0].size();
        q[1].clear();
        TIMES(i, K) {
            const int cur = q[0][i].first;
            const int acc = q[0][i].second;
            //printf("%d %d %d\n", turn, cur, acc);
            if(cur == 0 && acc > 0) {
                ans = turn;
                goto end;
            }
            if(start_of[cur] == -1) continue;
            const int cur_lng = lngs[cur];
            for(int i = start_of[cur]; i < M*2 && edges[i].first == cur; ++i) {
                const int to = edges[i].second;
                const int to_lng = lngs[to];
                int d = (to_lng+360 - cur_lng) % 360;
                d = min(d, 360-d);
                if((cur_lng + d) % 360 == to_lng) { // CW
                    const int nacc = acc + d;
                    if(memo[to] < nacc) {
                        memo[to] = nacc;
                        q[1].push_back(make_pair(to, nacc));
                    }
                } else { // CCW
                    const int nacc = acc - d;
                    if(memo[to] < nacc) {
                        memo[to] = nacc;
                        q[1].push_back(make_pair(to, nacc));
                    }
                }
            }
        }
        q[0].swap(q[1]);
    }
end:
    printf("%d\n", ans);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
