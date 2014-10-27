//Name: Seven Puzzle
//Level: 2
//Category: 探索
//Note:

/**
 * 状態を整数にエンコードして、同じ状態を2回踏まないようにしながら探索する。
 * テストケースの数が多いので、ゴールから逆に探索していき、「ある盤面に到達するまでの最小手数」を全ての盤面に対して求めておくとよい。
 *
 * オーダーは O(N!)。
 * ただしNはマスの数で、N=8。
 */

#include <iostream>
#include <array>
#include <vector>
#include <unordered_map>

using namespace std;

array<array<int,4>,2> field;

int encode() {
    int res = 0;
    for(int r = 0; r < 2; ++r) {
        for(int c = 0; c < 4; ++c) {
            res *= 8;
            res += field[r][c];
        }
    }
    return res;
}

pair<int,int> decode(int v) {
    pair<int,int> zero;
    for(int r = 1; r >= 0; --r) {
        for(int c = 3; c >= 0; --c) {
            field[r][c] = v % 8;
            v /= 8;
            if(field[r][c] == 0) {
                zero = make_pair(r, c);
            }
        }
    }
    return zero;
}

const int DR[] = {0, -1, 0, 1};
const int DC[] = {1, 0, -1, 0};
unordered_map<int,int> memo;
void init() {
    for(int r = 0; r < 2; ++r) {
        for(int c = 0; c < 4; ++c) {
            field[r][c] = r*4 + c;
        }
    }

    vector<int> q[2];
    q[0].push_back(encode());
    memo[q[0].back()] = 0;
    int turn = 1;
    while(q[0].size() > 0) {
        q[1].clear();
        for(int cur : q[0]) {
            auto z = decode(cur);
            for(int d = 0; d < 4; ++d) {
                const int nr = z.first + DR[d];
                const int nc = z.second + DC[d];
                if(nr < 0 || nr >= 2 || nc < 0 || nc >= 4) continue;
                swap(field[z.first][z.second], field[nr][nc]);
                const int ns = encode();
                if(!memo.count(ns)) {
                    memo[ns] = turn;
                    q[1].push_back(ns);
                }
                swap(field[z.first][z.second], field[nr][nc]);
            }
        }
        turn++;
        q[0].swap(q[1]);
    }
}

bool solve() {
    for(int r = 0; r < 2; ++r) {
        for(int c = 0; c < 4; ++c) {
            if(!(cin >> field[r][c])) return false;
        }
    }

    cout << memo[encode()] << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    init();
    while(solve()) ;
    return 0;
}
