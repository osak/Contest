//Name: Cosmic Tables
//Level: 2
//Category: シミュレーション,やるだけ
//Note: Codeforces #137

/*
 * 行の入れ替え，列の入れ替えはインデックスだけを入れ替えればよい．
 * 愚直に全要素をswapしてもギリギリ間に合うとの噂もある(試してない)．
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int table[1024][1024];
int row[1024], col[1024];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N, M, K;
    cin >> N >> M >> K;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            cin >> table[i][j];
        }
    }
    cin.ignore();
    for(int i = 0; i < N; ++i) row[i] = i;
    for(int i = 0; i < M; ++i) col[i] = i;
    while(K--) {
        char c;
        int x, y;
        cin >> c >> x >> y;
        --x; --y;
        if(c == 'c') {
            swap(col[x], col[y]);
        } else if(c == 'r') {
            swap(row[x], row[y]);
        } else if(c == 'g') {
            cout << table[row[x]][col[y]] << endl;
        }
    }
    return 0;
}
