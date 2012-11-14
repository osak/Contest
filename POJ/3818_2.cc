//Name: Mosaic
//Level: 4
//Category: DP,動的計画法,ビット演算
//Note:

/*
 * 典型的な敷き詰め問題．
 * あるマス(r,c)を見ているときは，(0,c+1)..(r,c+1)と(r,c)..(R-1,c)だけが次以降に影響する状態となる．
 * 図にすると
 * ....*
 * ....*
 * ...#*
 * ...*.
 * ...*.
 * こんな感じ．#が注目マスで，.は自明(必ず埋まっている or 必ず空いている)．
 * タイルの大きさが2×2なので，一番下の行では特殊処理が必要になることに注意．
 *
 * オーダーは O(RC 2^R)．
 * ただし状態の保持と遷移をどちらもビット演算でやらないとTLEする可能性が高い．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

const int MOD = 1000000;

const int TILE[6] = {
    0x0f, 0x0d, 0x0b, 0x07, 0x0e, 0x00
};
const int rcmask_tbl[11] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x100, 0x200, 0x400};

int R, C;
int memo[2][1<<11];
int res[11][501];
void calc(int R, int C) {
    fill_n((int*)memo, sizeof(memo)/sizeof(int), 0);
    const int pat_nums = 1<<(R+1);
    const int pat_mask = pat_nums-1;
    int *cur = memo[0], *next = memo[1];
    cur[0] = 1;
    for(int c = 0; c < C-1; ++c) {
        res[R][c] = cur[0];
        for(int r = 0; r < R; ++r) {
            fill_n(next, pat_nums, 0);
            const int rcmask = rcmask_tbl[r+1];
            for(int pat = 0; pat < pat_nums; ++pat) {
                if(cur[pat] == 0) continue;
                if(r == R-1) {
                    if(pat&rcmask) {
                        next[(pat<<1)&pat_mask] = cur[pat];
                        //cout << "cr: " << r << ' ' << c << ' ' << pat << ' ' << ((pat<<1)&pat_mask) << ' ' << cur[pat] << endl;
                    }
                } else {
                    for(int tidx = 0; tidx < 6; ++tidx) {
                        // (r,c) must be filled after place tile
                        if(!(pat & rcmask) && (tidx == 1 || tidx == 5)) continue;
                        int tpat = (TILE[tidx] & 0x07) << r;
                        if((pat & tpat) == 0) {
                            // 状態遷移は tpat でマスが埋まり， rcmask のビットが c の列から c+1 の列に移る．
                            int npat = pat | tpat;
                            npat &= ~rcmask;
                            if(TILE[tidx]&0x08) npat |= rcmask;
                            next[npat] += cur[pat];
                            next[npat] %= MOD;
                            //cout << r << ' ' << c << ' ' << pat << ' ' << npat << endl;
                        }
                    }
                }
            }
            swap(cur, next);
        }
    }
    res[R][C-1] = cur[0];
    res[R][C] = cur[pat_mask&~1];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for(int i = 2; i <= 10; ++i) calc(i, 500);
    while(true) {
        cin >> R >> C;
        if(!R && !C) break;
        cout << res[R][C] << endl;
    }
    return 0;
}
