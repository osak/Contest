//Name: JOI Flag
//Level: 4
//Category: 数え上げ,動的計画法,DP,ビットDP
//Note:

/*
 * あり得る全ての旗から、JOIが含まれないものの個数を引けばよい。
 *
 * JOIが含まれないものの個数は、直前N文字を覚えておけばDPで求められるが、単純にJ,O,Iを覚えるのでは
 * 状態数が多くなりすぎてしまう（最大ケースで O(MN 3^M) = 約1.3兆状態）。
 * しかし、JOIが構成されるかどうかは、真上の行でJOという並びが存在しているかどうかのみに依存するため、
 * 1マスについて覚えなければならない情報は「Jがあり、その右にOがあるかどうか」の1bitだけになる。
 * また、JOができたことを判定するためには、直前にJを置いたかどうかを覚えておく必要があるが、これは1bitのみでよい。
 *
 * 以上より、状態数は O(MN 2^M) = 約4億状態になるため、ビットDPで間に合う。
 * 実際には、1のビットが連続することはあり得ないため、状態数は半分以下になる。
 * また、メモリの制約上すべての状態を保持しておくのは難しいので、1マスずつ状態を進めながらバッファを使いまわす必要がある。
 *
 * オーダーは O(MN 2^M)。
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

const int MOD = 100000;

bool solve() {
    int N, M;
    if(!(cin >> N >> M)) return false;
    if(!N && !M) return false;

    vector<string> field(N);
    for(int i = 0; i < N; ++i) {
        cin >> field[i];
    }

    vector<int> dp[2];
    dp[0].resize(1<<(M+1));
    dp[1].resize(1<<(M+1));

    const int MASK = (1<<(M+1))-1;
    vector<int> states[2];
    fill(begin(dp[0]), end(dp[0]), 1);
    states[0].push_back(0);
    int allpat = 1;
    for(int r = 0; r < N; ++r) {
        for(int c = 0; c < M; ++c) {
            const char fc = field[r][c];
            if(fc == '?') {
                allpat *= 3;
                allpat %= MOD;
            }
            fill(begin(dp[1]), end(dp[1]), 0);
            states[1].clear();
            for(int s : states[0]) {
                //cout << r << ' ' << c << ' ' << s << endl;
                const int prev_j = s & 1;
                const int pat = dp[0][s];
                s ^= prev_j;

                // Put J
                if(fc == '?' || fc == 'J') {
                    const int sj = ((s << 1) & MASK) | (1 && (c < M-1));
                    dp[1][sj] += pat;
                    dp[1][sj] %= MOD;
                    states[1].push_back(sj);
                }
                // Put O
                if(fc == '?' || fc == 'O') {
                    const int so = ((s << 1) & MASK) | (prev_j ? 4 : 0);
                    dp[1][so] += pat;
                    dp[1][so] %= MOD;
                    states[1].push_back(so);
                }
                // Put I
                if(fc == '?' || fc == 'I') {
                    if(!(s & (1<<M))) {
                        const int si = (s << 1) & MASK;
                        dp[1][si] += pat;
                        dp[1][si] %= MOD;
                        states[1].push_back(si);
                    }
                }
            }
            sort(begin(states[1]), end(states[1]));
            states[1].erase(unique(begin(states[1]), end(states[1])), end(states[1]));
            dp[0].swap(dp[1]);
            states[0].swap(states[1]);
        }
    }

    const int invalid = accumulate(begin(dp[0]), end(dp[0]), 0, [](int a, int b){return (a+b) % MOD;});
    cout << (allpat + MOD - invalid) % MOD << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
