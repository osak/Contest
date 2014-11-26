//Name: Carpet
//Level: 2
//Category: ヒストグラム,矩形数え上げ
//Note:

/**
 * x方向に見ていくと、ヒストグラムを何枚の矩形で覆えるかという問題になる。
 * 枚数を最小化するためには、y座標を固定してx方向にスキャンし、連続している区間を1枚のカーペットで覆った上で
 * y方向に同じ長さのカーペットが隣接していればマージする、という操作を行えばよいことがわかる。
 *
 * ナイーブに実装するとO(AN)かかるが、現在の高さと、その高さが終わったときにどの高さに復帰するかという履歴をスタックでもつことにより、
 * y座標が一気に2以上変化する箇所もまとめて扱うことができる。
 * オーダーは O(N)。
 */
#include <iostream>
#include <stack>

using namespace std;

bool solve() {
    int N;
    if(!(cin >> N)) return false;

    stack<int> stk;
    int ans = 0;
    for(int i = 0; i < N; ++i) {
        int a;
        cin >> a;
        while(stk.size() > 0 && stk.top() > a) {
            ++ans;
            stk.pop();
        }
        if(stk.size() == 0 || stk.top() != a) stk.push(a);
    }
    ans += stk.size();
    cout << ans << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
