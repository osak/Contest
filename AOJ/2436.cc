//Name: Card
//Level: 4
//Category: 動的計画法,DP
//Note:

/*
 * 基本的には，ある箇所に1枚カードを置いたとき，そのような置き方が何通りあるかを数え上げて足していけばよい．
 * たとえば12を置くとき， ...12，..12.，.12...，12... のような置き方が考えられる．
 * (ここで.は1桁に対応する)
 * それぞれにマッチするパターン数をn1,n2,n3,n4とすると，12をどこかに置くことで合計値が
 *   12*n1 + 120*n2 + 1200*n3 + 12000*n4
 * だけ増えることが分かる．これを全てのカードについて行なう．
 *
 * 置き方を数え上げるとき，左半分と右半分に分けて考える．
 * leading-zeroを考えないとき，左側は任意に長くできるので左側に置けるカードの枚数Mに対して
 *   Σ(0 ≦ m ≦ M) Perm(M, m)
 * だけの置き方がある(ここでmは左側に実際に置くカードの枚数を意味することになる)．
 * 右側は長さが固定されているため，DPによってパターン数を数える必要がある．
 *
 * dp[j][k]がカードをj枚使って長さkの数を作るパターン数だとすると，ここに長さlのカードを加えたとき
 * カード枚数はj+1, 長さはk+lになる．
 * このパターン数は，j枚が並んでいるところに任意にカードを挿入することと等しいから，結局
 *   dp[j+1][k+l] += dp[j][k] * j
 * として更新することになる．
 *
 * 右側で使う枚数が決まれば，先に挙げた式によって左側の置き方も決まるので，あとは合計すればよい．
 * leading-zeroに対しては，leading-zeroを考えずに計算したあと，先頭を0に固定したものと考えて
 * この0を抜いた状態で同様に数え上げ，先の計算結果から引けばよい．
 */
#include <iostream>
#include <vector>

using namespace std;

typedef unsigned long long ULL;
const int MOD = 1000000007;
ULL dp[4][256][800]; // dp[i][j][k] = 長さi+1のカードを1枚抜いて，j枚使って長さkの列を作る場合の数
ULL factorial[201];
ULL perm[201]; // perm[i] = iP1 + iP2 + ... + iPi

inline int digit_len(int n) {
    if(0 <= n && n <= 9) return 1;
    else if(10 <= n && n <= 99) return 2;
    else if(100 <= n && n <= 999) return 3;
    else if(1000 <= n && n <= 9999) return 4;
    throw "Invalid";
}

void calc(const vector<int> &nums, int idx) {
    for(int j = 0; j <= 200; ++j) {
        for(int k = 0; k <= 799; ++k) {
            dp[idx][j][k] = 0;
        }
    }
    dp[idx][0][0] = 1;
    for(int len = 1; len <= 4; ++len) {
        for(int i = 0; i < nums[len]; ++i) {
            // 干渉を防ぐため後ろから更新していく．
            for(int j = 200; j >= 1; --j) {
                for(int k = 799; k >= len; --k) {
                    // 長さlenのものを1枚追加すると，dp[idx][j-1][k-len]の並べ方それぞれに対して
                    // j箇所の挿入箇所がある．
                    // したがってdp[idx][j][k]はdp[idx][j-1][k-len]*jだけ増える．
                    dp[idx][j][k] += dp[idx][j-1][k-len] * j;
                    dp[idx][j][k] %= MOD;
                    //cout << idx << ' ' << j << ' ' << k << ' ' << dp[idx][j][k] << endl;
                }
            }
        }
    }
}

ULL solve(vector<int> &nums, const vector<int> &sums) {
    int N = 0;
    int max_len = 0;
    for(int len = 0; len <= 4; ++len) {
        N += nums[len];
        max_len += nums[len]*len;
    }
    for(int i = 1; i <= 4; ++i) {
        if(nums[i] > 0) {
            nums[i]--;
            calc(nums, i-1);
            nums[i]++;
        }
    }
    ULL ans = 0;
    for(int uselen = 1; uselen <= 4; ++uselen) {
        if(nums[uselen] > 0) {
            ULL ord = 1;
            for(int pos = 0; pos <= max_len-uselen; ++pos) {
                // 右に何枚使うか
                for(int right_cnt = 0; right_cnt <= N-1; ++right_cnt) {
                    ULL right = dp[uselen-1][right_cnt][pos];
                    ans += sums[uselen]*ord % MOD * right % MOD * perm[N-right_cnt-1] % MOD;
                    ans %= MOD;
                    //cout << ans << endl;
                }
                ord *= 10;
                ord %= MOD;
            }
        }
    }
    return ans;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    factorial[0] = 1;
    for(int i = 1; i <= 200; ++i) {
        factorial[i] = factorial[i-1] * i;
        factorial[i] %= MOD;
    }
    perm[0] = 1;
    for(int i = 1; i <= 200; ++i) {
        ULL fact = 1;
        perm[i] = 1; // iP0
        for(int j = i; j >= 1; --j) {
            fact *= j;
            fact %= MOD;
            perm[i] += fact;
            perm[i] %= MOD;
        }
        //cout << "perm[" << i << "]=" << perm[i] << endl;
    }
    vector<int> nums(5, 0);
    vector<int> sums(5, 0);
    bool have_zero = false;
    int N;
    cin >> N;
    for(int i = 0; i < N; ++i) {
        int a;
        cin >> a;
        if(a == 0) have_zero = true;
        const int len = digit_len(a);
        nums[len]++;
        sums[len] += a;
    }
    ULL ans = solve(nums, sums);
    if(have_zero) {
        nums[1]--;
        ULL leading_zero = solve(nums, sums);
        ans = ans + MOD - leading_zero;
        ans %= MOD;
    }
    cout << ans << endl;
    return 0;
}
