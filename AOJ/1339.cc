//Name: Dragon's Cruller
//Level: 3
//Category: 最短経路,探索
//Note:

/**
 * 状態は高々9!通りしかないので、数の並び方を適当にエンコードして状態として使い、ダイクストラで最短経路を求めればよい。
 *
 * オーダーは O(V log V)。
 * ただしVは状態数の総数で、V=9!。
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <cassert>
#include <array>

using namespace std;

typedef long long LL;

array<int,9> field, goal;

LL encode() {
    LL res = 0;
    for(int i = 0; i < 9; ++i) {
        res *= 9;
        res += field[i];
    }
    return res;
}

void decode(LL v) {
    for(int i = 0; i < 9; ++i) {
        field[8-i] = v % 9;
        v /= 9;
    }
}

const int TO[4][9] = {
    {1, 2, 3, 4, 5, 6, 7, 8, 0},
    {8, 0, 1, 2, 3, 4, 5, 6, 7},
    {6, 7, 8, 0, 1, 2, 3, 4, 5},
    {3, 4, 5, 6, 7, 8, 0, 1, 2},
};
bool solve() {
    int CH, CV;
    if(!(cin >> CH >> CV)) return false;
    if(!CH && !CV) return false;

    for(int i = 0; i < 9; ++i) {
        cin >> field[i];
    }
    for(int i = 0; i < 9; ++i) {
        cin >> goal[i];
    }
    LL G = 0;
    {
        array<int,9> tmp = field;
        field = goal;
        G = encode();
        field = tmp;
    }

    unordered_map<LL,int> memo;
    memo[0] = encode();
    priority_queue<pair<int,int>> q;
    q.push(make_pair(0, encode()));
    while(!q.empty()) {
        const int cost = -q.top().first;
        const LL state = q.top().second;
        q.pop();
        if(memo.count(state) && memo[state] < cost) continue;
        if(state == G) {
            cout << cost << endl;
            return true;
        }
        decode(state);

        int zero = 0;
        while(field[zero] != 0) ++zero;

        for(int d = 0; d < 4; ++d) {
            swap(field[zero], field[TO[d][zero]]);
            const int nc = cost + (d < 2 ? CH : CV);
            const int ns = encode();
            swap(field[zero], field[TO[d][zero]]);
            if(memo.count(ns) && memo[ns] <= nc) continue;
            memo[ns] = nc;
            q.push(make_pair(-nc, ns));
        }
    }
    assert(false);
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
