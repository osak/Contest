//Name: Specialized Four-Digit Numbers
//Level: 1
//Category: 数学,やるだけ
//Note:

/*
 * 全ての4桁の数値について，10, 12, 16進法で各桁の和を出すだけ．
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define FOREACH(it,c) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)

int partsum(int n, int base) {
    int res = 0;
    while(n > 0) {
        res += n % base;
        n /= base;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    for(int i = 2992; i <= 9999; ++i) {
        const int s1 = partsum(i, 10);
        const int s2 = partsum(i, 16);
        const int s3 = partsum(i, 12);
        if(s1 == s2 && s2 == s3) {
            cout << i << endl;
        }
    }
    return 0;
}
