//Name: IOI Manju
//Level: 2
//Category: 動的計画法,DP
//Note: 

/**
 * 饅頭は高いものから詰めていけばよいことは明らか。
 * したがって詰め方は関係なく、（選んだ箱の総容量分の饅頭の価格）-（選んだ箱のコスト）を最大化する問題になるから、
 * ある容量を実現するためのコストが計算できればよい。
 * これは0-1ナップサック問題であるが、入れる饅頭の個数に対して容量がオーバーしてもよいことから「最低でも容量cを実現するためのコスト」と
 * 読みかえると実装しやすい。
 *
 * オーダーは O(NM)。
 */
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template <typename T>
struct Maybe {/*{{{*/
    T val;
    bool valid;

    Maybe() : valid(false) {}
    Maybe(T &t) : val(t), valid(true) {}

    T& operator =(const T &rv) {
        val = rv;
        valid = true;
        return val;
    }

    operator T() {
        return valid ? val : T();
    }

    template<typename Cond>
    void update(const T &v, Cond cond) {
        if(!valid || cond(v, val)) {
            val = v;
            valid = true;
        }
    }

    void update(const T &v) {
        update(v, less<T>());
    }
};/*}}}*/

bool solve(bool first) {
    int M, N;
    if(!(cin >> M >> N)) return false;

    vector<long long> ms(M);
    for(int i = 0; i < M; ++i) {
        cin >> ms[i];
    }
    sort(begin(ms), end(ms), greater<long long>());
    for(int i = 1; i < M; ++i) {
        ms[i] += ms[i-1];
    }

    vector<Maybe<long long>> dp(M+1);
    dp[0] = 0;
    for(int _ = 0; _ < N; ++_) {
        int c, e;
        cin >> c >> e;
        for(int i = M; i >= 0; --i) {
            const int prev = max(0, i-c);
            if(dp[prev].valid) dp[i].update(dp[prev] + e);
        }
        for(int i = M-1; i >= 0; --i) {
            if(dp[i+1].valid) dp[i].update(dp[i+1]);
        }
    }
    long long ans = 0;
    for(int i = 0; i <= M; ++i) {
        if(dp[i].valid) {
            ans = max(ans, (i > 0 ? ms[i-1] : 0) - dp[i]);
        }
    }
    cout << ans << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    bool first = true;
    while(solve(first)) {
        first = false;
    }
    return 0;
}
