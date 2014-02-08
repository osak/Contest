//Name: Rectangular Covering
//Level: 3
//Category: 全探索
//Note:

/**
 * 任意の2つの点を選び、それをちょうど覆うような長方形について、その面積と含まれる点の集合を前処理で求める。
 * すると、覆われた点のパターンが与えられた時、残っている全ての点を覆う長方形の取り方が探索できる。
 * 2点を結ぶ直線が座標軸と平行なときは、高さ1の長方形で覆えばよい
 * （他の長方形を拡張して覆ったとしても、これより効率良くはなり得ない）。
 *
 * オーダーはO(2^N N^2)。
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

pair<int,int> points[15];
pair<int,int> cover[15][15];

int N;
int memo[1<<15];
int dfs(int pat) {
    int &res = memo[pat];
    if(res != -1) return res;
    TIMES(i, N) {
        if(pat & (1<<i)) continue;
        TIMES(j, N) {
            if(i == j) continue;
            const int tmp = dfs(pat | cover[i][j].first) + cover[i][j].second;
            //printf("%x %d %d %d %d\n", pat, i, j, tmp, dfs(pat | cover[i][j].first));
            if(res == -1 || tmp < res) {
                res = tmp;
            }
        }
    }
    return res;
}

bool solve() {
    if(scanf("%d", &N) == EOF) return false;
    if(!N) return false;
    TIMES(i, N) {
        scanf("%d %d", &points[i].first, &points[i].second);
    }
    TIMES(i, N) {
        TIMES(j, i) {
            const int minx = min(points[i].first, points[j].first);
            const int miny = min(points[i].second, points[j].second);
            int maxx = max(points[i].first, points[j].first);
            int maxy = max(points[i].second, points[j].second);
            if(minx == maxx) ++maxx;
            else if(miny == maxy) ++maxy;
            int pat = 0;
            TIMES(k, N) {
                if(minx <= points[k].first && points[k].first <= maxx
                        && miny <= points[k].second && points[k].second <= maxy)
                {
                    pat |= (1<<k);
                }
            }
            cover[i][j] = cover[j][i] = make_pair(pat, (maxx-minx) * (maxy-miny));
            //printf("%d %d %x %d\n", i, j, cover[i][j].first, cover[i][j].second);
        }
    }
    fill_n(memo, 1<<N, -1);
    memo[(1<<N)-1] = 0;
    printf("%d\n", dfs(0));
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
