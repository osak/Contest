//Name: Red and Black
//Level: 2
//Category: 幅優先探索,やるだけ
//Note:

/*
 * @から幅優先探索するだけ．
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <queue>

using namespace std;

#define FOREACH(it,c) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int R, C;
    while(cin >> C >> R) {
        if(!R && !C) break;

        vector<string> field(R);
        pair<int,int> start;
        TIMES(r, R) {
            cin >> field[r];
            TIMES(c, C) {
                if(field[r][c] == '@') {
                    start = make_pair(r, c);
                }
            }
        }

        int cnt = 1;
        queue<pair<int,int> > q;
        q.push(start);
        field[start.first][start.second] = '#';
        while(!q.empty()) {
            const int r = q.front().first;
            const int c = q.front().second;
            q.pop();

            const int DR[] = {0, -1, 0, 1};
            const int DC[] = {1, 0, -1, 0};
            TIMES(i, 4) {
                const int nr = r + DR[i];
                const int nc = c + DC[i];
                if(0 <= nr && nr < R && 0 <= nc && nc < C) {
                    if(field[nr][nc] != '#') {
                        ++cnt;
                        field[nr][nc] = '#';
                        q.push(make_pair(nr, nc));
                    }
                }
            }
        }
        cout << cnt << endl;
    }
    return 0;
}
