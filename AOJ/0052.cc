//Name: Factorial II
//Level: 1
//Category: 数論
//Note:

/*
 * 10は2*5でしか生成されない。
 * 階乗の中にある2の数は5の数より十分に多いので、5の数を数えればよい。
 */
#include <iostream>

using namespace std;

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;
        int cnt = 0;
        for(int i = 1; i <= N; ++i) {
            int n = i;
            while(n > 0 && n % 5 == 0) {
                ++cnt;
                n /= 5;
            }
        }
        cout << cnt << endl;
    }
    return 0;
}
