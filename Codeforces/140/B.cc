#include <iostream>
#include <cstdio>
#include <algorithm>
#include <functional>

using namespace std;

typedef unsigned long long ULL;

int as[100001];
ULL sum[100001];
ULL ans[100001];
int main() {
    int N;
    scanf("%d", &N);
    for(int i = 0; i < N; ++i) {
        scanf("%d", as+i);
    }
    sort(as, as+N);
    for(int i = N-1; i >= 0; --i) {
        sum[i] = sum[i+1] + as[i];
    }
    int Q;
    scanf("%d", &Q);
    for(int i = 0; i < Q; ++i) {
        int K;
        scanf("%d", &K);
        K = min(K, N-1);
        if(ans[K] == 0) {
            long long tail = N-2;
            long long head = tail-K + 1;
            int phase = 1;
            while(tail >= 0) {
                ans[K] += phase * (sum[head] - sum[tail+1]);
                const long long size = tail - head + 1;
                const long long next_head = head - size*K;
                tail = head - 1;
                head = max(0LL, next_head);
                ++phase;
            }
        }
        if(i != 0) cout << ' ';
        cout << ans[K];
    }
    cout << endl;
    return 0;
}
