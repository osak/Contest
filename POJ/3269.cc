//Name: Building A New Barn
//Level: 4
//Category: 数学,マンハッタン距離
//Note:

/**
 * X方向とY方向は独立に考えられる。
 *
 * 点を右に動かす時、この点より右にある点が左にある点より多ければコストは減り、少なければ増える。
 * したがって、X座標が中央値をとるときにコストは最小となる。
 * Nが偶数のときは中央値が2つあるが、そのときはこれらの間のどの座標でもよい。
 *
 * 設置可能な幅が2以上あるときには、隣り合った牛がいないという条件より、必ずbarnを設置できる。
 * 幅が1のときは候補地に牛がいる場合があるが、そのときは上下左右を見る。
 *
 * オーダーはO(N log N)。
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

typedef long long LL;

const int MAX = 20200;

pair<int,int> cows[10000]; // (y, x)
int xs[10000], ys[10000];

pair<int,int> mid_range(int *xs, int N) {
    sort(xs, xs+N);
    pair<int,int> res(xs[N/2], xs[N/2]);
    if(N % 2 == 0) {
        res.first = xs[N/2-1];
    }
    return res;
}

LL calc(int x, int y, int N) {
    LL res = 0;
    TIMES(i, N) {
        res += abs(x-cows[i].first) + abs(y-cows[i].second);
    }
    return res;
}

bool solve() {
    int N;
    if(scanf("%d", &N) == EOF) return false;
    if(!N) return false;

    TIMES(i, N) {
        scanf("%d %d", &cows[i].first, &cows[i].second);
        xs[i] = cows[i].first;
        ys[i] = cows[i].second;
    }
    const pair<int,int> rx = mid_range(xs, N);
    const pair<int,int> ry = mid_range(ys, N);
    int area = (rx.second - rx.first + 1) * (ry.second - ry.first + 1);
    TIMES(i, N) {
        if(rx.first <= cows[i].first && cows[i].first <= rx.second) {
            if(ry.first <= cows[i].second && cows[i].second <= ry.second) {
                --area;
            }
        }
    }
    LL cost = calc(rx.first, ry.first, N);

    if(area == 0) {
        const int DX[] = {1, 0, -1, 0};
        const int DY[] = {0, -1, 0, 1};
        cost = 1LL << 50;
        TIMES(dir, 4) {
            const int x = rx.first + DX[dir];
            const int y = ry.first + DY[dir];
            const LL tmpcost = calc(x, y, N);
            if(tmpcost == cost) {
                ++area;
            } else if(tmpcost < cost) {
                cost = tmpcost;
                area = 1;
            }
        }
    }
    printf("%lld %d\n", cost, area);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
