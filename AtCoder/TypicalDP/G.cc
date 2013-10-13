//Name: 辞書順
//Level: 4
//Category: 文字列,辞書順最小,DP,動的計画法
//Note: Typical DP Contest G

/**
 * 辞書順最小を探索するには、先頭から1文字ずつ決めていき、
 * 「それ以降で何通りの可能性があるか」を見ていく。
 *
 * この問題では、文字S[i]を使い、次に文字cを使うとき、cの場所はS[i]の後で
 * 一番左側のもののみ考えればよい。
 * この前提により、S[i]を使うことを確定した後のパターン数は
 *   dp[i] = Σ dp[next_pos[i][c]]
 * として表すことができる。
 *
 * 復元時は、使う文字を
 *   c = argmax(Σ_(k<=c)dp[next_pos[i][k]] < K)
 * によって決め、
 *   i = next_pos[i][c]
 *   K -= Σ_(k<=c)dp[next_pos[i][k]]+1
 * とすればよい。
 * Kから余分に1引いているのは、任意の場所で打ち切りが可能なためである。
 *
 * オーダーはO(NC)。
 * ただしCはアルファベットの個数。
 */
#include <iostream>
#include <string>
#include <utility>
#include <algorithm>

using namespace std;

typedef unsigned long long LL;

const LL MAX = 1000000000000000000LL;
LL dp[1000001];
bool visited[1000001];
int next_pos[1000001][26];
string S;

LL calc(int pos) {
    const int N = S.size();
    if(pos == N+1) return 0;
    if(visited[pos]) return dp[pos];
    visited[pos] = true;

    dp[pos] = (pos == 0) ? 0 : 1;
    for(int c = 0; c < 26; ++c) {
        dp[pos] += calc(next_pos[pos][c]);
        if(dp[pos] > MAX) {
            dp[pos] = MAX;
        }
    }
    return dp[pos];
}

int main() {
    LL K;
    cin >> S >> K;
    const int N = S.size();
    fill_n(visited, N, false);
    for(int i = N; i >= 0; --i) {
        int sc = (i == N) ? -1 : S[i-1+1]-'a';
        for(int c = 0; c < 26; ++c) {
            if(sc == c) {
                next_pos[i][c] = i+1;
            } else {
                const int prev = (i == N) ? N+1 : next_pos[i+1][c];
                next_pos[i][c] = prev;
            }
        }
    }
    /*
    for(int i = 0; i <= N; ++i) {
        for(int c = 0; c < 26; ++c) {
            cout << next_pos[i][c] << ' ';
        }
        cout << endl;
    }
    cout << calc(0) << endl;
    cout << calc(1) << endl;
    cout << calc(2) << endl;
    */
    // To avoid stack overflow
    for(int i = N; i >= 0; --i) {
        calc(i);
    }
    if(calc(0) < K) {
        cout << "Eel" << endl;
    } else {
        string res;
        int pos = 0;
        while(pos < N+1 && K > 0) {
            LL acc = 0;
            for(int c = 0; c < 26; ++c) {
                LL nacc = acc + calc(next_pos[pos][c]);
                if(nacc >= K) {
                    res += c+'a';
                    pos = next_pos[pos][c];
                    K -= acc+1;
                    break;
                }
                acc = nacc;
            }
        }
        cout << res << endl;
    }
    return 0;
}
