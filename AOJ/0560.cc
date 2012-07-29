//Name: Planetary Exploration
//Level: 2
//Category: DP,動的計画法,累積和
//Note:

/*
 * J,O,Iそれぞれについて，(0,0)と(r,c)を対角に持つ矩形内の個数を持っておく．
 * (a,b)と(c,d)を対角に持つ矩形内の個数は
 *   acc[c,d] - acc[c,b-1] - acc[a-1,d] + acc[a-1,b-1]
 * として算出できる．
 */
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int acc[3][1000][1000];
int R, C;
int get(int buf[1000][1000], int r, int c) {
    if(r < 0 || r >= R || c < 0 || c >= C) return 0;
    return buf[r][c];
}

void calc_acc(const vector<string> &field, char ch, int buf[1000][1000]) {
    for(int r = 0; r < R; ++r) {
        for(int c = 0; c < C; ++c) {
            buf[r][c] = get(buf, r-1, c) + get(buf, r, c-1) - get(buf, r-1, c-1);
            if(field[r][c] == ch) ++buf[r][c] ;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int K;
    cin >> R >> C >> K;
    vector<string> field(R);
    for(int i = 0; i < R; ++i) {
        cin >> field[i];
    }
    calc_acc(field, 'J', acc[0]);
    calc_acc(field, 'O', acc[1]);
    calc_acc(field, 'I', acc[2]);
    for(int i = 0; i < K; ++i) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        --a; --b; --c; --d;
        for(int j = 0; j < 3; ++j) {
            if(j > 0) cout << ' ';
            cout << get(acc[j], c, d) - get(acc[j], c, b-1) - get(acc[j], a-1, d) + get(acc[j], a-1, b-1);
        }
        cout << endl;
    }
    return 0;
}
