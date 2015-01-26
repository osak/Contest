//Name: ニコニコ文字列
//Level: 2
//Category: 文字列,組み合わせ
//Note: 

/**
 * 25が連続している区間では、その区間内で始点と終点を任意に取ることで、有効な部分文字列が取れる。
 * このような部分文字列は、25がN個連続しているとき、comb(N, 2) + N個存在する。
 *
 * オーダーは O(|S|)。
 */
#include <iostream>
#include <string>

using namespace std;

bool solve(bool first) {
    string s;
    if(!(cin >> s)) return false;
    int start = -1;
    long long ans = 0;
    const int N = s.size();

    char prev = '1';
    for(int i = 0; i < N; ++i) {
        if(prev == '2' && s[i] == '5') {
            // Go ahead
        } else if(prev == '5' && s[i] == '2') {
            // Go ahead
        } else if(start != -1) {
            // Terminal
            long long cnt = (i - start) / 2;
            ans += cnt * (cnt-1) / 2 + cnt;
            start = -1;
        }
        if(start == -1) {
            if(s[i] == '2') {
                start = i;
            }
        } 
        prev = s[i];
    }
    if(start != -1) {
        // Terminal
        long long cnt = (N - start) / 2;
        ans += cnt * (cnt-1) / 2 + cnt;
    }

    cout << ans << endl;

    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    bool first = true;
    while(solve(first)) {
        first = false;
    }
    return 0;
}
