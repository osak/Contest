//Name: Telephone Wire
//Level: 3
//Category: 動的計画法,DP
//Note:

/**
 * 高さは他の電柱と同じ高さにする以外は意味がない。
 * 特に、100より高くする意味はない。
 *
 * 電線を張るときのコストは、直前の電柱までで電線を張るときのコストと、その時の高さだけが分かれば決定できる。
 * このとき、現在の電柱の高さと直前の電柱の高さの組み合わせを全て試すと状態数が多すぎて間に合わない。
 *
 * 現在の電柱の高さをchとして、最小コストを達成したときの直前の電柱高さをp(ch)とする。
 * ここで、ch+1で p(ch+1)≦p(ch) となったとする。
 * このとき、
 * ・p(ch) > ch とすると、p(ch)の最小性と|p(ch)-(ch+1)| ≦ |p(ch)-ch| より、(ch+1)とp(ch)を結んだほうが得であるか、少なくとも結果は変化しない。
 * ・p(ch) < ch のときも同様。
 * ・p(ch) = ch のときは、|p(ch)-1 - ch| ≦ |p(ch)-1 - (ch+1)| より同様。
 * より、矛盾を導くことができる。
 * すなわち、常にp(ch+1) ≧ p(ch)である。
 *
 * オーダーはO(NH)。
 * ただしHは高さの最大値。
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
const LL INF = 1LL << 50;

bool solve() {
    int N, C;
    if(scanf("%d %d", &N, &C) == EOF) return false;
    if(!N && !C) return false;

    static LL dp[2][101];
    int cur = 0;
    fill_n(dp[1^cur], 101, 0);
    int prev_h = 0;
    TIMES(i, N) {
        int h;
        scanf("%d", &h);
        int ph = prev_h, ch = h;
        fill_n(dp[cur], 101, INF);
        while(ch <= 100) {
            LL best_cost = dp[cur^1][ph] + abs(ch-ph)*C;
            while(ph < 100) {
                const LL tmp = dp[cur^1][ph+1] + abs(ch-(ph+1))*C;
                if(tmp < best_cost) {
                    ++ph;
                    best_cost = tmp;
                } else {
                    break;
                }
            }
            best_cost += (ch-h)*(ch-h);
            //printf("%d %lld\n", ch, best_cost);
            dp[cur][ch++] = best_cost;
        }
        cur ^= 1;
        prev_h = h;
    }
    printf("%lld\n", *min_element(dp[1^cur], dp[1^cur]+101));
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
