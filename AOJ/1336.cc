//Name: The Last Ant
//Level: 2
//Category: シミュレーション
//Note:

/**
 * 細いところにいるアリを管理して1秒ずつシミュレーションする。
 * 2匹のアリが衝突するとき、隣り合ったセルにいた場合は、1秒後にはすれ違っているので問題ない。
 * 1つ離れたマスにいた場合は、移動後に向きを反転する。
 *
 * 向きの反転を考えた場合でも、アリを区別しなければそのまますれ違ったのと同じなので、
 * 全てのアリが脱出するまでの時間は高々l秒である。
 * したがって、この愚直なシミュレーションで間に合う。
 *
 * オーダーは O(NL)。
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool solve() {
    int N, L;
    if(!(cin >> N >> L)) return false;
    if(!N && !L) return false;

    vector<vector<pair<int,int>>> ants(L+1), buf(L+1);
    for(int i = 0; i < N; ++i) {
        char c;
        int x;
        cin >> c >> x;
        ants[x].emplace_back(i, c == 'L' ? -1 : 1);
    }

    int rem = N;
    int last = -1;
    int turn = 0;
    while(rem) {
        ++turn;
        for(int i = 0; i < L+1; ++i) {
            buf[i].clear();
        }
        for(int i = 0; i < L+1; ++i) {
            for(const auto &ant : ants[i]) {
                buf[i + ant.second].push_back(ant);
            }
        }
        for(int i = 0; i < L+1; ++i) {
            if(buf[i].size() == 2) {
                buf[i][0].second *= -1;
                buf[i][1].second *= -1;
            }
        }
        if(buf.back().size() > 0) {
            last = buf.back()[0].first;
            buf.back().clear();
            --rem;
        }
        if(buf[0].size() > 0) {
            last = buf[0][0].first;
            buf[0].clear();
            --rem;
        }
        ants.swap(buf);
    }
    cout << turn << ' ' << last+1 << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
