//Name: Subway
//Level: 2
//Category: グラフ,Graph,最短経路,Dijkstra
//Note:

/**
 * グラフを構築し、Dijkstra法で最短経路を求める。
 *
 * オーダーはO(N log N)。
 * ただしNは駅の数。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <complex>
#include <queue>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

struct Point {
    complex<double> pos;
    int id;

    Point() {}
    Point(double x, double y, int id) : pos(x, y), id(id) {}
};

double dist[202][202];
double memo[202];

bool solve() {
    int sx, sy, tx, ty;
    scanf("%d %d %d %d", &sx, &sy, &tx, &ty);
    vector<Point> points;
    points.push_back(Point(sx, sy, 0));
    points.push_back(Point(tx, ty, 1));
    TIMES(i, 202) {
        TIMES(j, 202) {
            dist[i][j] = -1;
        }
    }

    int prev = -1;
    while(true) {
        int x, y;
        if(scanf("%d %d", &x, &y) == EOF) break;
        if(x == -1 && y == -1) {
            prev = -1;
            continue;
        }
        const int id = points.size();
        points.push_back(Point(x, y, id));
        if(prev != -1) {
            dist[id][prev] = dist[prev][id] = abs(points[id].pos - points[prev].pos) / (40*1000/60.0);
        }
        prev = id;
    }
    const int N = points.size();
    TIMES(i, N) {
        TIMES(j, N) {
            const double d = abs(points[i].pos - points[j].pos) / (10*1000/60.0);
            if(dist[i][j] < 0 || dist[i][j] > d) {
                dist[i][j] = dist[j][i] = d;
            }
        }
        memo[i] = -1;
    }

    priority_queue<pair<double,int> > q;
    q.push(make_pair(0.0, 0));
    memo[0] = 0;
    while(!q.empty()) {
        const double cost = -q.top().first;
        const int cur = q.top().second;
        q.pop();
        if(memo[cur] < cost) continue;
        if(cur == 1) {
            int ans = static_cast<int>(cost + 0.5);
            printf("%d\n", ans);
            break;
        }
        TIMES(i, N) {
            const double nc = cost + dist[cur][i];
            //printf("%d %d %f\n", cur, i, nc);
            if(memo[i] == -1 || memo[i] > nc) {
                memo[i] = nc;
                q.push(make_pair(-nc, i));
            }
        }
    }
    return false;
}

int main() {
    while(solve()) ;
    return 0;
}
