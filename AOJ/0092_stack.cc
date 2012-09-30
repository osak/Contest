//Name: Square Searching
//Level: 2
//Category: 累積和,連続区間
//Note: 類題 POJ1964

/*
 * あるマスについて，そのマスを含めてそれより上にいくつ白マスが連続しているかを記憶しておく．
 * すると，大きさ s の正方形ができるためには，1行の中で s 以上の値が s 個以上連続していればよいことが分かる．
 *
 * これはスタックを使い，ある高さの区間がいくつ連続しているかを高さの昇順で管理すると求められる．
 * 1行を左から右になめながら値をpushしていくが，このとき
 * ・スタックトップより大きい値であればそのままpushする．
 * ・スタックトップより小さい値 s' であれば，このマスを含んで s' より大きい正方形は作れないため，スタックトップを s' に揃えてしまう．
 *   つまり， s' より小さい値が出てくるまでスタックを巻き戻しながらその個数を数え，最後に s' を同数追加すればよい．
 *   以前にpushした値が正方形を構成できるかどうかは，巻き戻しの途中で個数と値を比べることで判定できる．
 * 
 * また， s' を同数追加するという処理は (値, 長さ) のペアを管理するようにすると効率的に処理できる．
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
        int N;
        cin >> N;
        if(!N) break;
        for(int i = 0; i < N; ++i) {
            acc[0][i] = 0;
        }
        for(int i = 0; i < N; ++i) {
            string line;
            cin >> line;
            for(int c = 0; c < N; ++c) {
                if(i > 0) acc[i][c] = acc[i-1][c];
                if(line[c] == '*') acc[i][c] = 0;
                else acc[i][c]++;
            }
        }
        int ans = 0;
        for(int r = 0; r < N; ++r) {
            // 番兵
            acc[r][N] = 0;
            // スタックの中身は常に昇順になっている．
            stack<pair<int,int> > stk;
            for(int c = 0; c <= N; ++c) {
                int len = 0;
                const int cur = acc[r][c];
                while(!stk.empty() && stk.top().first >= cur) {
                    len += stk.top().second;
                    if(len >= stk.top().first) {
                        ans = max(ans, stk.top().first);
                    }
                    stk.pop();
                }
                ++len;
                if(len >= cur) {
                    ans = max(ans, cur);
                }
                stk.push(make_pair(cur, len));
            }
        }
        cout << ans << endl;
    }
    return 0;
}
