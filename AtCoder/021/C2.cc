//Name: 増築王高橋君
//Level: 4
//Category: 二分探索,貪欲,Greedy
//Note:

/**
 * 「何円以下までなら増築する」という基準にして、このボーダーラインに関して二分探索。
 * このとき、ボーダーラインまでに何回増築できるかは簡単に求めることができる。
 * ボーダーラインちょうどに到達する建物がいくつもある場合、必要なぶんより多く増築してしまうことがあるが、
 * そのときは最後に余分なものを引いて調整する。
 * （余分なものはすべて、ちょうどボーダーラインの金額である）。
 *
 * 等差数列の和の公式を使うとき、先に積を計算するとギリギリでlong longを超えてオーバーフローするので注意。
 * オーダーは O(N log KB)。
 */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
typedef long long LL;

bool solve() {
    int K, N;
    if(!(cin >> K >> N)) return false;
    if(!K && !N) return false;

    vector<pair<LL,LL>> buildings(N);
    for(int i = 0; i < N; ++i) {
        cin >> buildings[i].first >> buildings[i].second;
    }

    LL left = 0, right = 1000000000000LL;
    while(left+1 < right) {
        const LL lim = (left + right) / 2;
        LL buy = 0;
        for(const auto b : buildings) {
            if(lim < b.first) continue;
            LL cnt = (lim - b.first) / b.second + 1;
            buy += cnt;
        }
        if(buy < K) {
            left = lim;
        } else {
            right = lim;
        }
    }

    LL ans = 0;
    LL buy = 0;
    LL max_cost = 0;
    for(const auto b : buildings) {
        if(b.first > right) continue;
        LL cnt = (right - b.first) / b.second + 1;
        LL last = b.first + b.second * (cnt-1);
        max_cost = max(max_cost, last);
        buy += cnt;
        LL s = b.first + last;
        LL c = cnt;
        if(s % 2 == 0) s /= 2;
        else c /= 2;
        ans += s * c;
    }
    ans -= max_cost * (buy - K);
    cout << ans << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
