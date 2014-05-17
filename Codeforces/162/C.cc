//Name: Choosing Balls
//Level: 4
//Category: 動的計画法,DP
//Note:

/**
 * オーダーを無視して考えると、あるインデックスiで実現できる最大値についてDPすればよく、
 *   dp[i] = max(dp[color[j] == color[i]] + a * v[i], dp[color[j] != color[i]] + b * v[i])
 * となる。
 * これは単純に実装すると O(N^2) になる。
 *
 * 上のDPの肝は、aを使った更新とbを使った更新のそれぞれで、max dp[j] がどうなるかという点である。
 * これは、色ごとに達成できたmaxを保持しておくようにすると
 * ・max dp[color[j] == color[i]] は max[color[i]] と等しい
 * ・max dp[color[j] != color[i]] は
 *   ・その時点で最大のスコアを達成している色がcolor[i]の場合、2位の色（同着含む）
 *   ・それ以外の場合、1位の色
 * となる。
 * したがって、更新時に1位の色と2位の色を管理しておくことで、O(N)で解が求められるようになる。
 *
 * オーダーは O(NQ)。
 */
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

typedef long long LL;
const LL INF = 100000LL * 100000 * 100000 * 2;

void update(LL color, LL value, vector<LL> &best, LL &best_color, LL &second_best_color) {
    if(value > best[color]) {
        if(value > best[best_color]) {
            if(best_color != color) {
                second_best_color = best_color;
            }
            best_color = color;
        } else if(value > best[second_best_color]) {
            assert(color != best_color);
            second_best_color = color;
        }
        best[color] = value;
    }
}

bool solve() {
    int N, Q;
    if(!(cin >> N >> Q)) return false;
    if(!N && !Q) return false;

    vector<LL> vs(N);
    vector<LL> cs(N);
    for(int i = 0; i < N; ++i) {
        cin >> vs[i];
    }
    for(int i = 0; i < N; ++i) {
        cin >> cs[i];
    }
    while(Q--) {
        LL a, b;
        cin >> a >> b;
        vector<LL> best(N+1, -INF);
        best[0] = 0;
        LL best_color = 0, second_best_color = 0;
        for(int i = 0; i < N; ++i) {
            const LL pb = best_color;
            const LL psb = second_best_color;
            if(best[cs[i]] > -INF) {
                update(cs[i], best[cs[i]] + a * vs[i], best, best_color, second_best_color);
            }
            if(pb != cs[i]) {
                update(cs[i], best[pb] + b * vs[i], best, best_color, second_best_color);
            }
            if(psb != cs[i]) {
                update(cs[i], best[psb] + b * vs[i], best, best_color, second_best_color);
            }
        }
        cout << *max_element(best.begin(), best.end()) << endl;
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
