//Name: New Year Ratings Change
//Level: 2
//Category: 貪欲,Greedy
//Note:

/**
 * 数直線上で複数個が重なっているところを右に伸ばせばよい。
 * レート順にソートして1つずつ処理しながら、余ったものを覚えておく。
 *
 * オーダーはO(N)。
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

bool solve() {
    int N;
    if(!(cin >> N)) return false;
    vector<pair<int,int>> v(N);
    for(int i = 0; i < N; ++i) {
        int val;
        cin >> val;
        v[i] = make_pair(val, i);
    }
    sort(v.begin(), v.end());
    long long cur = 0;
    queue<int> q;
    vector<long long> ans(N, 0);
    auto it = v.begin();
    while(it != v.end()) {
        while(!q.empty() && cur < it->first) {
            ans[q.front()] = cur;
            q.pop();
            ++cur;
        }
        cur = it->first;
        q.push(it->second);
        ++it;
    }
    while(!q.empty()) {
        ans[q.front()] = cur;
        q.pop();
        ++cur;
    }
    for(int i = 0; i < N; ++i) {
        if(i > 0) cout << ' ';
        cout << ans[i];
    }
    cout << endl;
    return true;
}
    
int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
