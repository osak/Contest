#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cctype>
#include <queue>

using namespace std;

int main() {
    int R, C;
    cin >> R >> C;

    vector<string> code(R);
    for(int i = 0; i < R; ++i)
        cin >> code[i];
    
    pair<int,int> pos = make_pair(0,0);
    vector<vector<vector<int> > > memo(R, vector<vector<int> >(C, vector<int>(16, 0)));
    queue<pair<pair<int,int>,pair<int,int> > > q;
    int dir = 0;
    int dl[4][2] = {{0,1},{1,0},{0,-1},{-1,0}}; //Right,Down,Left,Up
    int mem = 0;
    bool halt = false;
    q.push(make_pair(pos, make_pair(mem,dir)));
    memo[0][0][0] |= 1;
    while(!q.empty()) {
        pos = q.front().first;
        mem = q.front().second.first;
        dir = q.front().second.second;
        q.pop();

        char c = code[pos.first][pos.second];
        if(c == '<') {
            dir = 2;
        }
        else if(c == '>') {
            dir = 0;
        }
        else if(c == '^') {
            dir = 3;
        }
        else if(c == 'v') {
            dir = 1;
        }
        else if(c == '_') {
            dir = mem?2:0;
        }
        else if(c == '|') {
            dir = mem?3:1;
        }
        else if(c == '?') {
            int &flag = memo[pos.first][pos.second][mem];
            for(int i = 0; i < 4; ++i) {
                if(!(flag & (1<<i))) {
                    pair<int,int> newpos = pos;
                    newpos.first = (newpos.first+dl[i][0]+R) % R;
                    newpos.second = (newpos.second+dl[i][1]+C) % C;
                    q.push(make_pair(newpos, make_pair(mem, i)));
                }
            }
            flag = 0x0f;
        }
        else if(c == '@') {
            halt = true;
            break;
        }
        else if(c == '+') {
            ++mem;
            if(mem == 16) mem = 0;
        }
        else if(c == '-') {
            --mem;
            if(mem == -1) mem = 15;
        }
        else if(isdigit(c)) {
            mem = c - '0';
        }
        pos.first = (pos.first+dl[dir][0]+R) % R;
        pos.second = (pos.second+dl[dir][1]+C) % C;
        if(!(memo[pos.first][pos.second][mem] & (1<<dir))) {
            q.push(make_pair(pos, make_pair(mem, dir)));
            memo[pos.first][pos.second][mem] |= 1<<dir;
        }
    }

    cout << (halt?"YES":"NO") << endl;
}
