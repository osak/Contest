//Name: Distant Galaxy
//Level: 3
//Category: Event driven
//Note:

/**
 * Y座標の範囲だけ決めると、左端を左から順に動かしていったとき、
 * ・横線上に乗っている星が矩形から外れるか
 * ・縦線上に何個星が乗るか
 * を判定することで、矩形状の星の数が求められる。
 * 右端も同様に決定する。
 *
 * 右端が左端を超えないようにすることと、左端はなるべく左端に置いたほうがよいことに注意。
 *
 * オーダーはO(N^3)。
 */
#include <cstdio>
#include <algorithm>
#include <utility>

using namespace std;

typedef long long LL;
typedef pair<LL,LL> P;

bool solve(int CASE) {
    int N;
    scanf("%d", &N);
    if(!N) return false;

    static P ps[100];
    for(int i = 0; i < N; ++i) {
        scanf("%lld %lld", &ps[i].first, &ps[i].second);
    }
    sort(ps, ps+N);

    int res = 0;
    for(int ti = 0; ti < N; ++ti) {
        const LL top = ps[ti].second;
        for(int bi = 0; bi < N; ++bi) {
            const LL bottom = ps[bi].second;
            if(top < bottom) continue;

            // Count stars on horizontal line
            int cnt = 0;
            for(int i = 0; i < N; ++i) {
                if(ps[i].second == top || ps[i].second == bottom) ++cnt;
            }
            res = max(res, cnt);

            // Determine left edge
            int left_max = 0;
            LL left_max_x = 0;
            for(int i = 0; i < N; ) {
                LL x = ps[i].first;
                int to_elim = 0;
                int vert = 0;
                while(i < N && ps[i].first == x) {
                    if(ps[i].second == top || ps[i].second == bottom) {
                        ++to_elim;
                    } else if(bottom < ps[i].second && ps[i].second < top) {
                        ++vert;
                    }
                    ++i;
                }
                if(left_max < cnt + vert) {
                    left_max = cnt + vert;
                    left_max_x = x;
                }
                cnt -= to_elim;
            }
            res = max(res, left_max);

            // Determine right edge
            cnt = left_max;
            for(int i = N-1; i >= 0; ) {
                LL x = ps[i].first;
                if(x == left_max_x) break;
                int to_elim = 0;
                int vert = 0;
                while(i >= 0 && ps[i].first == x) {
                    if(ps[i].second == top || ps[i].second == bottom) {
                        ++to_elim;
                    } else if(bottom < ps[i].second && ps[i].second < top) {
                        ++vert;
                    }
                    --i;
                }
                res = max(res, cnt + vert);
                cnt -= to_elim;
            }
        }
    }
    printf("Case %d: %d\n", CASE, res);
    return true;
}

int main() {
    for(int i = 1; solve(i); ++i) ;
    return 0;
}
