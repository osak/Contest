//Name: Summer of Phyonkichi
//Level: 3
//Category: グラフ,Graph,探索,メモ化,幅優先探索,BFS
//Note: 

/**
 * 時間を1つずつ進めながら、死なないで到達できるようなセルの集合を管理する。
 *
 * オーダーは O(HWN)。
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int DX[12] = {2, 2, 1, 0, -1, -2, -2, -2, -1, 0, 1, 2};
const int DY[12] = {0, -1, -2, -2, -2, -1, 0, 1, 2, 2, 2, 1};

bool solve() {
    int X, Y;
    if(!(cin >> X >> Y)) return false;
    if(!X && !Y) return false;
    int N;
    cin >> N;
    vector<pair<int,int>> ss;
    for(int i = 0; i < N; ++i) {
        int x, y;
        cin >> x >> y;
        ss.emplace_back(x, y);
    }

    vector<pair<int,int>> v[2];
    v[0].emplace_back(X, Y);
    for(int t = 0; t < N; ++t) {
        v[1].clear();
        for (const auto &cur : v[0]) {
            for(int d = 0; d < 12; ++d) {
                const int nx = cur.first + DX[d];
                const int ny = cur.second + DY[d];
                if(nx < 0 || nx >= 10 || ny < 0 || ny >= 10) continue;
                if(max(abs(nx-ss[t].first), abs(ny-ss[t].second)) > 1) continue;
                v[1].emplace_back(nx, ny);
            }
        }
        sort(begin(v[1]), end(v[1]));
        v[1].erase(unique(begin(v[1]), end(v[1])), end(v[1]));
        v[0].swap(v[1]);
    }
    cout << (v[0].size() > 0 ? "OK" : "NA") << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    while(solve()) ;
    return 0;
}
