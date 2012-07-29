//Name: Path on a Grid
//Level: 2
//Category: シミュレーション,迷路,グリッド
//Note:

/*
 * 壁をなでていく、ではなく、壁の上を通っていき、曲がるときの法則を考えるようにすると楽。
 */
#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

typedef pair<int, int> Point;

int pack(int x, int y) {
    return x*5+y;
}

Point unpack(int p) {
    return make_pair(p/5, p%5);
}

bool can(const vector<vector<int> > &v, int x1, int y1, int x2, int y2) {
    if(x1 < 0 || y1 < 0 || x1 >= 5 || y1 >= 5) return false;
    if(x2 < 0 || y2 < 0 || x2 >= 5 || y2 >= 5) return false;
    return v[pack(x1,y1)][pack(x2,y2)];
}

int main() {
    vector<vector<int> > v(30, vector<int>(30, 0));
    for(int i = 0; i < 9; ++i) {
        string str;
        cin >> str;
        for(int j = 0; j < str.size(); ++j) {
            if(i % 2 == 0) v[pack(j, i/2)][pack(j+1, i/2)] = v[pack(j+1,i/2)][pack(j,i/2)] = str[j]-'0';
            else v[pack(j, i/2)][pack(j, i/2+1)] = v[pack(j,i/2+1)][pack(j,i/2)] = str[j]-'0';
        }
    }

    const char *dirchar = "RDLU";
    const int delta[][2] = {
        {1, 0}, {0, 1}, {-1, 0}, {0, -1}
    };
    int x = 0, y = 0;
    int dir = 0;
    while(true) {
        cout << dirchar[dir];
        x += delta[dir][0];
        y += delta[dir][1];
        if(x == 0 && y == 0) break;

        int left = (dir+3)%4;
        int right = (dir+1)%4;
        if(can(v, x,y, x+delta[left][0],y+delta[left][1])) {
            dir = left;
        }
        else if(can(v, x,y, x+delta[dir][0],y+delta[dir][1])) {
            dir = dir;
        }
        else if(can(v, x,y, x+delta[right][0],y+delta[right][1])) {
            dir = right;
        }
        else dir = (dir+2)%4;
    }
    cout << endl;
    return 0;
}
