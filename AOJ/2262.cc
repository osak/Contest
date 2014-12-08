//Name: Stopping Problem
//Level: 2
//Category: シミュレーション,幅優先探索,BFS
//Note:

/**
 * 状態は「どのマスにいるか」、「どの方向に進んでいるか」、「メモリの値がいくつか」の3つ。
 * 同じ状態からは同じ遷移しか発生しないので、一度通った状態は2回目以降は無視して良い。
 *
 * オーダーは O(RCDM)。
 * ただしDは進行方向の種類数、Mはメモリのとり得る値の種類数で、D=4, M=16。
 */
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_set>
#include <queue>
#include <tuple>

using namespace std;

const int DR[] = {0, -1, 0, 1};
const int DC[] = {1, 0, -1, 0};

int hashf(int r, int c, int d, int m) {
    return ((((r) * 20 + c) * 20 + d) * 20 + m);
}

bool solve() {
    int R, C;
    if(!(cin >> R >> C)) return false;

    vector<string> prog(R);
    for(int r = 0; r < R; ++r) {
        cin >> prog[r];
    }

    unordered_set<int> memo;
    queue<tuple<int,int,int,int>> q;
    q.push(make_tuple(0, 0, 0, 0));
    memo.insert(0);
    bool ans = false;
    while(!q.empty()) {
        int r, c, d, m;
        tie(r, c, d, m) = q.front();
        q.pop();

        switch(prog[r][c]) {
        case '<':
            d = 2;
            break;
        case '>':
            d = 0;
            break;
        case '^':
            d = 1;
            break;
        case 'v':
            d = 3;
            break;
        case '_':
            d = (m ? 2 : 0);
            break;
        case '|':
            d = (m ? 1 : 3);
            break;
        case '@':
            ans = true;
            goto end;
        case '+':
            m = (m + 1) % 16;
            break;
        case '-':
            m = (m + 15) % 16;
            break;
        default:
            if(isdigit(prog[r][c])) {
                m = prog[r][c] - '0';
            }
        }
        if(prog[r][c] == '?') {
            for(d = 0; d < 4; ++d) {
                const int nr = (r + DR[d] + R) % R;
                const int nc = (c + DC[d] + C) % C;
                const int h = hashf(nr, nc, d, m);
                if(!memo.count(h)) {
                    memo.insert(h);
                    q.push(make_tuple(nr, nc, d, m));
                }
            }
        } else {
            const int nr = (r + DR[d] + R) % R;
            const int nc = (c + DC[d] + C) % C;
            const int h = hashf(nr, nc, d, m);
            if(!memo.count(h)) {
                memo.insert(h);
                q.push(make_tuple(nr, nc, d, m));
            }
        }
    }
end:
    cout << (ans ? "YES" : "NO") << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
