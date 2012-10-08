//Name: Split Up!
//Level: 3
//Category: 全探索,DP
//Note:

/*
 * 全ての選び方を試す．
 * このとき，ある選び方が2進数 pat で与えられているとき，これに対する攻撃力の合計値は
 * patのビットをどれか1つ落としたときの合計値に，落としたビットに対応する攻撃力を加えたものとなる．
 * このとき，パターンを2進数で昇順に試していけばビットを1つ落としたパターンは必ず pat より前に試しているので，
 * これらの値を記憶しておくことで簡単に計算できるようになる．
 *
 * 落とすビットはどれでもよいが，最下位ビットが pat&(-pat) で得られるのでここではこれを使っている．
 *
 * オーダーは O(2^N)．
 * 愚直に各パターンについて合計値を求めると O(N*2^N) であるから高速化されている．
 */
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int arr[20];
int pos_of[1<<20];
int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    for(int i = 0; i < 20; ++i) pos_of[1<<i] = i;
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        int sum = 0;
        for(int i = 0; i < N; ++i) {
            cin >> arr[i];
            sum += arr[i];
        }
        int ans = 100000000;
        vector<int> memo(1<<N, 0);
        for(int pat = 1; pat < (1<<N); ++pat) {
            const int prev = pat&~(pat&-pat);
            const int suma = memo[prev] + arr[pos_of[pat&-pat]];
            const int sumb = sum - suma;
            ans = min(ans, abs(suma-sumb));
            memo[pat] = suma;
        }
        cout << ans << endl;
    }
    return 0;
}
