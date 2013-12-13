//Name: Conting Kangaroos is Fun
//Level: 3
//Category: 二分探索,Binary Search
//Note:

/**
 * 数を消すときは、小さい方と大きい方それぞれk個ずつをマッチングさせることのみを考えればよい。
 * マッチング可能なkの値について二分探索をする。
 *
 * ギリギリ消せる組を貪欲にマッチングしていくような方法だと、
 * 4
 * 10 4 2 2
 * や
 * 4
 * 2 4 5 6
 * のようなケースでWAになる。
 *
 * オーダーはO(N log N)。
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool solve() {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    vector<int> v(N);
    for(int i = 0; i < N; ++i) {
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    int left = 0, right = N-1;
    while(left+1 < right) {
        const int m = (left+right) / 2;
        const int k = N - m;
        bool ok = true;
        if(k < m) {
            ok = false;
        } else {
            for(int i = 0; i < m; ++i) {
                if(v[i]*2 > v[k+i]) {
                    ok = false;
                    break;
                }
            }
        }
        if(ok) {
            left = m;
        } else {
            right = m;
        }
    }
    cout << N-left << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
