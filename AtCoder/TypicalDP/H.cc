//Name: ナップザック
//Level: 4
//Category: DP,動的計画法
//Note: Typical DP Contest H

/**
 * 色ごとに区切ってDPを行うことで、種類数制約を簡単に扱うことができる。
 * ある色までを使って dp[w][c] = (合計重さw, 使用した色数の上限cの時の最大価値)
 * が得られているとすると、その次の色の塊を追加したとき
 *   ・新しい色は使わない dp[w][c]
 *   ・新しい色を初めて追加する dp[w][c-1]+v_i
 *   ・すでに新しい色を使っており、さらに追加する dp'[w][c] + v_i
 * の3種類の遷移が可能である。
 * これにしたがって
 *   dp'[w][c] = max(dp[w][c], dp'[w][c] + v_i, dp[w][c-1]+v_i)
 * とすることで、次のDP表が得られる。
 *
 * オーダーはO(NWC)。
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Tag {
    int w, v, c;

    bool operator <(const Tag &other) const {
        if(c != other.c) return c < other.c;
        return w < other.w;
    }
};

typedef vector<Tag>::iterator Iterator;

int W, C;
int dp[10001][51];
int tmp_dp[10001][51];

void step(const Iterator &begin, const Iterator &end) {
    for(int w = 0; w <= W; ++w) {
        for(int c = 0; c <= C; ++c) {
            tmp_dp[w][c] = 0;
        }
    }
    for(Iterator it = begin; it != end; ++it) {
        for(int w = W; w >= it->w; --w) {
            for(int c = 1; c <= C; ++c) {
                tmp_dp[w][c] = max(tmp_dp[w][c], max(tmp_dp[w-it->w][c], dp[w-it->w][c-1]) + it->v);
                //cout << w << ' ' << c << ' ' << tmp_dp[w][c] << endl;
            }
        }
    }
    for(int w = 0; w <= W; ++w) {
        for(int c = 0; c <= C; ++c) {
            dp[w][c] = max(dp[w][c], tmp_dp[w][c]);
        }
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N;
    cin >> N >> W >> C;
    vector<Tag> tags(N);
    for(int i = 0; i < N; ++i) {
        Tag &t = tags[i];
        cin >> t.w >> t.v >> t.c;
    }
    sort(tags.begin(), tags.end());
    for(Iterator it = tags.begin(); it != tags.end(); ) {
        Iterator start = it;
        while(it != tags.end() && it->c == start->c) ++it;
        //cout << "color " << start->c << endl;
        step(start, it);
    }
    
    int ans = 0;
    for(int i = 0; i <= W; ++i) {
        for(int j = 0; j <= C; ++j) {
            ans = max(ans, dp[i][j]);
        }
    }
    cout << ans << endl;
    return 0;
}
