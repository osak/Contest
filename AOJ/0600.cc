//Name: Baumkuchen
//Level: 3
//Category: 最小値の最大化,累積和,二分探索
//Note: 

/**
 * 一切れの大きさの下限について二分探索する。
 *
 * 下限をひとつ決め、更に切断する切れ込みをひとつ決めると、この切れ込みを端にもつ2つの切れ端について、
 * もう一方の端をどこにするかは累積和上の二分探索で求められる。
 * もう一方の端をどちらも下限ギリギリになるように取ったとき、これらが交差しておらず、かつ3つ目の切れ端も下限を超えていれば、その下限は達成できる。
 *
 * 円周上の累積和をうまく扱うため、数列を3回繰り返したものの上で考えるとよい。
 * オーダーは O(N (log N)^2)。
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool solve(bool first) {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    vector<long long> as(1+3*N);
    as[0] = 0; // sentinel
    for(int i = 1; i <= N; ++i) {
        cin >> as[i];
        as[N+i] = as[N*2+i] = as[i];
    }
    for(int i = 1; i < 1+3*N; ++i) {
        as[i] += as[i-1];
    }

    long long sum = as[N];
    long long left = 0, right = sum / 3 + 10;
    while(left+1 < right) {
        const long long c = (left + right) / 2;
        // Separate between m-1 and m
        bool ok = false;
        for(int m = N+1; m <= 2*N; ++m) {
            const auto it = begin(as) + m;
            auto lit = lower_bound(it-N, it, as[m-1] - c);
            auto rit = lower_bound(it, it+N, as[m-1] + c);
            if(as[m-1] - *lit < c) {
                --lit;
            }
            if(rit == it+N) goto next;
            if(rit - lit >= N) goto next;
            if(sum - (*rit - *lit) < c) goto next;
            ok = true;
            break;
next:
            ;
        }
        if(ok) {
            left = c;
        } else {
            right = c;
        }
    }
    cout << left << endl;
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
