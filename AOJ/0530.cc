#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>
#include <utility>

using namespace std;

struct Tag {
    unsigned y, x, c, m;
    Tag() {}
    Tag(int yy, int xx, unsigned cc, int mm) : x(xx), y(yy), c(cc), m(mm) {}
};
bool operator < (const Tag &t1, const Tag &t2) {
    return t1.c > t2.c;
}

int main() {
    while(true) {
        int N, M;
        cin >> N >> M;
        if(!N && !M) break;

        vector<vector<pair<int, int> > > stones(N);
        for(int i = 0; i < N; ++i) {
            int n;
            cin >> n;
            while(n--) {
                int x, d;
                cin >> x >> d;
                --x;
                stones[i].push_back(make_pair(x, d));
            }
        }

        //vector<vector<vector<int> > > dp(3, vector<vector<int> >(10, vector<int>(M+1, 2000*1000*150)));
        vector<vector<vector<int> > > dp(N, vector<vector<int> >(10, vector<int>(M+1, 2000*1000*150)));
        for(int i = 0; i < stones[0].size(); ++i) {
            dp[0][i][M] = 0;
        }
        if(M > 0) {
            for(int i = 0; i < stones[1].size(); ++i) {
                dp[1][i][M-1] = 0;
            }
        }
        for(int i = 1; i < N; ++i) {
            /*
            int curr = i%3;
            int prev = (i-1)%3;
            int pp = (i-2)%3;
            */
            int curr = i;
            int prev = i-1;
            int pp = i-2;
            if(i > 1) {
                for(int k = 0; k < stones[i].size(); ++k) {
                    fill(dp[curr][k].begin(), dp[curr][k].end(), 2000*1000*150);
                }
            }
            if(i > 1) {
                for(int j = 0; j < stones[i-2].size(); ++j) {
                    //pp to prev
                    int sx = stones[i-2][j].first;
                    int sc = stones[i-2][j].second;
                    for(int k = 0; k < stones[i-1].size(); ++k) {
                        int skx = stones[i-1][k].first;
                        int skc = stones[i-1][k].second;
                        int cost = (sc+skc) * abs(sx-skx);
                        for(int m = 0; m <= M; ++m) {
                            dp[prev][k][m] = min(dp[prev][k][m], dp[pp][j][m]+cost);
                        }
                    }

                    //pp to curr
                    for(int k = 0; k < stones[i].size(); ++k) {
                        int skx = stones[i][k].first;
                        int skc = stones[i][k].second;
                        int cost = (sc+skc) * abs(sx-skx);
                        for(int m = 0; m < M; ++m) {
                            dp[curr][k][m] = min(dp[curr][k][m], dp[pp][j][m+1]+cost);
                        }
                    }
                }
            }
            for(int j = 0; j < stones[i-1].size(); ++j) {
                //prev to curr
                int sx = stones[i-1][j].first;
                int sc = stones[i-1][j].second;
                for(int k = 0; k < stones[i].size(); ++k) {
                    int skx = stones[i][k].first;
                    int skc = stones[i][k].second;
                    int cost = (sc+skc) * abs(sx-skx);
                    for(int m = 0; m <= M; ++m) {
                        dp[curr][k][m] = min(dp[curr][k][m], dp[prev][j][m]+cost);
                    }
                }
            }
        }
        int ans = INT_MAX;
        /*
        int curr = (N-1) % 3;
        int prev = (N-2) % 3;
        */
        int curr = N-1;
        int prev = N-2;

        for(int m = 0; m <= M; ++m) {
            for(int k = 0; k < stones[N-1].size(); ++k) {
                ans = min(ans, dp[curr][k][m]);
            }
            if(m > 0) {
                for(int k = 0; k < stones[N-2].size(); ++k) {
                    ans = min(ans, dp[prev][k][m]);
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
