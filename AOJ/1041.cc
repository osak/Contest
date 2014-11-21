//Name: Kyudo: A Japanese Art of Archery
//Level: 1
//Category: やるだけ
//Note:

/**
 * 問題文の通りに処理し、合計するだけ。
 */
#include <iostream>
#include <vector>

using namespace std;

bool solve() {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    int sum = 0;
    for(int i = 0; i < N/4; ++i) {
        int a;
        cin >> a;
        sum += a;
    }
    cout << sum << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
