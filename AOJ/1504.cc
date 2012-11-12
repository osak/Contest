//Name: Connect
//Level: 4
//Category: 探索,メモ化再帰
//Note:

/*
 * ペンシルパズルの「橋をかけろ」のような問題(ただし本物は全体が連結であるという条件が追加である)．
 * 盤面を左上から右，下の順でなめていき，
 * ・シマに当たったら橋の出し方を全て試す．
 *   このとき，橋を出した方向のマスにはフラグを立てておく．
 * ・橋フラグのマスに当たったら，その方向(右か下)に橋の本数を伝搬させる．
 * として探索していけばよい．
 *
 * ただしこのままだと計算量が爆発してしまうため，メモ化を加える．
 * あるマス(r, c)を見ているとき，不確定要素があるのは各列で一番上の未処理マスのみである(それより上は確定済み，それより下は必ずnil)．
 * これらの状態は
 * ・シマのマスであれば，そこに接続している橋の本数(0， 左から2本，上から2本で合計5通り)
 * ・シマ以外のマスであれば，橋の向きと本数(0，右向き，下向きと本数2通り，合計5通り)
 * ただし(r, c)以外のマスでは橋は上からくるパターンしかあり得ず，実質3通りである．
 * したがって状態数は最大で 10*10*(5*3^9) = 約1000万．
 * 実際には不可能な状態も多いと考えられるので，もっと少なくなる．
 *
 * オーダーは O(3^W HW)．
 */
#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <tr1/unordered_map>

using namespace std;

const int MOD = 100000007;

enum CellType {NONE, ISLAND, VER_BRIDGE, HOR_BRIDGE};
struct State {
    CellType type;
    int num;

    void inc(int n, CellType bridgeType) {
        num += n;
        if(num > 0 && type == NONE) type = bridgeType;
    }

    void dec(int n) {
        num -= n;
        assert(num >= 0);
        if(num == 0 && type != ISLAND) type = NONE;
    }

    int getval() const {
        if(type == VER_BRIDGE) return num+2;
        return num;
    }

    bool isBridge() const {
        return type == VER_BRIDGE || type == HOR_BRIDGE;
    }
};

State current[10][10];
int H, W;
tr1::unordered_map<int,int> memo[10][10];
int hash(int r_, int c_) {
    int val = 0;
    int r = r_, c = c_;
    for(int i = 0; i < W; ++i) {
        val *= 5;
        val += current[r][c].getval();
        ++c;
        if(c == W) {
            ++r;
            if(r == H) break;
            c = 0;
        }
    }
    return val;
}

State field[10][10];
void print_current() {
    for(int r = 0; r < H; ++r) {
        for(int c = 0; c < W; ++c) {
            if(current[r][c].type == ISLAND) cout << field[r][c].num;
            else if(current[r][c].type == HOR_BRIDGE) cout << " -="[current[r][c].num];
            else if(current[r][c].type == VER_BRIDGE) cout << " |#"[current[r][c].num];
            else cout << '.';
        }
        cout << endl;
    }
}

int dfs(int r, int c) {
    if(c == W) {
        ++r;
        c = 0;
    }
    if(r == H) {
        //print_current();
        //cout << endl;
        return 1;
    }
    const int hashval = hash(r, c);
    //cout << r << ' ' << c << ' ' << hashval << endl;
    if(memo[r][c].count(hashval)) return memo[r][c][hashval];
    int ret = 0;
    ret = 0;
    if(field[r][c].type == ISLAND) {
        const int rem = field[r][c].num - current[r][c].num;
        //cout << "rem " << rem << endl;
        if(rem < 0 || rem > 4) goto enddfs; // Invalid
        assert(rem >= 0);
        for(int right = 0; right <= min(rem, 2); ++right) {
            if(right > 0 && (c == W-1 || current[r][c+1].isBridge())) continue; // Cannot construct new bridge to right
            int down = rem - right; 
            if(down > 0 && r == H-1) continue; // Cannot construct new bridge to down
            if(down > 2) continue;

            // Construct right bridge
            if(right > 0) {
                current[r][c+1].inc(right, HOR_BRIDGE);
            }
            // Construct down bridge
            if(down > 0) {
                current[r+1][c].inc(down, VER_BRIDGE);
            }
            ret += dfs(r, c+1);
            ret %= MOD;
            // Restore
            if(down > 0) {
                current[r+1][c].dec(down);
            }
            if(right > 0) {
                current[r][c+1].dec(right);
            }
        }
    } else if(current[r][c].type != NONE) { // Bridge
        if(current[r][c].type == VER_BRIDGE) {
            if(r == H-1) goto enddfs; // Invalid
            if(current[r+1][c].isBridge()) goto enddfs;
            current[r+1][c].inc(current[r][c].num, VER_BRIDGE);
            ret += dfs(r, c+1);
            ret %= MOD;
            current[r+1][c].dec(current[r][c].num);
        } else if(current[r][c].type == HOR_BRIDGE) {
            if(c == W-1) goto enddfs; // Invalid
            if(current[r][c+1].isBridge()) goto enddfs;
            current[r][c+1].inc(current[r][c].num, HOR_BRIDGE);
            ret += dfs(r, c+1);
            ret %= MOD;
            current[r][c+1].dec(current[r][c].num);
        }
    } else {
        ret = dfs(r, c+1);
    }
enddfs:
    return memo[r][c][hashval] = ret;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    while(cin >> H >> W) {
        if(!H && !W) break;
        for(int i = 0; i < H; ++i) {
            string line;
            cin >> line;
            for(int j = 0; j < W; ++j) {
                if(line[j] == '.') {
                    field[i][j].type = NONE;
                }
                else {
                    field[i][j].type = ISLAND;
                    field[i][j].num = line[j]-'0';
                }
                current[i][j].type = field[i][j].type;
                current[i][j].num = 0;
                memo[i][j].clear();
            }
        }
        cout << dfs(0, 0) << endl;
    }
    return 0;
}
