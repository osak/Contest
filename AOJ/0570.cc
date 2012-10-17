//Name: Zig-Zag Numbers
//Level: 4
//Category: 動的計画法,DP,Digit DP
//Note:

/*
 * 10進表記のある数 ABCDE が M で割り切れるとは，
 *   A*10000 + B*1000 + C*100 + D*10 + E
 * が M で割り切れるということである．
 * この各位の値をあらかじめ M で剰余を取っておくと，先頭から数字を1桁づつ決めていって
 * 1の位に到達したときにこの剰余の合計が0であれば割り切れると判定できる．
 * また，取り得る最小値と最大値が決められているので，先頭から1桁ずつ決めていくときには
 * それまでに下限/上限と同じ数値しか使っていないかを覚えておき，もしもそうであるなら
 * その桁の範囲は下限/上限の対応する桁に縛られる．
 *
 * このように考えると，ある桁を決めるときに使われる状態は
 * ・上限に縛られているか
 * ・下限に縛られているか
 * ・直前の桁は何か
 * ・選ぶべき数字は直前の桁より大きいか小さいか
 * ・何桁目か
 * ・これまでの合計値(mod M)はいくらか
 * である．
 * ただし，これを全て状態として使うと 2*2*10*2*501*500 = 約20M となり，int型ではオーバーフローしてしまうので
 * short型を使う必要がある．
 *
 * 以下のプログラムでは，選ぶべき数字の大小を列の関数として表現し，2通り試行することで空間計算量を落としている．
 *
 * オーダーは O(M log B)．
 * ただし定数項は 2*2*2*10*10 と非常に大きい．
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef short T;
const int MOD = 10000;

bool even_is_up;
inline bool up_turn(int col) {
    bool even = (col & 1) == 0;
    return even_is_up ? even : !even;
}

// 各位の M による MOD．
// mod_of[0]が1の位，mod_of[1]が10の位……
int mod_of[501];
int M;

// memo[high_limited][low_limited][prev_digit][column][acc]
T memo[2][2][16][512][500];
vector<int> low_digits, high_digits;
int dfs(int col, int high_limited, int low_limited, int prev, int acc) {
    if(col == -1) return acc == 0;
    // 最初の桁判定
    // 本当はもうひとつ変数を渡すのがきれい？
    bool first_digit = (prev < 0 || prev >= 10);
    T dmy = -1;
    T &res =  first_digit ? dmy : memo[high_limited][low_limited][prev][col][acc];
    //cout << "come " << col << ' ' << prev << ' ' << acc << ": res = " << res << endl;
    if(res < 0) {
        res = 0;
        // 取り得る上限・下限の設定
        int low = low_limited ? low_digits[col] : 0;
        int high = high_limited ? high_digits[col] : 9;
        // 最初の桁は 0 を使わない
        if(first_digit) low = max(low, 1);
        if(up_turn(col)) {
            low = max(low, prev+1);
        } else {
            high = min(high, prev-1);
        }
        for(int digit = low; digit <= high; ++digit) {
            int next_hl = high_limited && (digit == high_digits[col]);
            int next_ll = low_limited && (digit == low_digits[col]);
            //cout << col << ' ' << high_limited << ' ' << low_limited << ' ' << acc << ": choose " << digit << endl;
            res += dfs(col-1, next_hl, next_ll, digit, (acc+mod_of[col]*digit) % M);
            res %= MOD;
        }
    }
    return res;
}

void clear_memo() {
    const int nelems = sizeof(memo) / sizeof(T);
    fill_n((T*)memo, nelems, -1);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    string A, B;
    cin >> A >> B >> M;

    mod_of[0] = 1 % M;
    for(int i = 1; i <= 500; ++i) {
        mod_of[i] = (mod_of[i-1]*10) % M;
    }
    for(string::reverse_iterator it = A.rbegin(); it != A.rend(); ++it) {
        low_digits.push_back(*it - '0');
    }
    for(string::reverse_iterator it = B.rbegin(); it != B.rend(); ++it) {
        high_digits.push_back(*it - '0');
    }
    for(int i = 0; i < (int)B.size()-(int)A.size(); ++i) {
        low_digits.push_back(0); // sentinel
    }
    const int low_ord = (int)A.size()-1;
    const int high_ord = (int)B.size()-1;
    int res = 0;
    for(int step = 0; step < 2; ++step) {
        //cout << "step " << step << endl;
        even_is_up = (step == 0);
        clear_memo();
        for(int col = high_ord; col >= low_ord; --col) {
            if(col == 0 && step == 1) break; // 1桁の数の二重カウント防止
            bool low_limited = (col == low_ord);
            bool high_limited = (col == high_ord);
            int prev = up_turn(col) ? -1 : 10;
            res += dfs(col, high_limited, low_limited, prev, 0);
            res %= MOD;
        }
    }
    cout << res << endl;
    return 0;
}
