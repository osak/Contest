#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <deque>

using namespace std;

int main() {
    while(true) {
        int N, M;
        cin >> N >> M;
        if(!N && !M) break;

        vector<vector<int> > v(N, vector<int>(N, -1));

        vector<bool> connected(N, false);
        int connectcnt = 0;
        for(int i = 0; i < M; ++i) {
            int a, b, w;
            cin >> a >> b >> w;
            --a; --b;
            v[a][b] = v[b][a] = w;

            if(!connected[a]) ++connectcnt;
            if(!connected[b]) ++connectcnt;

            connected[a] = connected[b] = true;
        }

        if(connectcnt != N) {
            cout << -1 << endl;
            continue;
        }

        int ans = INT_MAX;
        vector<vector<bool> > checked(N, vector<bool>(N, false));
        for(int sa = 0; sa < N; ++sa) {
            for(int sb = sa+1; sb < N; ++sb) {
                if(v[sa][sb] == -1) continue;
                vector<bool> used(N, false);
                deque<int> unused_node;
                deque<int> used_node;

                for(int i = 0; i < N; ++i)
                    if(i != sa && i != sb) unused_node.push_back(i);

                used_node.push_back(sa);
                used_node.push_back(sb);

                int mincost = v[sa][sb];
                int maxcost = v[sa][sb];
                used[sa] = used[sb] = true;
                for(int i = 2; i < N; ++i) {
                    int bestj, bestk;
                    int bestdiff = INT_MAX;
                    for(int j = 0; j < used_node.size(); ++j) {
                        for(int k = 0; k < unused_node.size(); ++k) {
                            int a = used_node[j];
                            int b = unused_node[k];
                            if(mincost <= v[a][b] && v[a][b] <= maxcost) {
                                bestj = j;
                                bestk = k;
                                bestdiff = 0;
                                goto endjk;
                            }
                            else if(v[a][b] < mincost) {
                                if(maxcost - v[a][b] < bestdiff) {
                                    bestj = j;
                                    bestk = k;
                                    bestdiff = maxcost - v[a][b];
                                }
                            }
                            else if(maxcost < v[a][b]) {
                                if(v[a][b] - mincost < bestdiff) {
                                    bestj = j;
                                    bestk = k;
                                    bestdiff = v[a][b] - mincost;
                                }
                            }
                        }
                    }
endjk:
                    int a = used_node[bestj], b = unused_node[bestk];
                    used[b] = true;
                    if(bestdiff > 0) {
                        if(v[a][b] < mincost) {
                            mincost = v[a][b];
                        }
                        else {
                            maxcost = v[a][b];
                        }
                    }

                    if(maxcost-mincost >= ans) break;
                    used_node.push_back(b);
                    unused_node.erase(unused_node.begin()+bestk);
                    checked[a][b] = checked[b][a] = true;

                }
                ans = min(ans, maxcost-mincost);
            }
        }

        cout << ans << endl;
    }

    return 0;
}
