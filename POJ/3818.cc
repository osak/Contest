//Name: Mosaic
//Level:
//Category:
//Note:

/*
 * 再帰計算版．
 * -O2 でも 10 500 に 1秒ほどかかり，POJではTLEする．
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int MOD = 1000000;

const int TILE[5][2] = {
    {0x03, 0x03}, {0x02, 0x03}, {0x01, 0x03}, {0x03, 0x01}, {0x03, 0x02}
};

int R, C;
int current[500];
string dbg[10];
int hash(int r, int c) {
    int val = 0;
    const int mask1 = (1<<(r+1)) - 1;
    const int mask2 = (1<<R)-1 - (mask1>>1);
    //cout << current[c] << ' ' << current[c+1] << endl;
    if(c+1 < C) val |= current[c+1] & mask1;
    val |= (current[c] & mask2) << 1;
    return val;
}

inline bool canput(int r, int c, int tidx) {
    const int cur = (current[c] >> r) & 0x03;
    const int nr = c+1 < C ? (current[c+1] >> r)&0x03 : 0x03;
    return (cur&TILE[tidx][0]) == 0 && (nr&TILE[tidx][1]) == 0;
}

inline void put(int r, int c, int tidx) {
    current[c] |= TILE[tidx][0] << r;
    if(c+1 < C) current[c+1] |= TILE[tidx][1] << r;
    /*
    if(TILE[tidx][0] & 0x01) dbg[r][c] = tidx+'0';
    if(TILE[tidx][0] & 0x02) dbg[r+1][c] = tidx+'0';
    if(c+1 < C && TILE[tidx][1] & 0x01) dbg[r][c+1] = tidx+'0';
    if(c+1 < C && TILE[tidx][1] & 0x02) dbg[r+1][c+1] = tidx+'0';
    */
}

inline void unput(int r, int c, int tidx) {
    current[c] &= ~(TILE[tidx][0]<<r);
    if(c+1 < C) current[c+1] &= ~(TILE[tidx][1]<<r);
    /*
    if(TILE[tidx][0] & 0x01) dbg[r][c] = '*';
    if(TILE[tidx][0] & 0x02) dbg[r+1][c] = '*';
    if(c+1 < C && TILE[tidx][1] & 0x01) dbg[r][c+1] = '*';
    if(c+1 < C && TILE[tidx][1] & 0x02) dbg[r+1][c+1] = '*';
    */
}

int memo[10][501][1<<11];
int calc(int r, int c) {
    if(r == R) {
        ++c;
        r = 0;
    }
    if(c == C) {
        /*
        for(int i = 0; i < R; ++i) {
            cout << dbg[i] << endl;
        }
        cout << endl;
        */
        return 1;
    }
    const int hashval = hash(r, c);
    //cout << r << ' ' << c << ' ' << hashval << endl;
    int &res = memo[r][c][hashval];
    if(res == -1) {
        res = 0;
        if(r < R-1) {
            for(int tidx = 0; tidx < 5; ++tidx) {
                if(canput(r, c, tidx)) {
                    put(r, c, tidx);
                    if(current[c] & (1<<r)) {
                        res += calc(r+1, c);
                        res %= MOD;
                    }
                    unput(r, c, tidx);
                }
            }
            if(current[c] & (1<<r)) {
                res += calc(r+1, c);
                res %= MOD;
            }
        } else if(r == R-1) {
            if(current[c] & (1<<r)) res = calc(r+1, c);
            else res = 0;
        }
    }
    return res;
}

inline void calc2(int r, int c, int pat) {
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    while(true) {
        cin >> R >> C;
        if(!R && !C) break;
        fill_n((int*)memo, sizeof(memo)/sizeof(int), -1);
        fill_n((int*)current, sizeof(current)/sizeof(int), 0);
        /*
        for(int i = 0; i < R; ++i) {
            dbg[i] = string(C, '*');
        }
        */
        cout << calc(0, 0) << endl;
    }
    return 0;
}
