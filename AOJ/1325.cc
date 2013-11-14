//Name: Ginkgo Numbers
//Level: 1
//Category: 数論,やるだけ
//Note:

/**
 * Ginkgo numberは複素数である。
 *
 * 性質2より、与えられた複素数の約数となるためには、絶対値がそれよりも
 * 小さくないといけない。
 * したがって、入力の制約より、-200 ≦ m,n ≦ 200 だけを調べればよい。
 *
 * オーダーはO(N)。
 */
#include <iostream>

using namespace std;

bool solve() {
    int N;
    cin >> N;
    while(N--) {
        int p, q;
        cin >> p >> q;
        const int len = p*p + q*q;
        int cnt = 0;
        for(int m = -200; m <= 200; ++m) {
            if(m*m > len) continue;
            for(int n = -200; n <= 200; ++n) {
                const int len2 = m*m + n*n;
                if(len2 == 0) continue;
                if(len % len2 != 0) continue;
                if((m*p+n*q) % len2 == 0 && (m*q-n*p) % len2 == 0) {
                    ++cnt;
                }
            }
        }
end:
        cout << (cnt==8 ? "P" : "C") << endl;
    }
    return false;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
