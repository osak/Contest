//Name: Convenient Location
//Level: 2
//Cateogry: グラフ,Graph,全点間最短距離,All- points shortest path
//Note:

/**
 * Warshall-Floydで全点間最短距離を求め、行ごとに総和を求めて最小になるものを出力する。
 * 存在している街の番号を別に管理しないといけないのが面倒くさいが、隣接行列としては10×10でとってしまい、
 * どこにも行けない街があったら弾くという処理にすると楽。
 *
 * オーダーは O(N^3)。
 */

#include <iostream>
#include <vector>

using namespace std;

bool solve() {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    vector<vector<int>> dist(10, vector<int>(10, -1));
    for(int i = 0; i < N; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        dist[a][b] = dist[b][a] = c;
        dist[a][a] = 0;
        dist[b][b] = 0;
    }

    for(int k = 0; k < 10; ++k) {
        for(int i = 0; i < 10; ++i) {
            for(int j = 0; j < 10; ++j) {
                if(dist[i][k] == -1 || dist[k][j] == -1) continue;
                const int nd = dist[i][k] + dist[k][j];
                if(dist[i][j] == -1 || dist[i][j] > nd) {
                    dist[i][j] = nd;
                }
            }
        }
    }

    int town = -1;
    int sum = -1;
    for(int i = 0; i < 10; ++i) {
        int tmp = 0;
        bool valid = false;
        for(int j = 0; j < 10; ++j) {
            if(dist[i][j] != -1) {
                tmp += dist[i][j];
                valid = true;
            }
        }
        if(valid && (sum == -1 || tmp < sum)) {
            town = i;
            sum = tmp;
        }
    }
    cout << town << ' ' << sum << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
