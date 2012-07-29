#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef pair<int,int> Point;
int H, W;
int N;
string ans;

void print_field(vector<string> &field) {
    for(int i = 0; i < field.size(); ++i) {
        cout << field[i] << endl;
    }
    cout << endl;
}

bool dfs(vector<string> &field, Point pos, char dir, string cmd) {
    if(cmd.size() == N) {
        ans = cmd;
        return true;
    }
    //cout << cmd << endl;
    //print_field(field);

    if(dir != 'U') {
        for(int y = pos.second; y < H; ++y) {
            if(field[y][pos.first] == 'o') {
                field[y][pos.first] = '.';
                if(dfs(field, Point(pos.first, y), 'D', cmd+'D')) return true;
                field[y][pos.first] = 'o';
                break;
            }
        }
    }
    if(dir != 'D') {
        for(int y = pos.second; y >= 0; --y) {
            if(field[y][pos.first] == 'o') {
                field[y][pos.first] = '.';
                if(dfs(field, Point(pos.first, y), 'U', cmd+'U')) return true;
                field[y][pos.first] = 'o';
                break;
            }
        }
    }
    if(dir != 'L') {
        for(int x = pos.first; x < W; ++x) {
            if(field[pos.second][x] == 'o') {
                field[pos.second][x] = '.';
                if(dfs(field, Point(x, pos.second), 'R', cmd+'R')) return true;
                field[pos.second][x] = 'o';
                break;
            }
        }
    }
    if(dir != 'R') {
        for(int x = pos.first; x >= 0; --x) {
            if(field[pos.second][x] == 'o') {
                field[pos.second][x] = '.';
                if(dfs(field, Point(x, pos.second), 'L', cmd+'L')) return true;
                field[pos.second][x] = 'o';
                break;
            }
        }
    }

    return false;
}

int main() {
    cin >> H >> W;

    vector<string> field;
    Point init;
    char dir;
    for(int i = 0; i < H; ++i) {
        string s;
        cin >> s;
        field.push_back(s);

        for(int j = 0; j < W; ++j) {
            if(s[j] == 'o') ++N;
            if(s[j] == '.' || s[j] == 'o') continue;
            init = Point(j, i);
            dir = s[j];
        }
    }

    dfs(field, init, dir, "");
    cout << ans << endl;
    return 0;
}
