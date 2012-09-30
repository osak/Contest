//Name: Pachimon Creature
//Level: 3
//Category: 動的計画法,DP,探索
//Note:

/*
 * 障害物がないので，マス目間の距離はマンハッタン距離になる．
 * また，順番は最初に選んだパチクリから順番に1ずつ増やしながら捕まえる以外に存在しない．
 * したがって，マップでスタート，ゴール，各パチクリの座標だけを覚えておいて
 * 種類ごとにパチクリをなめていき，そこに到達する最短経路長を更新していく．
 *
 * オーダーは読み込みがO(XY)，パチクリの種類ごとの最大数をNとするとO(N^2)．
 */
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <cctype>
#include <climits>
#include <algorithm>

using namespace std;
typedef pair<int,int> Point;

inline int dist(const Point &p1, const Point &p2) {
    return abs(p1.first-p2.first) + abs(p1.second-p2.second);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    while(true) {
        int X, Y;
        cin >> X >> Y;
        if(!X && !Y) break;

        Point start, goal;
        vector<Point> creatures[5];
        for(int i = 0; i < Y; ++i) {
            string line;
            cin >> line;
            for(int j = 0; j < X; ++j) {
                if(line[j] == 'S') {
                    start = make_pair(i, j);
                } else if(line[j] == 'G') {
                    goal = make_pair(i, j);
                } else if(isdigit(line[j])) {
                    creatures[line[j]-'0'-1].push_back(make_pair(i, j));
                }
            }
        }
        int best_init = -1;
        int ans = INT_MAX;
        for(int init = 0; init < 5; ++init) {
            vector<int> prev, cur;
            {
                int target = (init+1) % 5;
                // 最初は init から始めて, init+1 を捕まえたところから始める．
                prev.resize(creatures[target].size());
                for(int i = 0; i < (int)creatures[target].size(); ++i) {
                    prev[i] = dist(start, creatures[target][i]);
                }
            }
            for(int step = 2; step < 5; ++step) {
                const int target = (init+step) % 5;
                const int prev_target = (target+4) % 5;
                const vector<Point> &tv = creatures[target];
                const vector<Point> &pv = creatures[prev_target];
                cur.resize(tv.size());
                fill(cur.begin(), cur.end(), INT_MAX/5);
                for(int i = 0; i < (int)tv.size(); ++i) { // Target(position move to)
                    for(int j = 0; j < (int)pv.size(); ++j) { // Previous(position move from)
                        cur[i] = min(cur[i], prev[j] + dist(pv[j], tv[i]));
                    }
                }
                prev = cur;
            }
            // 最後はゴールへ移動
            {
                const int prev_target = (init+4) % 5;
                for(int i = 0; i < (int)prev.size(); ++i) {
                    const int d = prev[i] + dist(creatures[prev_target][i], goal);
                    if(d < ans) {
                        ans = d;
                        best_init = init;
                    }
                }
            }
        }
        if(best_init == -1) cout << "NA" << endl;
        else cout << best_init+1 << ' ' << ans << endl;
    }
    return 0;
}
