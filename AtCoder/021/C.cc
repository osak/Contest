//Name: 増築王高橋君
//Level: 3
//Category: 貪欲,Priority queue
//Note: 部分点解法

/**
 * コストの低いものから順に増築していけばよい。
 * Priority queueを使うことでメンテナンスできる。
 *
 * オーダーは O(K log N)。
 */
#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef long long LL;

bool solve() {
    int K, N;
    if(!(cin >> K >> N)) return false;
    if(!K && !N) return false;
    if(K > 100000) return true;

    priority_queue<pair<LL,int>> q;
    for(int i = 0; i < N; ++i) {
        pair<LL,int> b;
        cin >> b.first >> b.second;
        b.first = -b.first;
        q.push(b);
    }
    LL score = 0;
    for(int i = 0; i < K; ++i) {
        auto p = q.top();
        q.pop();
        score += -p.first;
        p.first -= p.second;
        q.push(p);
    }
    cout << score << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
