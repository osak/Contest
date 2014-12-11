//Name: Sort
//Level: 2
//Category: グラフ,Graph,最短経路
//Note:

/**
 * pの状態を頂点として、iとjを入れ替えて到達できる頂点にコストc_{i,j}の辺を張る。
 * ソート済み列を始点として、このグラフの上で最短経路を求めたとき、その最大値が答えとなる。
 *
 * オーダーは O(N^2 log N!) = O(N^3 log N)。
 */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>

using namespace std;

const int INF = 1000000000;

int main() {
    ios::sync_with_stdio(0);

    int N;
    cin >> N;

    vector<vector<int> > costs(N, vector<int>(N, 0));
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            cin >> costs[i][j];
        }
    }

    vector<int> dp(1<<21, INF);
    priority_queue<pair<int,int> > q;
    {
        int init = 0;
        for(int i = 0; i < N; ++i) {
            init |= (i&7) << (i*3);
        }
        q.push(make_pair(0, init&07777777));
    }
    while(!q.empty()) {
        int cost = -q.top().first;
        int state = q.top().second;
        q.pop();

        if(dp[state] <= cost) continue;
        dp[state] = cost;

        if(N == 8) {
            bool contains[8] = {0};
            for(int i = 0; i < 7; ++i) {
                contains[(state>>(3*i))&7] = true;
            }
            int rem = 0;
            while(contains[rem]) ++rem;
            state |= rem << 3*7;
        }

        for(int i = 0; i < N; ++i) {
            int ni = (state>>(3*i))&7;
            for(int j = 0; j < N; ++j) {
                if(i == j) continue;

                int nj = (state>>(3*j))&7;
                int newstate = state;
                newstate &= ~(7<<(3*i));
                newstate &= ~(7<<(3*j));
                newstate |= ni<<(3*j);
                newstate |= nj<<(3*i);
                newstate &= 07777777;
                int newcost = cost + costs[ni][nj];
                if(dp[newstate] > newcost) {
                    q.push(make_pair(-newcost, newstate));
                }
            }
        }
    }

    int ans = 0;
    for(vector<int>::iterator it = dp.begin(); it != dp.end(); ++it) {
        if(*it != INF) {
//            cout << oct << (it-dp.begin()) << ' ' << dec << *it << endl;
            ans = max(ans, *it);
        }
    }
    cout << ans << endl;

    return 0;
}
