//Name: Card Game
//Level: 2
//Category: 確率,Probability,全探索
//Note:

/*
 * ゲイツの出す手札の順番は固定し、ジャッキーの出し方を全探索する。
 *
 * オーダーは O(N! ×N)。
 */
#include <iostream>
#include <algorithm>
#include <array>

using namespace std;

void solve() {
    array<int,9> as, bs;
    for(int i = 0; i < 9; ++i) {
        cin >> as[i];
    }
    for(int i = 0; i < 9; ++i) {
        cin >> bs[i];
    }

    int awin = 0;
    int total = 0;
    sort(begin(bs), end(bs));
    do {
        int asum = 0, bsum = 0;
        for(int i = 0; i < 9; ++i) {
            if(as[i] > bs[i]) asum += as[i]+bs[i];
            else bsum += as[i]+bs[i];
        }
        if(asum > bsum) ++awin;
        ++total;
    } while(next_permutation(begin(bs), end(bs)));
    double prob = (double)awin / total;
    cout << prob << ' ' << 1-prob << endl;
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
