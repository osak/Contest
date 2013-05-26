#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>

using namespace std;

#define TIMES(i,n) for(int i = 0; (i) < (n); ++(i))
#define FOREACH(it,v) for(__typeof((v).begin()) it = (v).begin(); (it) != (v).end(); ++(it))

bool field[2001][2001];

bool in_range(int a, int x, int b) {
    return a <= x && x < b;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        fill_n((bool*)field, sizeof(field)/sizeof(bool), false);
        field[0][1000] = true;
        vector<pair<int,int> > points;
        TIMES(row, N-1) {
            TIMES(col, 2001) {
                if(field[row][col]) {
                    field[row+1][col-1] = field[row+1][col+1] = true;
                    points.push_back(make_pair(row, col));
                }
            }
        }
        TIMES(col, 2001) {
            if(field[N-1][col]) points.push_back(make_pair(N-1, col));
        }

        // ↑: sqrt(3)
        // →: 1
        const int K = points.size();
        //cout << K << endl;
        long long ans = 0;
        TIMES(i, K) {
            const pair<int,int> a = points[i];
            TIMES(j, i) {
                const pair<int,int> b = points[j];
                const int dr = a.first - b.first;
                const int dc = a.second - b.second;
                { // * (1/2, 1/2 sqrt(3))
                    const int nr = (dr-dc) / 2;
                    const int nc = (dr*3+dc) / 2;
                    if(in_range(0, b.first+nr, 2001) && in_range(0, b.second+nc, 2001) && field[b.first+nr][b.second+nc]) ++ans;
                }
                { // * (1/2, -1/2 sqrt(3))
                    const int nr = (dr+dc) / 2;
                    const int nc = (-dr*3+dc) / 2;
                    if(in_range(0, b.first+nr, 2001) && in_range(0, b.second+nc, 2001) && field[b.first+nr][b.second+nc]) ++ans;
                }
            }
        }
        cout << ans/3 << endl;
    }
    return 0;
}
