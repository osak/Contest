//Name: The Secret Number
//Level: 2
//Category: 動的計画法,DP
//Note:

/*
 * あるマスを先頭とする文字列で最大のものは，
 *   ・そこから右に進み，それを先頭とした最大の文字列をくっつける
 *   ・そこから下に進み，それを先頭とした最大の文字列をくっつける
 * のどちらか．
 * ここで大小関係はまず文字列の長さで比較し，長さが同じときは辞書順により決定される．
 * 最大文字列を右下から決定していくとうまくDPに落としこめる．
 * 先頭が0の文字列の扱いに注意．
 *
 * オーダーは各マスをなめるのと，それぞれのマスで文字列の比較・生成が発生するため O(WH(W+H))．
 * 文字列をいちいちコピーして生成せず，次のマスへのポインタだけ保持することもできるが，空間計算量が落ちるだけで
 * 時間計算量には変化がない．
 * (コピーが生じないぶん定数倍高速化は発生する)
 */
#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

inline string& max_one(string &a, string &b) {
    if(a.size() > b.size()) return a;
    if(b.size() > a.size()) return b;
    return a > b ? a : b;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    while(true) {
        int W, H;
        cin >> W >> H;
        if(!W && !H) break;

        vector<string> matrix(H);
        for(int i = 0; i < H; ++i) {
            cin >> matrix[i];
        }
        vector<vector<string> > largest(H, vector<string>(W));
        string ans = "";
        for(int r = H-1; r >= 0; --r) {
            for(int c = W-1; c >= 0; --c) {
                if(isdigit(matrix[r][c])) {
                    string right(""), down("");
                    if(c+1 < W) {
                        right = largest[r][c+1];
                    }
                    if(r+1 < H) {
                        down = largest[r+1][c];
                    }
                    largest[r][c] = string("") + matrix[r][c] + max_one(right, down);
                    if(matrix[r][c] != '0') {
                        ans = max_one(ans, largest[r][c]);
                    }
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
