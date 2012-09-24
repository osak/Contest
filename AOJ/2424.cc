//Name: Kakezan
//Level: 1
//Category: やるだけ
//Note:

/*
 * 問題の操作を行ってNが大きくなることはないのでシミュレーションするだけ．
 */
#include <iostream>
#include <algorithm>

using namespace std;

int search(int n) {
    int right = 0;
    int ord = 1;
    int ans = 0;
    while(n > 0) {
        right += ord * (n % 10);
        ord *= 10;
        n /= 10;
        ans = max(ans, n*right);
    }
    return ans;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int Q;
    cin >> Q;
    while(Q--) {
        int N;
        cin >> N;
        int cnt = 0;
        while(N >= 10) {
            N = search(N);
            ++cnt;
        }
        cout << cnt << endl;
    }
    return 0;
}
