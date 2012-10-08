//Name: Split Up!
//Level: 2
//Category: 全探索
//Note:

/*
 * 全ての分け方を試せばよい．
 *
 * オーダーは O(N*2^N)．
 */
#include <iostream>
#include <algorithm>

using namespace std;

int arr[20];
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
        int ans = 100000000;
        for(int pat = 0; pat < (1<<N); ++pat) {
            int suma = 0, sumb = 0;
            for(int i = 0; i < N; ++i) {
                if(pat & (1<<i)) suma += arr[i];
                else sumb += arr[i];
            }
            ans = min(ans, abs(suma-sumb));
        }
        cout << ans << endl;
    }
    return 0;
}
