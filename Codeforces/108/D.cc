#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<int,int> Point;
const int DELTA[][2] = {{0,1},{0,-1},{1,0},{-1,0}};

int N, M;

int hash(const Point &p) {
    return p.first*M + p.second;
}

Point unhash(int val) {
    return Point(val/M, val%M);
}

int main() {
    ios::sync_with_stdio(0);

    int K;
    cin >> N >> M >> K;

    vector<vector<int> > field(N, vector<int>(M));
    for(int i = 0; i < N; ++i)
        for(int j = 0; j < M; ++j) 
            cin >> field[i][j];

    vector<Point> important;
    for(int i = 0; i < K; ++i) {
        Point p;
        cin >> p.first >> p.second;
        p.first--; p.second--;
        important.push_back(p);
    }

    const int maxpos = hash(Point(N-1, M-1)) + 1;

    // excluding start, including end
    vector<vector<int> > mindist(maxpos, vector<int>(maxpos, 1000*N*M));
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            const int fromh = hash(Point(i, j));
            for(int d = 0; d < 4; ++d) {
                const Point to(i+DELTA[d][0], j+DELTA[d][1]);
                if(0 <= to.first && to.first < N && 0 <= to.second && to.second < M) {
                    mindist[fromh][hash(to)] = field[to.first][to.second];
                }
            }
            mindist[fromh][fromh] = field[i][j];
        }
    }

    for(int k = 0; k < maxpos; ++k) {
        for(int i = 0; i < maxpos; ++i) {
            for(int j = 0; j < maxpos; ++j) {
                mindist[i][j] = min(mindist[i][j], mindist[i][k] + mindist[k][j]);
            }
        }
    }

    vector<vector<int> > dp(1<<K, vector<int>(N*M, 1000*N*M));
    for(int i = 0; i < K; ++i) {
        const Point &p = important[i];
        dp[1<<i][hash(p)] = field[p.first][p.second];
        for(int j = 0; j < maxpos; ++j) {
            if(j != hash(p)) dp[1<<i][j] = mindist[hash(p)][j] + field[p.first][p.second];
        }
    }

    //determine dp[pat][i]
    for(int pat = 0; pat < (1<<K); ++pat) {
        for(int subpat = 1; subpat < pat; ++subpat) {
            if((pat & subpat) == subpat) {
                int rem = pat ^ subpat;
                for(int i = 0; i < maxpos; ++i) { 
                    const Point ip = unhash(i);
                    dp[pat][i] = min(dp[pat][i], dp[subpat][i]+dp[rem][i]-field[ip.first][ip.second]);
                    for(int j = 0; j < maxpos; ++j) {
                        const Point jp = unhash(j);
                        dp[pat][i] = min(dp[pat][i], dp[subpat][i]+dp[rem][j]+mindist[i][j]-field[jp.first][jp.second]);
                    }
                }
            }
        }
    }

    int ans = 1000*N*M;
    for(int i = 0; i < maxpos; ++i)
        ans = min(ans, dp[(1<<K)-1][i]);

    cout << ans << endl;
}
