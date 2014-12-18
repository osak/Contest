//Name: Carry a Cheese
//Level: 2
//Category: 数学,幾何
//Note:

/**
 * 直方体のどれかの面をまっすぐ入口に押しこむように入れるのが最適。
 * このとき、入口に平行な面の対角線の長さが、入口の直径よりも小さければ運び込むことができる。
 * 浮動小数点数を使うと誤差が怖いので、長さを2乗して扱うことで整数で判定する。
 *
 * オーダーは O(N)。
 */
#include <iostream>
#include <algorithm>

using namespace std;

bool solve() {
    long long A, B, C;
    cin >> A >> B >> C;
    if(!A && !B && !C) return false;

    const long long diag = min({A*A+B*B, A*A+C*C, B*B+C*C});
    int N;
    cin >> N;
    while(N--) {
        long long R;
        cin >> R;
        cout << (4*R*R > diag ? "OK" : "NA") << endl;
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
