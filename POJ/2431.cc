//Name: Expedition
//Level: 2
//Category: 貪欲,Greedy
//Note:

/**
 * ガソリンスタンドを通過したあとでガソリンが切れた場合、巻き戻して以前に補給したことにすればよい。
 * このとき、使うスタンドはもっとも多く補給できるものから使っていけばよい。
 *
 * オーダーはO(N log N)。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

bool solve() {
    int N;
    if(scanf("%d", &N) == EOF) return false;
    if(!N) return false;
    vector<pair<int,int> > v;
    TIMES(i, N) {
        int d, f;
        scanf("%d %d", &d, &f);
        v.push_back(make_pair(d, f));
    }
    int L, P;
    scanf("%d %d", &L, &P);
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());
    vector<pair<int,int> >::const_iterator it = v.begin();
    priority_queue<int> q;
    int ans = 0;
    while(L > 0) {
        L -= P;
        if(L <= 0) break;
        while(it != v.end() && it->first >= L) {
            q.push(it->second);
            ++it;
        }
        if(q.empty()) {
            ans = -1;
            break;
        }
        ++ans;
        P = q.top();
        q.pop();
    }
    printf("%d\n", ans);
    return false;
}

int main() {
    while(solve()) ;
    return 0;
}
