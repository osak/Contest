//Name: Recutangular Searching
//Level: 3
//Category: 累積和,連続区間
//Note: 類題 POJ1964

/*
 * あるマスについて，そのマスを含めてそれより上にいくつ白マスが連続しているかを記憶しておく．
 * すると，1行内のある区間を底辺に持つ長方形の面積は，区間長 * その区間内の最小値で与えられることが分かる．
 *
 * これはスタックを使い，ある高さの区間がいくつ連続しているかを高さの昇順で管理すると効率良く求められる．
 * 1行を左から右になめながら値をpushしていくが，このとき
 * ・スタックトップより大きい値であればそのままpushする．
 * ・スタックトップより小さい値 h' であれば，このマスを含んで h' より高い長方形は作れないため，スタックトップを h' に揃えてしまう．
 *   つまり， h' より小さい値が出てくるまでスタックを巻き戻しながらその個数を数え，最後に h' を同数追加すればよい．
 *   以前にpushした値を起点とする長方形は，巻き戻しの途中で右方向の最大区間長を得られるためここで計算できる．
 * 
 * また， h' を同数追加するという処理は (値, 長さ) のペアを管理するようにすると効率的に処理できる．
 * この処理をした上でのオーダーは，各マスを1回ずつなめる操作でO(N^2)，スタック操作は高々2N回しかpushされず，したがってpopも2N回であるからO(N)．
 * よって全体のオーダーは O(N^2)．
 */
#include <iostream>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

int acc[1024][1001];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(true) {
        int H, W;
        cin >> H >> W;
        if(!H && !W) break;
        for(int i = 0; i < W; ++i) {
            acc[0][i] = 0;
        }
        for(int i = 0; i < H; ++i) {
            string line;
            cin >> line;
            for(int c = 0; c < W; ++c) {
                if(i > 0) acc[i][c] = acc[i-1][c];
                if(line[c] == '*') acc[i][c] = 0;
                else acc[i][c]++;
            }
        }
        int ans = 0;
        for(int r = 0; r < H; ++r) {
            // 番兵
            acc[r][W] = 0;
            // スタックの中身は常に昇順になっている．
            stack<pair<int,int> > stk;
            for(int c = 0; c <= W; ++c) {
                int len = 0;
                const int cur = acc[r][c];
                while(!stk.empty() && stk.top().first >= cur) {
                    len += stk.top().second;
                    const int area = len * stk.top().first;
                    ans = max(ans, area);
                    stk.pop();
                }
                ++len;
                stk.push(make_pair(cur, len));
            }
        }
        cout << ans << endl;
    }
    return 0;
}
