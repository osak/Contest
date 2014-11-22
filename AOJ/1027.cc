//Name: A Piece of Cake
//Level: 2
//Category: 数学
//Note:

/**
 * cを全て合計すると、1種類のケーキはちょうど(K-1)回だけ足されたことになる。
 * したがって、ΣcをK-1で割ればよい。
 *
 * オーダーは O(K^2)。
 */
#include <iostream>

using namespace std;

bool solve() {
    int K;
    if(!(cin >> K)) return false;
    if(!K) return false;

    int sum = 0;
    for(int i = 0; i < K*(K-1)/2; ++i) {
        int c;
        cin >> c;
        sum += c;
    }
    cout << sum / (K-1) << endl;
    return true;

}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    while(solve()) ;
    return 0;
}
