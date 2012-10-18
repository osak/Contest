//Name: Mysterious Onslaught
//Level: 4
//Category: DP,ビット演算
//Note:

/*
 * 状態数は全部で 2^25 だが，これはちょうどメモリ制限の値と等しいため
 * 愚直な探索では解を求められない．
 * この手の問題だと上の行の状態を覚えておいて下の行に伝搬させるのが常套手段だが，
 * この問題でもその手法が使える．
 *
 * この問題で上の行から下の行へ伝搬する状態は，上の行でどのように矩形が置かれていたかである．
 * たとえばある行 r で 1〜3 列目を埋めるように矩形が置かれていた場合，その下の行 r+1 でも
 * 同じように 1〜3 列目を埋めるようにすると，これらはまとめて1個の矩形で表現できるため
 * コストが下がる．
 *
 * ある行について，列 x から右に矩形を伸ばしたとき，その幅は N-x 通り存在する．
 * これを各列について合計すると N=5 のときでも 15 通りであるから，1行を覆う矩形の取り方は
 * 高々 2^15 通り．
 * このうちその行を全滅させる置き方は更に少ないと予測できるので，そのような置き方だけを覚えて
 * 直前の状態として使うと計算量が抑えられる．
 * 実際には N=5 の時で 1024 通りになるので，1行の更新は 2^25 ループ程度で完了できる．
 *
 * 以下のコードではビット演算を使って，矩形の正当性(ちゃんと全てのビットを0にできるか)の判定を高速化している．
 * オーダーは O(2^(N^2)) ．
 */
#include <iostream>
#include <vector>

using namespace std;

const int INF = 30;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    while(true) {
        int N;
        cin >> N;
        if(!N) break;
        vector<int> field(N);
        for(int i = 0; i < N; ++i) {
            int pat = 0;
            for(int j = 0; j < N; ++j) {
                int v;
                cin >> v;
                pat <<= 1;
                pat |= v;
            }
            field[i] = pat;
        }
        // ビット演算で扱いやすくするため，右端を座標 0 として扱う．
        vector<int> myons; // 行にかかるmyon
        for(int c = 0; c < N; ++c) { // 右端の位置
            for(int w = 1; w <= N-c; ++w) {
                int mask = ((1<<w)-1) << c;
                myons.push_back(mask);
                //cout << mask << endl;
            }
        }
        const int M = myons.size();
        // 0: prev
        // 1: cur
        vector<int> valid_pats[2];
        vector<int> dp[2];
        dp[0].resize(1<<M, INF);
        dp[1].resize(1<<M, INF);
        for(int r = 0; r < N; ++r) {
            valid_pats[1].clear();
            fill(dp[1].begin(), dp[1].end(), INF);
            for(int pat = 0; pat < (1<<M); ++pat) {
                int mask = 0;
                for(int i = 0, ord = 1; i < M; ++i, ord <<= 1) {
                    if(pat & ord) mask ^= myons[i];
                }
                if(mask == field[r]) {
                    // Valid pattern
                    int cost = INF;
                    const int bits = __builtin_popcount(pat);
                    if(r != 0) {
                        // コストは
                        //   直前で有効な状態のコスト + 現在のパターンのコスト - 直前と合成する矩形のコスト
                        for(vector<int>::iterator it = valid_pats[0].begin(); it != valid_pats[0].end(); ++it) {
                            cost = min(cost, dp[0][*it] + bits - __builtin_popcount(pat & *it));
                        }
                    } else {
                        cost = bits;
                    }
                    //cout << r << ' ' << pat << ' ' << cost << endl;
                    dp[1][pat] = cost;
                    valid_pats[1].push_back(pat);
                }
            }
            valid_pats[0].swap(valid_pats[1]);
            dp[0].swap(dp[1]);
        }
        int ans = INF;
        for(vector<int>::iterator it = valid_pats[0].begin(); it != valid_pats[0].end(); ++it) {
            ans = min(ans, dp[0][*it]);
        }
        for(int i = 0; i < ans; ++i) {
            cout << "myon";
        }
        cout << endl;
    }
    return 0;
}
