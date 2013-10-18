//Name: Bookshelf 2
//Level: 1
//Category: 動的計画法,DP
//Note:

/**
 * 高さの上限は20000000(2千万)だが、構成可能な高さは2^20=100万通り程度しかない。
 * よって、構成可能な高さだけを配列に入れておき、牛を1頭追加したら、今までに構成したことのない高さの場合のみ
 * 配列に追加する。
 *
 * オーダーはO(N 2^N)。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

bool can[20000001];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N, B;
    scanf("%d %d", &N, &B);
    vector<int> q[2];
    q[0].push_back(0);
    can[0] = true;
    int S = 0;
    while(N--) {
        int H;
        scanf("%d", &H);
        q[1] = q[0];
        FOREACH(it, q[0]) {
            const int nh = *it + H;
            if(!can[nh]) {
                q[1].push_back(nh);
                can[nh] = true;
            }
        }
        q[0].swap(q[1]);
        S += H;
    }
    int ans = S;
    for(int i = B; i <= S; ++i) {
        if(can[i]) {
            ans = i - B;
            break;
        }
    }
    printf("%d\n", ans);
    return 0;
}
