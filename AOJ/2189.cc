//Name: Addition Game
//Level: 3
//Category: 数学,Math
//Note:

/*
 * 桁数が1つ減るとき、全体の合計は変化しない。
 * 桁数が変化しないとき、全体の合計は9だけ減る。
 * したがって、どのような順序で操作を行っても結果は常に同じになり、
 * ・桁数の減る操作が |S| - 1回
 * ・桁数の減らない操作が floor((Σs_i - 1) / 9) 回
 * 発生する。
 *
 * オーダーは O(|S|)。
 */
#include <iostream>
#include <string>

using namespace std;

void solve() {
    string s;
    cin >> s;

    int sum = 0;
    for(char c : s) {
        sum += c - '0';
    }
    int check = (int)s.size()-1 + (sum-1)/9;
    cout << (check % 2 ? "Fabre" : "Audrey") << " wins." << endl;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    int N;
    cin >> N;
    while(N--) solve();
    return 0;
}
