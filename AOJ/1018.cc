//Name: Cheating on ICPC
//Level: 2
//Category: 貪欲法,Greedy
//Note:

/*
 * 単に一番かかる時間の短いものから解いていけばよい．
 * ソートした状態から要素を入れ替える必要のないことは証明可能．
 */
#include <iostream>
#include <algorithm>

using namespace std;

int arr[100];
int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int N;
    while(cin >> N) {
        for(int i = 0; i < N; ++i) {
            cin >> arr[i];
        }
        sort(arr, arr+N);
        unsigned long long ans = 0;
        unsigned long long acc = 0;
        for(int i = 0; i < N; ++i) {
            acc += arr[i];
            ans += acc;
        }
        cout << ans << endl;
    }
    return 0;
}
