#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>

using namespace std;

int field[3][3];
typedef long long LL;

LL encode() {
    LL res = 0;
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            res *= 10;
            res += field[i][j];
        }
    }
    return res;
}

void decode(LL v) {
    for(int i = 2; i >= 0; --i) {
        for(int j = 2; j >= 0; --j) {
            field[i][j] = v % 10;
            v /= 10;
        }
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            field[i][j] = i*3 + j + 1;
        }
    }
    field[2][2] = 0;
    const LL GOAL = encode();

    for(int i = 0; i < 3; ++i) {
        string line;
        cin >> line;
        for(int j = 0; j < 3; ++j) {
            field[i][j] = line[j] - '0';
        }
    }

    unordered_set<LL> memo;
    memo.insert(encode());
    queue<LL> q;
    q.push(encode());
    while(!q.empty()) {
        const LL cur = q.front();
        q.pop();
        decode(cur);

        int zr, zc;
        for(int r = 0; r < 3; ++r) {
            for(int c = 0; c < 3; ++c) {
                if(field[r][c] == 0) {
                    zr = r;
                    zc = c;
                    break;
                }
            }
        }
        const static int DR[] = {0, -1, 0, 1};
        const static int DC[] = {1, 0, -1, 0};
        //const static int DR[] = {1, -1, 1, -1};
        //const static int DC[] = {1, 1, -1, -1};
        for(int i = 0; i < 4; ++i) {
            const int nr = zr + DR[i];
            const int nc = zc + DC[i];
            if(nr < 0 || nr >= 3 || nc < 0 || nc >= 3) continue;
            swap(field[zr][zc], field[nr][nc]);
            const LL code = encode();
            if(code == GOAL) {
                cout << "Possible" << endl;
                return 0;
            }
            if(memo.count(code) == 0) {
                memo.insert(code);
                q.push(code);
            }
            swap(field[zr][zc], field[nr][nc]);
        }
    }
    cout << "Impossible" << endl;
    return 0;
}
