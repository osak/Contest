//Name: 連結
//Level: 5
//Category: 文字列,動的計画法,DP
//Note: Typical DP Contest Q

/**
 * 先頭から1文字ずつ追加していくと、すべての文字列を重複なく列挙できる。
 * このうち条件を満たすようなもののみフィルタすることを考える。
 *
 * 使える文字列は最大で8文字なので、ある場所に文字を追加したときにそれが有効かどうかは、最大で
 * 7文字分の先読みをしないと判定できない。
 * したがって、逆向きに考えると、最後に追加した7文字を記憶しておく必要があることが分かる。
 *
 * 文字を追加した時に8文字分のパターンができるが、これが与えられた文字列から構成できるかどうかも
 * 判定する必要がある。
 * （構成できない場合、無効な配列である）
 * ここで使う特徴は、"01/0"と"0/10"を区別しないような特徴でなければならないため、前回の区切り文字からの
 * 経過文字数等では情報量が少なく、正常に機能しない。
 * ここでは、パターン中のどこに区切り文字が入るかを覚えておき、どれかの区切り文字を起点として
 * 末尾までの部分文字列を生成できるときは構成可能であるという事実を用いている。
 *
 * オーダーはO(LW2^(2W))。
 * ただし、Wは与えられた文字列の最大長さ。
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef long long LL;

const LL MOD = 1000000007;

void add(LL &var, LL val) {
    var = (var + val%MOD) % MOD;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N, L;
    cin >> N >> L;
    vector<vector<bool>> termpat(1<<8, vector<bool>(9, false));
    for(int i = 0; i < N; ++i) {
        string patstr;
        cin >> patstr;
        int pat = 0;
        for(char c : patstr) {
            pat <<= 1;
            pat += c-'0';
        }
        const int len = patstr.size();
        termpat[pat][len] = true;
    }

    vector<vector<LL>> dp(1<<7, vector<LL>(1<<8, 0));
    dp[0][1] = 1;
    for(int _ = 0; _ < L; ++_) {
        vector<vector<LL>> next(1<<7, vector<LL>(1<<8, 0));
        for(int pat = 0; pat < 1<<7; ++pat) {
            for(int sep = 0; sep < 1<<8; ++sep) {
                for(int d = 0; d <= 1; ++d) {
                    const int npat = (pat<<1) | d;
                    int nsep = sep << 1;
                    bool terminate = false;
                    for(int len = 1; len <= 8; ++len) {
                        if(nsep & (1<<len)) {
                            const int tail = npat & ((1<<len)-1);
                            if(termpat[tail][len]) {
                                terminate = true;
                                break;
                            }
                        }
                    }
                    if(terminate) nsep |= 1;
                    add(next[npat & ((1<<7)-1)][nsep & ((1<<8)-1)], dp[pat][sep]);
                }
            }
        }
        dp.swap(next);
    }
    LL ans = 0;
    for(int pat = 0; pat < 1<<7; ++pat) {
        for(int sep = 0; sep < 1<<8; ++sep) {
            if(sep & 1) add(ans, dp[pat][sep]);
        }
    }
    cout << ans << endl;
    return 0;
}
