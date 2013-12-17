//Name: Landscaping
//Level: 4
//Category: 動的計画法,DP,木DP
//Note:

/**
 * 高さは高々1000通りしかないので、各高さの層に分けて考える。
 * それぞれの層について、上にさらに層が乗っているような関係を考えると、
 * この構造は木になることが容易にわかる。
 * ピークを削除するということはここから葉を削除することと等しい。
 * すると、問題は葉の数がK個以下になるように葉を削除するという問題に変形できる。
 *
 * これは典型的な木DPを使って、
 *   あるノードを以下の葉をk個にするコスト
 *     = min_{S ∈ kの分割}(Σ子i以下の葉をS_i個にするコスト)
 * として書ける。
 * この式も子を一つづつ追加していくDPの形にできて、
 *   j番目の子までで葉をk個にするコスト
 *     = min(j-1番目の子までで葉をs個にするコスト + j番目の子以下の葉をk-s個にするコスト)
 * で計算できる。
 * 最後に、自分自身を消すときのコストを、高さと幅から求める。
 *
 * オーダーはO(N^2 K^2)。
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

const LL INF = 1000000LL * 1000 * 2;

void build(int *heights, int left, int right, int hidx, const vector<int> &height_list, LL *dp) {
    int child_cnt = 0;
    if(hidx+1 < height_list.size()) {
        const int nh = height_list[hidx+1];
        //printf("%d %d %d\n", left, right, nh);
        for(int i = left; i < right; ) {
            if(heights[i] >= nh) {
                int next = i;
                while(next < right && heights[next] >= nh) ++next;
                LL dp_buf[26] = {0};
                build(heights, i, next, hidx+1, height_list, dp_buf);
                LL tmp[26];
                fill_n(tmp, 26, INF);
                for(int k = 25; k >= 0; --k) {
                    TIMES(ck, k+1) {
                        tmp[k] = min(tmp[k], dp[k-ck] + dp_buf[ck]);
                    }
                }
                TIMES(k, 26) {
                    dp[k] = tmp[k];
                }
                ++child_cnt;
                i = next;
            } else {
                ++i;
            }
        }
    }
    dp[0] += static_cast<LL>(height_list[hidx] - (hidx > 0 ? height_list[hidx-1] : 0)) * (right-left);
    /*
    TIMES(k, 26) {
        printf("%d %d %d %lld\n", left, right, k, dp[k]);
    }
    */
}

bool solve() {
    int N, K;
    if(scanf("%d %d", &N, &K) == EOF) return false;
    if(!N && !K) return false;

    static int heights[1000];
    vector<int> height_list;
    TIMES(i, N) {
        scanf("%d", heights+i);
        height_list.push_back(heights[i]);
    }
    sort(height_list.begin(), height_list.end());
    height_list.erase(unique(height_list.begin(), height_list.end()), height_list.end());
    LL dp[26] = {0};
    build(heights, 0, N, 0, height_list, dp);
    LL ans = INF;
    for(int k = 0; k <= K; ++k) {
        ans = min(ans, dp[k]);
    }
    printf("%lld\n", ans);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
