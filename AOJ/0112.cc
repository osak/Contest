//Name: A Milk Shop
//Level: 1
//Category: やるだけ
//Note:

/*
 * なるべく小さい数を前に持ってきたほうが良いことは直感的に分かり，証明できる．
 *
 * インデックス i,j (i ≦ j) で，[i]にa，[j]にb (a ≦ b)を置くとする(すなわちソート済みである)．
 * このときaとbを入れ換えたほうが良いというのは，すなわち (N-i)a + (N-j)b > (N-i)b + (N-j)a が成立するということである．
 * この式を移項して整理すると {(N-i)-(N-j)}(a-b) > 0．
 * ここで i ≦ j であるから (N-i)-(N-j) ≧ 0， a ≦ b であるから (a-b) ≦ 0．
 * よってaとbを入れ換えたほうがいいということはあり得ない．
 *
 * 最大ケースで答えが32bitに収まらないことに注意．
 * オーダーはソートが最大だから O(N log N)．
 */
#include <iostream>
#include <algorithm>

using namespace std;

int arr[10000];
int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    while(true) {
        int N;
        cin >> N;
        if(!N) break;
        for(int i = 0; i < N; ++i) {
            cin >> arr[i];
        }
        sort(arr, arr+N);
        long long ans = 0;
        long long acc = 0;
        for(int i = 0; i < N; ++i) {
            ans += acc;
            acc += arr[i];
        }
        cout << ans << endl;
    }
    return 0;
}
