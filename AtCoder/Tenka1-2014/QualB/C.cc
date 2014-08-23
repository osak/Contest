#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <cassert>
#include <string>

using namespace std;

const int DR[] = {0, 1, 0, -1};
const int DC[] = {1, 0, -1, 0};

bool solve() {
    int N;
    if(!(cin >> N)) return false;
    if(N > 9) return false;
    vector<string> field(N);
    for(int i = 0; i < N; ++i) {
        cin >> field[i];
    }

    vector<string> res(N);
    for(int i = 0; i < N; ++i) {
        res[i] = string(N, '.');
    }
    for(int pat = 0; pat < (1<<N); ++pat) {
        for(int i = 0; i < N; ++i) {
            if(pat & (1<<i)) res[0][i] = '#';
            else res[0][i] = '.';
        }
        for(int r = 1; r < N; ++r) {
            for(int c = 0; c < N; ++c) {
                int cnt = 0;
                for(int d = 0; d < 4; ++d) {
                    if(DR[d] == 1) continue;
                    const int nr = r-1 + DR[d];
                    const int nc = c + DC[d];
                    if(nr >= 0 && nr < N && nc >= 0 && nc < N && res[nr][nc] == '#') ++cnt;
                }
                if((cnt % 2 == 0 && field[r-1][c] == '.') || (cnt % 2 == 1 && field[r-1][c] == '#')) {
                    res[r][c] = '.';
                } else {
                    res[r][c] = '#';
                }
            }
        }
        /*
        for(const string &l : res) {
            cout << l << endl;
        }
        cout << endl;
        */
        // check last row
        bool ok = true;
        for(int c = 0; c < N; ++c) {
            int cnt = 0;
            for(int d = 0; d < 4; ++d) {
                if(DR[d] == 1) continue;
                const int nr = N-1 + DR[d];
                const int nc = c + DC[d];
                if(nr >= 0 && nr < N && nc >= 0 && nc < N && res[nr][nc] == '#') ++cnt;
            }
            if((cnt % 2 == 0 && field[N-1][c] == '#') || (cnt % 2 == 1 && field[N-1][c] == '.')) {
                ok = false;
                break;
            }
        }
        if(ok) {
            for(const string &l : res) {
                cout << l << endl;
            }
            break;
        }
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}

